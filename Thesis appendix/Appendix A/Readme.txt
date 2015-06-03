-------------------------------------------------------------
Appendix A: Source code
A.1 Qt application spurce code
A.2 matlab source code
-------------------------------------------------------------
A.1 Qt application spurce code
-Header file:
mainwindow.h
-Source file:
main.cpp
mainwindow.cpp
-GUI design file:
mainwindow.ui
-project file:
SensorSendFile.pro
-------------------------------------------------------------
A.2 Matlab source file
To run the full program, just load B1_Main.m

-Main program:
B1_Main.m

-Functions:
B1F1_HandleInputfile.m
B1F2_PlotRawData.m
B1F3_FilterNoiseAccelData.m
B1F4_FilterNoiseGyroData.m
B1F5_GyroConvertRollPitchYaw.m
B1F6_AccelConvertRollPitch.m
B1F7_MagnetCalibration.m
B1F8_MagnetConvertHeading.m
B1F9_FindStepsFromAccelRoll.m
B1F10_YawGyroRecalib.m
B1F11_SpeedModeSelection.m
B1F12_DataFusionBaseGyro.m
B1F13_DataFusionPlusCompass.m

-Convert to GPS coordinates:
FusionData2GPScoord.m