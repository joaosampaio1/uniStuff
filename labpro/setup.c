//setup do jogo
#include <stdlib.h>
#include <stdio.h>
#include <getopt.h>
#include <ctype.h>
#include <string.h>
#include <time.h>
#include "point.h"
#include "boat.h"
#include "map.h"
#include "quadtree.h"
#include "visual.h"
#include "setup.h"
#include "player.h"

#define MAXMAPSIZE 40
#define MINMAPSIZE 20

Options* newOptions() {
  Options* o = (Options *) malloc(sizeof(Options));
  o->optionR = 0;
  //o->optionW = 1;
  return o;
}

CustomSetup* newSetup(){
  CustomSetup* c = (CustomSetup*) malloc(sizeof(CustomSetup));
  return c;
}

CustomSetup* defineSetup(Options* o) {
  int randomizado = o->optionR;
  int uniqueBoatNeed = 5;
  //int wierdRules = o->optionW;
  int tmp;
  int erro;
  char str[100];
  CustomSetup* c = newSetup();

    //setup do mapa
  if (randomizado == 0) { // caso manual

    printf("Qual o tamanho do mapa?\n");
    do {
      scanf("%d", &tmp);
      if (tmp < 20 || tmp > 40) {
        erro = 1;
        printf("Tamnho do mapa errado(Hint: entre 20 e 40)\n");
      }
      else erro = 0;
    }
    while (erro == 1);
    c->mapSize = tmp;

    printf("Qual é o numero de barcos?\n");
    do {
      scanf("%d", &tmp);
      if (tmp < uniqueBoatNeed || tmp > (c->mapSize*c->mapSize / 25)) {
        erro = 1;
        printf("Numero errado de barcos (Hint: entre 5 e game_size/25)\n");
      }
      else erro = 0;
    }
    while (erro == 1);

    c->numBarcos=tmp;
    tmp = -2;
    for (int i=0; i<c->numBarcos; i++) {
      do {
        if (tmp == -2)
          printf("Qual é o nome do barco nrº %d?\n", i+1);
        else printf("Nome errado (nomes possiveis: carrier battleship cruiser destroyer tboat uboat vboat eboat fboat)\nou nao garante que exista pelo menos 5 tipos, escolha outro nome\n");
        scanf("%s", str);
       
        for (int i=0; str[i] != '\0'; i++) {
          str[i] = tolower(str[i]);
        } 
        tmp=transformBoatID(str);
        if (tmp!=-1 && bsearch(&tmp, c->names, i, sizeof(int), cmpfunc) == NULL) uniqueBoatNeed--;
      }
      while (tmp==-1 || c->numBarcos - i == uniqueBoatNeed);
      c->names[i] = tmp;
      tmp = -2;
    }
  }

  if (randomizado == 1) { //caso totalmente randomizado
  
    srand(time(0));
    c->mapSize = (rand() % MINMAPSIZE) + 20;
    c->numBarcos = rand() % (-5+c->mapSize*c->mapSize/25) + 5;
    for (int i=0; i<c->numBarcos; i++) {
      do{
        tmp = (rand() % 9) + 1;
        c->names[i] = tmp;
        if (bsearch(&tmp, c->names, i, sizeof(int), cmpfunc) == NULL) uniqueBoatNeed--;
      } while (c->numBarcos - i == uniqueBoatNeed);
    }
  }
  return c;
}

int transformBoatID(char name[]) {
  if(strcmp(name, "carrier")==0) return 1;
  if(strcmp(name, "battleship")==0) return 2;
  if(strcmp(name, "cruiser")==0) return 3;
  if(strcmp(name, "destroyer")==0) return 4;
  if(strcmp(name, "tboat")==0) return 5;
  if(strcmp(name, "uboat")==0) return 6;
  if(strcmp(name, "vboat")==0) return 7;
  if(strcmp(name, "eboat")==0) return 8;
  if(strcmp(name, "fboat")==0) return 9;
  return -1;
}

void readBoats(Map* m, Boat* b, int sizemap, int flagR){ //le as posições dos barcos dos jogadores

  int rot;
  int rotID;
  int x;
  int y;
  int tmp = 0;
  //srand(time(0));

  if (flagR == 0) {
    showTerminal(m, sizemap);
    printf("\nOnde quer colocar o barco(linha, coluna, rotaçao)\n");
    printBoat(b);
    putchar('\n');
  }

  while (tmp == 0 || rotID == -1) {
    rotID = -1;
    tmp = 0;
    if (flagR == 0) {
      scanf("%d", &x);
      scanf("%d", &y);				
			scanf("%d", &rot);    
			rotID = transformRot(rot);
    }
    else  {
      x = (rand() % sizemap) + 1;
      y = (rand() % sizemap) + 1;
      rotID = (rand() % 4);
    }
    if (rotID != -1) rotateMatrix(rotID, b);
    tmp = boatValid(x, y, m, sizemap, b);
    if (flagR == 0 && (tmp == 0 || rotID ==-1))
      fprintf(stderr, "Ponto Inválido, insira um novo ponto\n");
    if (tmp == 0 && rotID != -1) rotateMatrix(4-rotID,b);
  }
  boatToMap(x, y, m, sizemap, b);
}
  


int transformRot(int degree) {
  switch(degree) {
    case 0: return 0;
    case 90: return 1;
    case 180: return 2;
    case 270: return 3;
    default:   fprintf(stderr, "Rotaçao errada (0,90,180,270)\n"); return -1;
  }
}

int cmpfunc(const void * a, const void * b) {
   return ( *(int*)a - *(int*)b );
}

void readBoatsQT(QD_NODE* qtree, Boat* b, int sizemap, int flagR){ 

  //isto é uma copia do readboats que é chamada se for quadtree
  //funciona da mesma maneira

  int rot;
  int rotID;
  int x;
  int y;
  int tmp = 0;
  //srand(time(0));

  if (flagR == 0) {
    showTerminalQD(qtree, sizemap);
    printf("\nOnde quer colocar o barco(linha, coluna, rotaçao)\n");
    printBoat(b);
    putchar('\n');
  }

  while (tmp == 0 || rotID == -1) {
    rotID = -1;
    tmp = 0;
    if (flagR == 0) {
      scanf("%d", &x);
      scanf("%d", &y);        
      scanf("%d", &rot);    
      rotID = transformRot(rot);
    }
    else  {
      x = (rand() % sizemap) + 1;
      y = (rand() % sizemap) + 1;
      rotID = (rand() % 4);
    }
    if (rotID != -1) rotateMatrix(rotID, b);
    tmp = boatValidQT(x, y, qtree, sizemap, b);
    if (flagR == 0 && (tmp == 0 || rotID ==-1))
      fprintf(stderr, "Ponto Inválido, insira um novo ponto\n");
    if (tmp == 0 && rotID != -1) rotateMatrix(4-rotID,b);
  }
  boatToMapQT(x, y, qtree, sizemap, b);
}