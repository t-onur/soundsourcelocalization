#include <math.h>

#define Distance 0.40
#define Delay 1000

byte speed = 0x15;

byte viscaPanTiltCmd[15] = { 0x81, 0x01, 0x06, 0x02, speed, 0x07, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xFF };

int sensor1 = 20;
int sensor2 = 21;

unsigned long time1;
unsigned long time2;
unsigned long time3;

float radian;
float degree;

void SendViscaPanAngle(int ang) {
  word angw = 0;
  word angw1 = 0;

  if (ang >= 0) {
    angw = ang * 8.8;
    angw1 = angw;
    viscaPanTiltCmd[9] = angw1 & 15;
    angw1 = angw;
    viscaPanTiltCmd[8] = (angw1 >> 4) & 15;
    angw1 = angw;
    viscaPanTiltCmd[7] = (angw1 >> 8) & 15;
    angw1 = angw;
    viscaPanTiltCmd[6] = (angw1 >> 12) & 15;
  } else {
    {
      angw = ang * 8.8;
      angw = 65535 + angw;
      angw1 = angw;
      viscaPanTiltCmd[9] = angw1 & 15;
      angw1 = angw;
      viscaPanTiltCmd[8] = (angw1 >> 4) & 15;
      angw1 = angw;
      viscaPanTiltCmd[7] = (angw1 >> 8) & 15;
      angw1 = angw;
      viscaPanTiltCmd[6] = (angw1 >> 12) & 15;
    }
  }
  for (int c = 0; c < sizeof(viscaPanTiltCmd); c++) {
    Serial2.write(viscaPanTiltCmd[c]);
    delay(10);
  }
}

float time_to_radian(float time) {

  return (acos((time * 0.000001 * 343.00) / (Distance)));
}

float radian_to_deg(float radian) {

  return ((radian / (2 * PI)) * 360);
}

void setup() {

  Serial.begin(9600);
  Serial2.begin(9600);
  Serial3.begin(9600);

  pinMode(sensor1, INPUT);
  pinMode(sensor2, INPUT);
}

void loop() {

  time1 = 0;
  time2 = 0;
  time3 = 0;

  if (digitalRead(sensor1) == HIGH) {

    time1 = micros();

    while (digitalRead(sensor2) == LOW) {
    }
    time2 = micros();
    time3 = time2 - time1;

    if (time3 < 1171) {

      Serial.print("Time elapsed after Microphone - 2 has detected a sound: ");
      Serial.println(time1);
      Serial.print("Time elapsed when Microphone - 1 picks up the sound waves: ");
      Serial.println(time2);
      Serial.print("Microphone - 2 has detected the sound first and the time difference: ");
      Serial.println(time3);

      radian = time_to_radian(time3);
      degree = radian_to_deg(radian);
      float newdegree = -1 * (180 - 2 * degree);
      Serial.print("Angle: ");
      Serial.println(newdegree);
      SendViscaPanAngle(newdegree);
      delay(20);

      delay(Delay);
    }

  } else if (digitalRead(sensor2) == HIGH) {

    time1 = micros();

    while (digitalRead(sensor1) == LOW) {
    }
    time2 = micros();
    time3 = time2 - time1;

    if (time3 < 1171) {

      Serial.print("Time elapsed after Microphone - 1 has detected a sound: ");
      Serial.println(time1);
      Serial.print("Time elapsed when Microphone - 2 picks up the sound waves: ");
      Serial.println(time2);
      Serial.print("Microphone - 1 has detected the sound first and the time difference: ");
      Serial.println(time3);

      radian = time_to_radian(time3);
      degree = radian_to_deg(radian);
      float newdegree = 180 - 2 * degree;
      Serial.print("Angle: ");
      Serial.println(newdegree);
      SendViscaPanAngle(newdegree);
      delay(20);

      delay(Delay);
    }
  }
}
