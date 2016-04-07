#include "piPWM.h"

void setPWMChannel(int address, int channel, float value, int servo){

	value = (value * 0.05 + 0.05) * 4095;

	setPWMRawChannel(address, channel, (int)value, servo);
}

void setPWMAll(int address, float value, int servo){

	value = (value * 0.05 + 0.05) * 4095;

	setPWMRawAll(address, (int)value, servo);
}

void setPWMRawChannel(int address, int channel, int value, int servo){
#if !(PI_DEBUG_LEVEL & PI_DEBUG_PWM)
	disableLog();
#endif	
	
	if(channel < 0 || channel >= 16){
	    return;
	}
	logLevel("Setting PWM driver");
	logChild("PWM channel %d set to %d(%X)", channel, value, value);
	if(value > 4095)	value = 4095;
	if(value < 0)	value = 0;

	channel = channel * 4 + 0x06;
	logLevel("Setting registers");
	if(servo) wiringPiI2CWriteReg8(address, channel + 3, 0x00);
	logChild("Reg %X to 0x00", channel);
	logLevel("Reg %X to 0x00", channel + 1);
	logLevel("Reg %X to %X", channel + 2, value & 0xFF);
	logLevel("Reg %X to %X", channel + 3, value >> 8);
	wiringPiI2CWriteReg8(address, channel, 0x00);
	wiringPiI2CWriteReg8(address, channel + 1, 0x00);
	wiringPiI2CWriteReg8(address, channel + 2, value & 0xFF);
	wiringPiI2CWriteReg8(address, channel + 3, value >> 8);
	logSuccess("Registers set");
	logSuccess("PWM driver set");
	if(servo){
	        delay(SERVO_DELAY);
		wiringPiI2CWriteReg8(address, channel + 3, (value >> 8) | 0x10);
	}
	
#if !(PI_DEBUG_LEVEL & PI_DEBUG_PWM)
	enableLog();
#endif
}
void setPWMRawAll(int address, int value, int servo){
	
	
	if(value > 4095)	value = 4095;
	if(value < 0)	value = 0;
	
	if(servo)  wiringPiI2CWriteReg8(address, 0xFD, 0x00);
	
	wiringPiI2CWriteReg8(address, 0xFA, 0x00);
	wiringPiI2CWriteReg8(address, 0xFB, 0x00);
	wiringPiI2CWriteReg8(address, 0xFC, value & 0xFF);
	wiringPiI2CWriteReg8(address, 0xFD, value >> 8);
	
	if(servo){
	        delay(SERVO_DELAY);
		wiringPiI2CWriteReg8(address, 0xFD, (value >> 8) | 0x10);
	}
}
