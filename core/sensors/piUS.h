#ifndef PI_US
#define PI_US

#include <wiringPi.h>
#include <stdio.h>
#include <time.h>

#define START_T 20000
#define END_T 50000

int getDistance(int trigger, int echo);

#endif
