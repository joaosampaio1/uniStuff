#ifndef MAP_H
#define MAP_H

#define MAXSIZE 40

typedef struct{
	int value;
	Boat* boatPointer;
} Cell;

typedef struct{

	Cell* field[MAXSIZE][MAXSIZE];

} Map;

Cell* newCell();
Map* newMap(int);
int boatValid(int,int,Map*, int, Boat*);
void boatToMap(int,int,Map*, int, Boat*);

#endif