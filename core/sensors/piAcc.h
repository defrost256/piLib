#ifndef PI_ACC
#define Pi_ACC

#include <stdlib.h>

#include <wiringPi.h>
#include <wiringPiI2C.h>

#include "vector3.h"
#include "convert.h"

void getRawVectorFrom(int address, int isAcc, float* x, float* y, float* z);

#endif
