#include "Setup.h"
#include "Controllers.h"
#include "Slew.h"
#include "PID.h"
#include "../RobotC.h"
#include "../stdafx.h"
using namespace RobotC::Types;
using namespace RobotC::Threads;
using namespace RobotC::Types;
using namespace RobotC::Peripherals;
using namespace RobotC::Functions;
#include "Externs.h"
SensorPort leftEncoder;
SensorPort rightEncoder;
MotorPort leftMotor;
MotorPort rightMotor;
void SetUpConfig() {
	config("leftEncoder", leftEncoder, dgtl1);
	config("rightEncoder", rightEncoder, dgtl3);
	config("leftMotor", leftMotor, port1, false);
	config("rightMotor", rightMotor, port5, true);
};
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

/*
	Diego's General Programming Tips:

	You can download files from the Cortex using Robot > Advanced Tools > File Management

	You can view joystick values during runtime using Robot > Advanced Tools > Joystick Viewer

	You can check battery level by using nImmediateBatteryLevel; Found in Battery > Variables

	Controllers have accelerometers.

	Global variables are automaticalled extern'ed, so long as they aren't defined in main.c

	All sensor and motor ports are automatically extern'ed.

	Running tasks PID() and Slew() will give you 17 concurrent tasks left.
*/


task programMain() {
	delay(1000);

	StartSlewTask();
	StartPIDTask();

	LinkPID(leftMotor, leftEncoder);
	LinkPID(rightMotor, rightEncoder, true);

	SetPIDConstants(leftMotor, 1, 0, 0);
	SetPIDConstants(rightMotor, 1, 0, 0);

	SetPIDTarget(leftMotor, 500);
	SetPIDTarget(rightMotor, 1500);

	while((true) && !killAll) {
		// Keep program alive.
		delay(TASK_DELAY);
	}
}
