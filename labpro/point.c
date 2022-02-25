//ponto
#include <stdlib.h>
#include "point.h"
#include "boat.h"
#include "map.h"
#include "quadtree.h"
#include "visual.h"
#include "setup.h"
#include "player.h"


//função para criar um ponto

Point* newPoint(int x, int y){

	Point* p = (Point*) malloc(sizeof(Point));
	p->x = x;
	p->y = y;

	return p;
}

fPoint* newfPoint(float x, float y){

	fPoint* p = (fPoint*) malloc(sizeof(fPoint));
	p->x = x;
	p->y = y;

	return p;
}


Point* addPoint(Point* p, Point* q) {
	Point* rp = newPoint(0,0);
	rp -> x = p -> x + q -> x;
	rp -> y = p -> y + q -> y;
	return rp;
}

int isEqual(Point* p, Point* q) {
	if(p -> x != q -> x) return 0;
	if(p -> y != q -> y) return 0;
	return 1;
}

fPoint* middlePoint(Point* sw, Point* ne) {
	fPoint* m = newfPoint((float)(sw->x+ne->x)/2,(float)(sw->y+ne->y)/2);
	return m;
}

//inSquare(POINT p, POINT corner, int side) verifica se p está no quadrado definido por (corner,side)