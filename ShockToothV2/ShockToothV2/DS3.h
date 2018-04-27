#pragma once
//Structure which describes the type 01 input report over usb
typedef struct {
    unsigned char ReportType;     //Report Type 01
    unsigned char Reserved1;      // Unknown
    unsigned int  ButtonState;    // Main buttons
    unsigned char PSButtonState;  // PS button
    unsigned char Reserved2;      // Unknown
    unsigned char LeftStickX;     // left Joystick X axis 0 - 255, 128 is mid
    unsigned char LeftStickY;     // left Joystick Y axis 0 - 255, 128 is mid
    unsigned char RightStickX;    // right Joystick X axis 0 - 255, 128 is mid
    unsigned char RightStickY;    // right Joystick Y axis 0 - 255, 128 is mid
    unsigned char Reserved3[4];   // Unknown
    unsigned char PressureUp;     // digital Pad Up button Pressure 0 - 255
    unsigned char PressureRight;  // digital Pad Right button Pressure 0 - 255
    unsigned char PressureDown;   // digital Pad Down button Pressure 0 - 255
    unsigned char PressureLeft;   // digital Pad Left button Pressure 0 - 255
    unsigned char PressureL2;     // digital Pad L2 button Pressure 0 - 255
    unsigned char PressureR2;     // digital Pad R2 button Pressure 0 - 255
    unsigned char PressureL1;     // digital Pad L1 button Pressure 0 - 255
    unsigned char PressureR1;     // digital Pad R1 button Pressure 0 - 255
    unsigned char PressureTriangle;   // digital Pad Triangle button Pressure 0 - 255
    unsigned char PressureCircle;     // digital Pad Circle button Pressure 0 - 255
    unsigned char PressureCross;      // digital Pad Cross button Pressure 0 - 255
    unsigned char PressureSquare;     // digital Pad Square button Pressure 0 - 255
    unsigned char Reserved4[3];   // Unknown
    unsigned char Charge;         // charging status ? 02 = charge, 03 = normal
    unsigned char Power;          // Battery status ?
    unsigned char Connection;     // Connection Type ?
    unsigned char Reserved5[9];   // Unknown
    unsigned int AccelerometerX;  // X axis accelerometer Big Endian 0 - 1023
    unsigned int AccelerometerY;  // Y axis accelerometer Big Endian 0 - 1023
    unsigned int AccelerometerZ;  // Z axis accelerometer Big Endian 0 - 1023
    unsigned int GyrometerX;      // Z axis Gyro Big Endian 0 - 1023

} TYPE_01_REPORT;