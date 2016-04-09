#include "./core/piLogger.h"
#include "./core/piDebug.h"
#include "./core/sensors/vector3.h"
#include "./core/sensors/piSensors.h"
#include "./core/sensors/piMovement.h"
#include "./core/sensors/piUS.h"
#include "./core/piGPIO.h"
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <wiringPi.h>

void printHelp(int i);
void test0();
void test1();
void test2();
void test3();
void test4();

int main(int argc, char* argv[])
{
	if(argc == 1){
		logError("Please enter a test number");
		printHelp(-1);
		return -1;
	}
	else if(argc == 2){
		int i = atoi(argv[1]);
		switch(i){
			case(0):
				test0();
				break;
			case(1):
				test1();
				break;
			case(2):
				test2();
				break;
			case(3):
				test3();
				break;
			case(4):
				test4();
				break;
			default:
				printHelp(-1);
				return -1;
		}
	}
	else{
		logError("This program only requires 1 argument");
		printHelp(-1);
		return -1;
	}
	return 0;
}	

void test0(){
	float f;
	char c;
	
	initGPIO();
	initMovement();
	f=0;
	while((c = getchar()) != 'x'){
		switch(c){
			case('h'):
				printHelp(0);
				break;
			case('v'):
				f += 0.01;
				break;
			case('c'):
				f -= 0.01;
				break;
			case('a'):
				f += 0.05;
				break;
			case('d'):
				f -= 0.05;
				break;
			case('q'):
				f += 0.1;
				break;
			case('e'):
				f -= 0.1;
				break;
			case('w'):
				f += 0.5;
				break;
			case('s'):
				f -= 0.5;
				break;
			case('\n'):
				break;
			default:
				logError("'%c' is not a valid command", c);
				printHelp(0);
				break;
		}
		setTurn(f);
		logLevel("Steering: %f, PWM value: %d", f, (int)(f * 64 + 336));
	}
	setTurn(0);
}

void test1(){
	float f;
	char c;
	
	initGPIO();
	initMovement();
	f=0;
	while((c = getchar()) != 'x'){
		switch(c){
			case('h'):
				printHelp(1);
				break;
			case('v'):
				f += 0.01;
				break;
			case('c'):
				f -= 0.01;
				break;
			case('a'):
				f += 0.05;
				break;
			case('d'):
				f -= 0.05;
				break;
			case('q'):
				f += 0.1;
				break;
			case('e'):
				f -= 0.1;
				break;
			case('w'):
				f += 0.5;
				break;
			case('s'):
				f -= 0.5;
				break;
			case('\n'):
				break;
			default:
				logError("'%c' is not a valid command", c);
				printHelp(1);
				break;
		}
		setSpeed(f);
		logLevel("Speed: %f, PWM value: %d", f, (int)(f * 145 + 345));
	}
	setSpeed(0);
}

void test2(){
	char c;
	Vector3P v;
	
	initGPIO();
	initSensors();
	while((c = getchar()) != 'x'){
		switch(c){
			case('h'):
				printHelp(2);
				break;
			case('d'):
				logLevel("Dst: %d cm", getFrontDistance());
				break;
			case('D'):
				logLevel("Dst: %d cm", getRearDistance());
				break;
			case('m'):
				v = getRawMagneticField();
				logLevel("Raw magnetic field: (%.2f, %.2f, %.2f)", v->x, v->y, v->z);
				break;
			case('M'):
				v = getMagneticField();
				logLevel("Magnetic field: (%.2f, %.2f, %.2f)", v->x, v->y, v->z);
				break;
			case('a'):
				v = getRawAcceleration();
				logLevel("Raw accaleration: (%.2f, %.2f, %.2f)", v->x, v->y, v->z);
				break;
			case('A'):
				v = getAcceleration();
				logLevel("Accaleration: (%.2f, %.2f, %.2f)", v->x, v->y, v->z);
				break;
			case('\n'):
				break;
			default:
				logError("'%c' (%d) is not a valid command", c, c);
				printHelp(2);
				break;
		}
	}
}

void test3(){
	
	initGPIO();
	initSensors();
	initMovement();
	
	setTurn(0);
	setSpeed(0);
	delay(2000);
	setSpeed(0.6);
	int d;
	while(1){
		d = getFrontDistance();
		if(d != -1 && d < 45){
			setTurn(0.7);
			setSpeed(-0.6);
			delay(700);
			setTurn(0);
			setSpeed(0.6);
		}
	}
}

void test4(){
    initGPIO();
    pinMode(1, OUTPUT);
    pinMode(4, INPUT);
    while(1){
	logLevel("Distance: %d cm", getDistance(1, 4));
	delay(700);
    }
}

void printHelp(int i){
	logLevel("Help for test:");
	logChild("h -> Help");
	logLevel("x -> exit");
	switch(i){
		case(-1):
			logParent("Test cases:");
			logChild("0 -> Steering test");
			logLevel("1 -> Speed test");
			logLevel("2 -> Sensor test");
			logLevel("3 -> Moonrover test");
			break;
		case(0):
		case(1):
			logLevel("v -> +0.01");
			logLevel("c -> -0.01");
			logLevel("a -> +0.05");
			logLevel("d -> -0.05");
			logLevel("q -> +0.1");
			logLevel("e -> -0.1");
			logLevel("w -> +0.5");
			logLevel("s -> -0.5");
			break;
		case (2):
			logLevel("d -> front distance");
			logLevel("D -> rear distance");
			logLevel("m -> raw magnetic field");
			logLevel("M -> real magnetic field");
			logLevel("a -> raw accaleration");
			logLevel("A -> real accaleration");
			break;
		case (3):
			logSuccess("JUST WATCH AS IT GOES");	
	}
}
