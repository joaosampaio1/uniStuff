#ifndef POINT_H
#define POINT_H

//struct Ponto

typedef struct{

	int x;	//cordenada x
	int y;	//cordenada y

} Point;

typedef struct{

	float x;	//cordenada x
	float y;	//cordenada y

} fPoint;

Point* newPoint(int,int);
fPoint* newfPoint(float,float);
Point* addPoint(Point*,Point*);
int isEqual(Point*, Point*);
fPoint* middlePoint(Point*, Point*);

#endif
