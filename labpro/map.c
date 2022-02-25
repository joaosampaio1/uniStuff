#include <stdlib.h>
#include <stdio.h>
#include "point.h"
#include "boat.h"
#include "map.h"
#include "quadtree.h"
#include "visual.h"
#include "setup.h"
#include "player.h"


Map* newMap(int size){
	Map* f = (Map*) malloc(sizeof(Map));
	for (int i=1; i<=size; i++) {
		for (int j=1; j<=size; j++) {
			f -> field[i][j] = newCell(); 	//incializar tudo a 0 (sem boat)
		}
	}
	return f;
}

Cell* newCell(){
	Cell* c = (Cell*) malloc(sizeof(Cell));
	c -> value = 0;

  return c;
}

int boatValid(int x, int y, Map* m,int sizemap,Boat* b) {

  if (x<0 || x>sizemap || y<0 || y>sizemap) return 0; 
  for(int i=0;i<N; i++) {
    for (int j=0;j<N; j++) {
      if (x+i>sizemap || y+j>sizemap) {
        if (b->boat[i][j] == 1) return 0;
      }
      else
      if (m->field[x+i][y+j]->value== 1 && b->boat[i][j] == 1) return 0;
    }
  }
  return 1;
}

void boatToMap(int x, int y, Map* m,int sizemap,Boat* b) {
  Point* p = newPoint(x,y);
  b->p=p;
  for(int i=0;i<N; i++) 
    for (int j=0;j<N; j++) 
        if (b->boat[i][j]== 1) {
          m->field[x+i][y+j]->value = 1;
          m -> field[x+i][y+j]->boatPointer = b;
        }
}
