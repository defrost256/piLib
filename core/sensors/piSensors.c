#include "piSensors.h"

Vector3 accel[2], magnet[2], accelRaw[2], magnetRaw[2];
int onlyRaw[2];
int dstBack[2], dstFront[2];
int currentData = 0;
int sensorAddress[] = {0x19, 0x1E};

void initSensors(){
	
#if !(PI_DEBUG_LEVEL | PI_DEBUG_SENSORS)
	disableLog();
#endif
	
	logChild("Initializing Accelerometer");
	sensorAddress[0] = wiringPiI2CSetup(sensorAddress[0]);
	if(wiringPiI2CWriteReg8(sensorAddress[0], 0x23, 0x00) || wiringPiI2CWriteReg8(sensorAddress[0], 0x20, 0x27)){
		logError("Accelerometer Initialization failed");
		sensorAddress[0] = 0x19;
	}
	logSuccess("Accelerometer initialized");
	
	logChild("Initializing Magnetometer");
	sensorAddress[1] = wiringPiI2CSetup(sensorAddress[1]);
	if(wiringPiI2CWriteReg8(sensorAddress[1], 0x00, 0x10) || wiringPiI2CWriteReg8(sensorAddress[1], 0x01, 0xE0) ||
			wiringPiI2CWriteReg8(sensorAddress[1], 0x02, 0x00)){
		logError("Magnetometer Initialization failed");
		sensorAddress[1] = 0x19;
	}
	logSuccess("Magnetometer initialized");
	
	logChild("Initializing Ultrasonic sensors");
	pinMode(US1OUT, OUTPUT);
	pinMode(US1IN, INPUT);
	pinMode(US2OUT, OUTPUT);
	pinMode(US2IN, INPUT);
	logSuccess("Ultrasonic sensors initialized");
	
	logChild("Initializing timer");
	createTimer(100, updateSensors);
	logSuccess("Timer initialized");
	logChild("Starting timer");
	startTimer();
	logSuccess("Timer started");
	logSuccess("Sensors initialized");

#if !(PI_DEBUG_LEVEL | PI_DEBUG_SENSORS)
	enableLog();
#endif
}

void updateSensors(siginfo_t* si){
	
#if !(PI_DEBUG_LEVEL | PI_DEBUG_SENSORS)
	disableLog();
#endif
	
	int writeTo = (currentData == 0 ? 1 : 0);
	getRawVectorFrom(sensorAddress[0], 1, &(accelRaw[writeTo].x), &(accelRaw[writeTo].y), &(accelRaw[writeTo].z));
	getRawVectorFrom(sensorAddress[1], 0, &(magnetRaw[writeTo].x),&(magnetRaw[writeTo].y), &(magnetRaw[writeTo].z));
	dstFront[writeTo] = getDistance(US1OUT, US1IN);
	dstBack[writeTo] = getDistance(US2OUT, US2IN);
	onlyRaw[0] = 1;
	onlyRaw[1] = 1;
	currentData = writeTo;
	
#if !(PI_DEBUG_LEVEL | PI_DEBUG_SENSORS)
	enableLog();
#endif	
}

int getFrontDistance(){
	return dstFront[currentData];
}

int getRearDistance(){
	return dstBack[currentData];
}

Vector3P getRawAcceleration(){
	return &accelRaw[currentData];
}

Vector3P getAcceleration(){
	if(onlyRaw[0] == 1){
		convertRaw2Acc(&accelRaw[currentData], &accel[currentData]);
		onlyRaw[0] = 0;
	}
	return &accel[currentData];
}

Vector3P getRawMagneticField(){
	return &magnetRaw[currentData];
}

Vector3P getMagneticField(){
	if(onlyRaw[1] == 1){
		convertRaw2Mag(&magnetRaw[currentData], &magnet[currentData]);
		onlyRaw[1] = 0;
	}
	return &magnet[currentData];
}

