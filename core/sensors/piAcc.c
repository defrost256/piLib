#include "piAcc.h"

void getRawVectorFrom(int address, int isAcc, float* x, float* y, float* z){
	int startReg = 0x03;
	if(isAcc)
		startReg = 0x28;
	*x = convert_N(((wiringPiI2CReadReg8(address, startReg + 0) << (isAcc ? 0 : 8)) |
		(wiringPiI2CReadReg8(address, startReg + 1) << (isAcc ? 8 : 0))) >> (isAcc ? 4 : 0), (isAcc ? 12 : 16));
	*y = convert_N(((wiringPiI2CReadReg8(address, startReg + 2) << (isAcc ? 0 : 8)) |
		(wiringPiI2CReadReg8(address, startReg + 3) << (isAcc ? 8 : 0))) >> (isAcc ? 4 : 0), (isAcc ? 12 : 16));
	*z = convert_N(((wiringPiI2CReadReg8(address, startReg + 4) << (isAcc ? 0 : 8)) |
		(wiringPiI2CReadReg8(address, startReg + 5) << (isAcc ? 8 : 0))) >> (isAcc ? 4 : 0), (isAcc ? 12 : 16));
}
