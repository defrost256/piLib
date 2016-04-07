#include "convert.h"

int convert_N(int bin, int n){
	
	n = 32 - n;
	return bin << n >> n;
}

void convertRaw2Acc(Vector3P raw, Vector3P acc){
	acc->x = raw->x * 9.81 / 1000.0;
	acc->y = raw->y * 9.81 / 1000.0;
	acc->z = raw->z * 9.81 / 1000.0;
}

void convertRaw2Mag(Vector3P raw, Vector3P mag){
	mag->x = raw->x * 100 / 230.0;
	mag->y = raw->y * 100 / 230.0;
	mag->z = raw->z * 100 / 205.0;
}
