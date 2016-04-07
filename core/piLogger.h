#ifndef PI_LOGGER_H_
#define PI_LOGGER_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>
#include "./sensors/vector3.h"

#define ERROR_COLOR "\x1b[31;1m"
#define DEFAULT_COLOR "\x1b[0m"
#define SUCCESS_COLOR "\x1b[32;1m"
#define MAX_INDENT 10

void logLevel(const char* msg, ...);
void logChild(const char* msg, ...);
void logParent(const char* msg, ...);
void logError(const char* msg, ...);
void logSuccess(const char* msg, ...);
void logV3Level(Vector3P v);
void logV3Child(Vector3P v);
void logV3Error(Vector3P v);

void enableLog();
void disableLog();

#endif //PI_LOGGER_H_
