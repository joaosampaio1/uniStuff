#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "point.h"
#include "boat.h"
#include "map.h"
#include "quadtree.h"
#include "visual.h"
#include "setup.h"
#include "player.h"

#define N 5

const int carrier[5][5] = {
{1,0,0,0,0},
{1,0,0,0,0},
{1,0,0,0,0},
{1,0,0,0,0},
{1,0,0,0,0}
};

const int battleship[5][5] = {
{1,0,0,0,0},
{1,0,0,0,0},
{1,0,0,0,0},
{1,0,0,0,0},
{0,0,0,0,0},
};

const int cruiser[5][5] = {
{1,0,0,0,0},
{1,0,0,0,0},
{1,0,0,0,0},
{0,0,0,0,0},
{0,0,0,0,0},
};

const int destroyer[5][5] = {
{1,0,0,0,0},
{1,0,0,0,0},
{0,0,0,0,0},
{0,0,0,0,0},
{0,0,0,0,0},
};

const int tboat[5][5] = {
  {1,1,1,1,1},
  {0,0,1,0,0},
  {0,0,1,0,0},
  {0,0,1,0,0},
  {0,0,1,0,0}
};

const int uboat[5][5] = {
  {1,0,0,0,1},
  {1,0,0,0,1},
  {1,0,0,0,1},
  {1,0,0,0,1},
  {1,1,1,1,1}
};

const int vboat[5][5] = {
  {1,0,0,0,1},
  {1,0,0,0,1},
  {0,1,0,1,0},
  {0,1,0,1,0},
  {0,0,1,0,0}
};

const int eboat[5][5] = {
  {1,1,1,1,1},
  {1,0,0,0,0},
  {1,1,1,1,0},
  {1,0,0,0,0},
  {1,1,1,1,1}
};

const int fboat[5][5] = {
  {1,1,1,1,1},
  {1,0,0,0,0},
  {1,1,1,1,0},
  {1,0,0,0,0},
  {1,0,0,0,0}
};

Boat* newBoat() {
  Boat* b =(Boat*) malloc(sizeof(Boat));

  return b;
}

Boat* getBoat(int boatID) {
  Boat* b;
  switch(boatID) {
    case 1: b=putBoat(carrier); break;
    case 2: b=putBoat(battleship); break;
    case 3: b=putBoat(cruiser);break;
    case 4: b=putBoat(destroyer);break;
    case 5: b=putBoat(tboat);break;
    case 6: b=putBoat(uboat);break;
    case 7: b=putBoat(vboat);break;
    case 8: b=putBoat(eboat);break;
    case 9: b=putBoat(fboat);break;
    default: printf("NUNCA DEVE CHEGAR AQUI\n"); break;
  }
  return b;
}

Boat* putBoat(const int template[N][N]) {

  putchar('\n');
  Boat* b = newBoat();
  for(int i=0;i<N;i++) {
    for(int j=0;j<N;j++) {
      b->boat[i][j] = template[i][j];
    }
  }
  b -> lifes = sumMatrix(template);
  return b;
}

void rotateMatrix(int rotID, Boat* b) {
  int tmp[N][N];
  b -> rotID = rotID;
  for(int k=0;k<rotID;k++) {
    for(int i=0;i<N;i++) {
      for(int j=0;j<N;j++) {
        tmp[i][j] = b->boat[i][j];
      }
    }
    for(int i=0;i<N;i++) {
      for(int j=0;j<N;j++) {
        b->boat[i][j]=tmp[j][4-i];
      }
    }
  }
}

int sumMatrix(const int m[N][N]) {
  int sum = 0;
  for(int i=0;i<N;i++) {
    for(int j=0;j<N;j++) {
      sum= sum + m[i][j];
    }
  }
  return sum;
}

void printBoat(Boat*b) {
  putchar('\n');
  for(int i=0;i<N;i++) {
    for(int j=0;j<N;j++) {
      if (b->boat[i][j] == 1) putchar('X'); else putchar('.');
      putchar(' ');
    }
    putchar('\n');
  }
}
