#ifndef PI_TIMER_H_
#define PI_TIMER_H_

#include <time.h>
#include <signal.h>
#include "piLogger.h"
#include "piDebug.h"

#define SIG SIGRTMIN + 1

typedef void (*timer_call)(siginfo_t* si);

void createTimer(int interval, timer_call tc);
void startTimer();
void handler(int sig, siginfo_t* si, void* uc);

#endif //PI_TIMER_H_
