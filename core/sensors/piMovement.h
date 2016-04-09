#ifndef PI_MOVEMENT_H_
#define PI_MOVEMENT_H_

#include "piPWM.h"

#define REV_DELAY 1000

void initMovement();

void setSpeed(float speed);
void setTurn(float steer);

#endif //PI_MOVEMENT_H_
