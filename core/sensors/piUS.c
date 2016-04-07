#include "piUS.h"

int getDistance(int trigger, int echo){
	unsigned start, stop, firstStart;
	
	digitalWrite(trigger, HIGH);
	delayMicroseconds(10);
	digitalWrite(trigger, LOW);
	firstStart = start = micros();
	while(!digitalRead(echo)){
		start = micros();
	}
	while(digitalRead(echo))
		stop = micros();
	return (stop - start) / 58;
}
