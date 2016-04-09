#include "piUS.h"

int getDistance(int trigger, int echo){
	unsigned start, stop, firstStart;
	
	digitalWrite(trigger, HIGH);
	delayMicroseconds(10);
	digitalWrite(trigger, LOW);
	firstStart = start = micros();
	while(!digitalRead(echo)){
		start = micros();
		if((start - firstStart) > START_T)
			return -1;
	}
	while(digitalRead(echo)){
		stop = micros();
		if((stop - start) > END_T)
			return -2;
	}
	return (stop - start) / 58;
}
