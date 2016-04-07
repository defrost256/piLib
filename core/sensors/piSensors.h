#ifndef PI_SENSORS_H_
#define PI_SENSORS_H_

#include <stdlib.h>
#include <math.h>
#include <signal.h>

#include <wiringPi.h>
#include <wiringPiI2C.h>

#include "piAcc.h"
#include "piUS.h"
#include "vector3.h"
#include "../piLogger.h"
#include "../piDebug.h"
#include "../piTimer.h"

#define US1OUT 5
#define US1IN 6
#define US2OUT 3
#define US2IN 2


void initSensors();
void updateSensors(siginfo_t* si);

int getFrontDistance();
int getRearDistance();

Vector3P getRawAcceleration();
Vector3P getAcceleration();
Vector3P getRawMagneticField();
Vector3P getMagneticField();


#endif //PI_SENSORS_H_
