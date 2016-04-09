#ifndef PI_DEBUG_H_
#define PI_DEBUG_H_

#define PI_DEBUG_NONE 0
#define PI_DEBUG_SENSORS 1
#define PI_DEBUG_PWM 2
#define PI_DEBUG_TIMER 4
#define PI_DEBUG_MOVE 8

#define PI_DEBUG_LEVEL (PI_DEBUG_MOVE | PI_DEBUG_SENSORS | PI_DEBUG_TIMER)

#endif //PI_DEBUG_H_
