#include "point.h"
#include "boat.h"
#include "map.h"
#include "quadtree.h"
#include "visual.h"
#include "setup.h"
#include "player.h"


#include <stdlib.h>
#include <stdio.h>

QD_NODE* newQuadtree(int sizeMap) {
	QD_NODE* qd = (QD_NODE*) malloc(sizeof(QD_NODE) * sizeMap* sizeMap);
	qd -> type = QDNODE;
	return qd;
}

QD_NODE* newQuadleaf(Cell* c, Point* p) {
	QD_NODE* qd = (QD_NODE*) malloc(sizeof(QD_NODE));
	qd -> type = QDLEAF;
	qd -> node.leaf.value = c;
	qd -> node.leaf.p = p;
	return qd;
}

int insertQt(QD_NODE* qtree, QD_NODE* qd, Point* sw,Point* ne, int side) {
	if (qd == NULL) return 0;
	float f = (float) side/2.0;
	Point* sw_corner = newPoint(sw -> x, sw -> y);
	Point* ne_corner = newPoint(ne -> x, ne -> y);
	fPoint* m = middlePoint(sw, ne);


		/*if (side == 1) {
			qtree = qd;
			return 1;
		}*/
		if (qd -> node.leaf.p -> x > m->x && qd -> node.leaf.p -> y > m->y) {
			//quad3

			ne_corner -> y = ne_corner -> y + f;
			ne_corner -> x = ne_corner -> x + f;
			if (qtree -> node.quadrants[3] == NULL) {qtree -> node.quadrants[3] = newQuadtree(side/2); }
			return insertQt(qtree -> node.quadrants[3], qd, sw_corner,ne_corner, side/2); 
		}
		if (qd -> node.leaf.p -> x > m->x && qd -> node.leaf.p -> y < m->y) {
			//quad0

			if (qtree -> node.quadrants[0] == NULL) {qtree -> node.quadrants[0] = newQuadtree(side/2); }
			sw_corner -> y = sw_corner -> y - f;
			ne_corner -> x = ne_corner -> x + f;
			return insertQt(qtree -> node.quadrants[0], qd, sw_corner,ne_corner, side/2); 
		}
		if (qd -> node.leaf.p -> x < m->x && qd -> node.leaf.p -> y > m->y) {
			//quad2
			if (qtree -> node.quadrants[2] == NULL) {qtree -> node.quadrants[2] = newQuadtree(side/2); }
			sw_corner -> x = sw_corner -> x - f;
			ne_corner -> y = ne_corner -> y +f;
			return insertQt(qtree -> node.quadrants[2], qd, sw_corner,ne_corner, side/2); 
		}
		if (qd -> node.leaf.p -> x < m->x && qd -> node.leaf.p -> y < m->y) {
			//quad1
			if (qtree -> node.quadrants[1] == NULL) {qtree -> node.quadrants[1] = newQuadtree(side/2); }
			sw_corner -> y = sw_corner -> y - f;
			sw_corner -> x = sw_corner -> x - f;
			return insertQt(qtree -> node.quadrants[1], qd, sw_corner,ne_corner, side/2); 
		}
	
	qtree -> type = qd -> type;
	//if (qd-> type == QDLEAF) printf("SELAMALEYKUM\n");
	qtree -> node.leaf.p = qd -> node.leaf.p;
	qtree -> node.leaf.value = qd -> node.leaf.value;
	return 1;
}

int insideQt(Point* p, QD_NODE* qtree) {
	if (qtree == QDNODE) return insideQt(p, qtree -> node.quadrants[3]);
	if (qtree -> node.leaf.p -> x < p -> x) return 0;
	if (qtree -> node.leaf.p -> y < p -> y) return 0;	 
	return 1;
}

QD_NODE* search(QD_NODE *qtree, Point* p, Point* sw,Point* ne, int side) {
	if (qtree == NULL) {
		//printf("i return NULL");
		return NULL;
	}
	Point* sw_corner = newPoint(sw -> x, sw -> y);
	Point* ne_corner = newPoint(ne -> x, ne -> y);
	fPoint* m = middlePoint(sw, ne);
	float f = (float) side/2.0;
		if (p -> x > m->x && p -> y > m->y) {
			//quad3
			ne_corner -> y = ne_corner -> y + f;
			ne_corner -> x = ne_corner -> x + f;
			return search(qtree -> node.quadrants[3], p, sw_corner,ne_corner, side/2); 
		}
		if (p -> x > m->x && p -> y < m->y) {
			//quad0
			sw_corner -> y = sw_corner -> y - f;
			ne_corner -> x = ne_corner -> x + f;
			//printf("GOTOQUAD0\n");
			return search(qtree -> node.quadrants[0], p, sw_corner,ne_corner, side/2); 
		}
		if (p -> x < m->x && p -> y > m->y) {
			//quad2
			sw_corner -> x = sw_corner -> x - f;
			ne_corner -> y = ne_corner -> y + f;
			//printf("GOTOQUAD2\n");
			return search(qtree -> node.quadrants[2], p, sw_corner,ne_corner, side/2); 
		}
		if (p -> x < m->x && p -> y < m->y) {
			//quad1
			sw_corner -> y = sw_corner -> y - f;
			sw_corner -> x = sw_corner -> x - f;
			//printf("GOTOQUAD1\n");
			return search(qtree -> node.quadrants[1], p, sw_corner,ne_corner, side/2); 
		}
	
	return qtree;

} 

int changeCellValue(QD_NODE* qd, int newValue) {
	//if (qd -> type == QDNODE) return 0; //nao mudou
	qd -> node.leaf.value -> value = newValue;
	return 1;
}

int boatValidQT(int x, int y, QD_NODE* quadtree,int sizemap,Boat* b) {

  //isto é uma copia do boatValidQT para funcinar com quadtree
  //funciona de mesma maneira
  Point* p = newPoint(0,0);
  Point* ne = newPoint(1,1);
  QD_NODE* qd;
  int size;
    if (sizemap <= 32) size = 32; else size = 64;
  Point* sw = newPoint(size,size);
  if (x<0 || x>sizemap || y<0 || y>sizemap) return 0; 
  for(int i=0;i<N; i++) {
    for (int j=0;j<N; j++) {
      p->x=x+i;
      p->y=y+j;
      qd = search(quadtree, p, sw,ne, size);
      if (x+i>sizemap || y+j>sizemap) {
        if (b->boat[i][j] == 1) return 0;
      }
      else {
      	//if (qd != NULL)
      	if (qd != NULL && b->boat[i][j] == 1) {return 0; }
    	}
    }
  }
  return 1;
  free(p);
  free(sw);
}

void boatToMapQT(int x, int y, QD_NODE* qtree,int sizemap,Boat* b) {
  Point* p = newPoint(x,y);
  b->p=p;
  if (sizemap <= 32) sizemap = 32; else sizemap = 64;
  Point* sw = newPoint(sizemap,sizemap);
  Point* ne = newPoint(1,1);
  for(int i=0;i<N; i++) 
    for (int j=0;j<N; j++) 
        if (b->boat[i][j]== 1) {
          Cell* c = newCell();
          c->value = 1;
          c->boatPointer = b;
          Point* q = newPoint(x+i, y+j);
          QD_NODE* qd = newQuadleaf(c,q);
          insertQt(qtree, qd, sw, ne, sizemap);
        }
  free(p);
  free(sw);
}
