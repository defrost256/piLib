#include "piMovement.h"

int PWM_address = 0x40;
float prevSpeed = 0;

void initMovement(){
	
#if !(PI_DEBUG_LEVEL & PI_DEBUG_MOVE)
	disableLog();
#endif

	logLevel("Initializing Movement system");
	logChild("Initializing PWM driver");
	PWM_address = wiringPiI2CSetup(PWM_address);
	if(wiringPiI2CWriteReg8(PWM_address, 0xFA, 0x00) || wiringPiI2CWriteReg8(PWM_address, 0xFB, 0x00) || 
		wiringPiI2CWriteReg8(PWM_address, 0xFC, 0x00) || wiringPiI2CWriteReg8(PWM_address, 0xFD, 0x00) ||
		wiringPiI2CWriteReg8(PWM_address, 0x01, 0x04) || wiringPiI2CWriteReg8(PWM_address, 0x00, 0x01)){
			logError("PWM initialization failed");
			PWM_address = 0x40;
	}
	else{
		delay(5);
		if(wiringPiI2CWriteReg8(PWM_address, 0x00, 0x11) || wiringPiI2CWriteReg8(PWM_address, 0xFE, 121) ||
			wiringPiI2CWriteReg8(PWM_address, 0x00, 0x81)){
				logError("PWM initialization failed");
				PWM_address = 0x40;
		}
		else logSuccess("PWM driver initialized");
	}
	logSuccess("Movement system initialized");
	
#if !(PI_DEBUG_LEVEL & PI_DEBUG_MOVE)
	enableLog();
#endif

}

void setSpeed(float speed){
	if(prevSpeed > 0 && speed < 0){
		setPWMRawChannel(PWM_address, 10, 345, 0);
	}
	setPWMRawChannel(PWM_address, 10, (int)(speed * 145 + 345), 0);
}

void setTurn(float steer){
	setPWMRawChannel(PWM_address, 11, (int)(steer * 64 + 336), 1);
}
