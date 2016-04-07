#ifndef PI_PWM
#define PI_PWM

#include <wiringPi.h>
#include <wiringPiI2C.h>
#include <time.h>

#include "../piLogger.h"
#include "../piDebug.h"

#define T_PWM 120
#define SERVO_DELAY 400

void setPWMChannel(int address, int channel, float value, int servo);
void setPWMAll(int address, float value, int servo);

void setPWMRawChannel(int address, int channel, int value, int servo);
void setPWMRawAll(int address, int value, int servo);

#endif
