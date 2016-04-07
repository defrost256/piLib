#ifndef CONVERT
#define CONVERT

#include <stdio.h>
#include "vector3.h"

int convert_N(int bin, int n);
void convertRaw2Acc(Vector3P raw, Vector3P acc);
void convertRaw2Mag(Vector3P raw, Vector3P mag);

#endif
