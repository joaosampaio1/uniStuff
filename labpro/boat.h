#include "point.h"

#ifndef BOAT_H
#define BOAT_H

#define N 5

typedef struct{

	int boat[N][N];
	int lifes;
	Point* p;
	int rotID;

} Boat;

Boat* newBoat();
Boat* putBoat(const int[N][N]);
void rotateMatrix(int, Boat*);
int sumMatrix(const int[N][N]);
Boat* getBoat(int);
void printBoat(Boat*b);

#endif



