#include "piLogger.h"

const char* log_indent = "\t";
const char* log_prefix = "->";

int loggingEnabled = 1;
int nIndents = 0;

void logLevel(const char* msg, ...){
	if(loggingEnabled == 0)
		return;
	va_list arg;
	int i = 0;
	for(; i < nIndents; i++)
		printf("%s", log_indent);
	printf("%s", log_prefix);
	va_start(arg, msg);
	vfprintf(stdout, msg, arg);
	va_end(arg);
	printf("\n");
}

void logChild(const char* msg, ...){
	if(loggingEnabled == 0)
		return;
	if(nIndents < MAX_INDENT)
		nIndents++;
	va_list arg;
	int i = 0;
	for(; i < nIndents; i++)
		printf("%s", log_indent);
	printf("%s", log_prefix);
	va_start(arg, msg);
	vfprintf(stdout, msg, arg);
	va_end(arg);
	printf("\n");
}

void logParent(const char* msg, ...){
	if(loggingEnabled == 0)
		return;
	if(nIndents > 0)
		nIndents--;
	va_list arg;
	int i = 0;
	for(; i < nIndents; i++)
		printf("%s", log_indent);
	printf("%s", log_prefix);
	va_start(arg, msg);
	vfprintf(stdout, msg, arg);
	va_end(arg);
	printf("\n");
}

void logError(const char* msg, ...){
	if(loggingEnabled == 0)
		return;
	va_list arg;
	int i = 0;
	for(; i < nIndents; i++)
		printf("%s", log_indent);
	printf("%s%s", log_prefix, ERROR_COLOR);
	va_start(arg, msg);
	vfprintf(stdout, msg, arg);
	va_end(arg);
	printf("%s\n", DEFAULT_COLOR);
	if(nIndents > 0)
		nIndents--;
}

void logSuccess(const char* msg, ...){
	if(loggingEnabled == 0)
		return;
	va_list arg;
	int i = 0;
	for(; i < nIndents; i++)
		printf("%s", log_indent);
	printf("%s%s", log_prefix, SUCCESS_COLOR);
	va_start(arg, msg);
	vfprintf(stdout, msg, arg);
	va_end(arg);
	printf("%s\n", DEFAULT_COLOR);
	if(nIndents > 0)
		nIndents--;
}

void logV3Level(Vector3P v){
	if(loggingEnabled == 0)
		return;
	int i = 0;
	for(; i < nIndents; i++)
		printf("%s", log_indent);
	printf("(%.2f, %.2f, %.2f\n)", v->x, v->y, v->z);
}

void logV3Child(Vector3P v){
	if(loggingEnabled == 0)
		return;
	if(nIndents < MAX_INDENT)
		nIndents++;
	logV3Level(v);
}

void logV3Error(Vector3P v){
	if(loggingEnabled == 0)
		return;
	printf("%s%s(%.2f, %.2f, %.2f)%s\n", log_prefix, ERROR_COLOR, v->x, v->y, v->z, DEFAULT_COLOR);
	if(nIndents > 0)
		nIndents--;
}

void enableLog(){
	loggingEnabled = 1;
}

void disableLog(){
	loggingEnabled = 0;
}


