#include "../ROBOTCtoC++/RobotC.h"
#include "CLibrary.h"


SensorPort leftEncoder;
SensorPort rightEncoder;
MotorPort leftMotor;
MotorPort rightMotor;
void SetUp() {
	config("leftEncoder", leftEncoder, dgtl1);
	config("rightEncoder", rightEncoder, dgtl3);
	config("leftMotor", leftMotor, port1, false);
	config("rightMotor", rightMotor, port5, true);
}

task programMain() {
	ResetEncoders();
	startTask(Slew);

	SetLeftMotor(leftMotor);
	SetRightMotor(rightMotor);
	SetLeftEncoder(leftEncoder);
	SetRightEncoder(rightEncoder);
	SetAverageDelay(20);
	SetControllerSpeed(1);
	SetSlewStep(10);

	PID();
	startTask(GamerControl);
	while(true) {
		// Keep program alive.
		delay(GetDelay());
	}
}
