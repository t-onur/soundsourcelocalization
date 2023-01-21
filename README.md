# Sound Source Localization
Automatic Camera Directing using Sound Source Localization

In this thesis, Time Difference of Arrival(TDOA) method has been used in order to find sound source's estimated location. To visualize the location, Sony's EVI-D31V camera, which can be controlled over VISCA Protocol, is used to be rotated towards the sound source automatically.

Source code and my final thesis report of this project can be found in files.

# Description

I have used SparkFun's KY-037 microphone sensors to detect sound waves. Since they are not sufficient to calculate/obtain amplitude or frequency values of a sound wave, I assumed that sound waves propagate as if they are plane wavefronts. TDOA has been used to obtain the time difference between detection times of my sensors. Once I knew the time difference, I have done some calculations with using velocity and trigonometic equations in Arduino IDE.
