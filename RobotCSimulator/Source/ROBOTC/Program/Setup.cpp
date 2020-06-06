#include "PID.h"
#include "Slew.h"
#include "Helpers.h"

#ifndef SETUP_SOURCE
#define SETUP_SOURCE


void InitCustomLibrary() {
	ResetEncoders();
	InitPID();
	InitSlew();
}


#endif