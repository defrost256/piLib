#include "piGPIO.h"

void initGPIO(){
	
	logLevel("Initializing GPIO for sensors");
	
	logChild("Initializing I2C bus");
	if(system("gpio load i2c"))
		logError("Init failed");
	wiringPiSetup();
	logSuccess("I2C Initialized");
	
}
