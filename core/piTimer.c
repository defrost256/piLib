#include "piTimer.h"

timer_t timer_ID;
struct itimerspec its;
sigset_t mask;
timer_call timerCall;

void createTimer(int interval_ms, timer_call call)
{
#if !(PI_DEBUG_LEVEL & PI_DEBUG_TIMER)
	disableLog();
#endif
	timerCall = call;
	logLevel("Creating timer");
	logChild("Creating sigaction");
	struct sigaction sa;
	sa.sa_flags = SA_SIGINFO;
	sa.sa_sigaction = handler;
	sigemptyset(&sa.sa_mask);
	if(sigaction(SIGRTMIN, &sa, NULL) == -1)
		logError("sigaction failed");
	logSuccess("Sigaction created");
			
	logChild("Blocking signal");
	sigemptyset(&mask);
	sigaddset(&mask, SIGRTMIN);
	if(sigprocmask(SIG_SETMASK, &mask, NULL) == -1)
		logError("Blocking failed");
	logSuccess("Signal blocked");
	
	logChild("Creating system timer");
	struct sigevent se;
	se.sigev_notify = SIGEV_SIGNAL;
	se.sigev_signo = SIGRTMIN;
	se.sigev_value.sival_ptr = &timer_ID;
	if(timer_create(CLOCK_REALTIME, &se, &timer_ID) == -1)
		logError("System clock creation failed");
	logSuccess("System timer created");
	
	its.it_value.tv_sec = interval_ms / 1000;
	its.it_value.tv_nsec = (interval_ms % 1000) * 1000000;
	its.it_interval.tv_sec = its.it_value.tv_sec;
	its.it_interval.tv_nsec = its.it_value.tv_nsec;
	
#if !(PI_DEBUG_LEVEL & PI_DEBUG_TIMER)
	enableLog();
#endif
	
}

void startTimer(){
#if !(PI_DEBUG_LEVEL & PI_DEBUG_TIMER)
	disableLog();
#endif
	logLevel("Starting timer");
	logChild("Unblocking signal");
	if(sigprocmask(SIG_UNBLOCK, &mask, NULL) == -1)
		logError("Unblocking failed");
	logSuccess("Signal Unblocked");
	logChild("Setting timer time");
	if(timer_settime(timer_ID, 0, &its, NULL) == -1)
		logError("Timer interval set failed");
	logSuccess("Timer interval set");
#if !(PI_DEBUG_LEVEL & PI_DEBUG_TIMER)
	enableLog();
#endif
}

void handler(int sig, siginfo_t* si, void* uc){
#if !(PI_DEBUG_LEVEL & PI_DEBUG_TIMER)
	disableLog();
#endif
	
	logLevel("Timer expired");
	timerCall(si);
	
#if !(PI_DEBUG_LEVEL & PI_DEBUG_TIMER)
	enableLog();
#endif
}

