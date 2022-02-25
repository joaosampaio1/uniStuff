#include <stdio.h>
#include <getopt.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

#include "point.h"
#include "boat.h"
#include "map.h"
#include "quadtree.h"
#include "visual.h"
#include "setup.h"
#include "player.h"

#define NUMEROMAXBOAT 64

Options* readInputGame(int argc, char** argv){

  int opt;
  Options* o = newOptions();
  while((opt = getopt(argc, argv, ":rq")) != -1){
    switch(opt){
    case 'r':
      o->optionR = 1;
      break;
    case 'q':
      o->optionQ = 1;
      break;
    default:
      break;	
    }
  }

  return o;
}

int turn(Map* m, int mapSize) {
	int x = -3343;
	int y = -3433;
	int xBoat;
	int yBoat;
	Boat* b;

	do {
		if (x != -3343 && y != -3433) printf("Posição Inválida\n");
		printf("(linha, coluna)\n");
		scanf("%d%d", &x, &y);
	} while (x < mapSize && x > 0 && y < mapSize && y > 0 && m -> field[x][y] -> value > 1);
	b = m -> field[x][y] -> boatPointer;
	if (b!=NULL) {
		xBoat = b -> p ->x;
		yBoat = b -> p-> y;
		m -> field[x][y] -> value = 3;
		b -> boat[x-xBoat][y-yBoat] = 3;
		b -> boat[x-xBoat][y-yBoat] = 3;
		b -> lifes = b -> lifes - 1;
		return 3;
	}
	m -> field[x][y] -> value = 2;
	return 2;
}

int turnQT(QD_NODE* qtree, int mapSize) { //copia do turn para quadtree
	int x = -3343;
	int y = -3433;
	Point* p = newPoint(0,0);
  Point* ne = newPoint(1,1);
  QD_NODE* qd;
  int size;
  if (mapSize <= 32) size = 32; else size = 64;
	Point* sw = newPoint(size,size);

	//do {
		//if (x != -3343 && y != -3433) printf("%d %d %d\n",x,y, mapSize);
		printf("(linha, coluna)\n");
		scanf("%d%d", &x, &y);
	//} while (x < mapSize && x > 0 && y < mapSize && y > 0);
	p -> x = x;
	p -> y = y;
  qd = search(qtree, p, sw,ne , size);
  if (qd == NULL) {
		//changeCellValue(qd, 2);
		return 2;
	}
	changeCellValue(qd, 3);
	return 3;
}

int main(int argc, char** argv){
	
	Options* o = readInputGame(argc, argv);
	CustomSetup* c = defineSetup(o);
	Player* p1; 
	Player* p2;
	PlayerQT* pq1;
	PlayerQT* pq2;
	if (o->optionQ == 0) {
		p1 = newPlayer(c); 
		p2 = newPlayer(c);
	}
	else {
		pq1 = newPlayerQT(c);
		pq2 = newPlayerQT(c);
	}
	int lifes1 = 0;
	int lifes2 = 0;

	//copy templates to boat
	for(int i=0;i<c->numBarcos;i++) {
		if (o->optionQ == 0) {
			p1 -> boat[i] = getBoat(c->names[i]);
			p2 -> boat[i] = getBoat(c->names[i]);
		}
		else {
			pq1 -> boat[i] = getBoat(c->names[i]);
			pq2 -> boat[i] = getBoat(c->names[i]);
		}
	}

	//colocar os barcos
	if (o->optionR == 0) printf("------Player 1, coloque seus barcos------\n");
	for (int i=0; i<c->numBarcos; i++) {
		if (o->optionQ == 0)
			readBoats(p1->map, p1->boat[i], c->mapSize, o->optionR);
		else {
			readBoatsQT(pq1->qtree, pq1->boat[i], c->mapSize, o->optionR);
		}
	}
	printf("\n\nMAPA DO PLAYER 1:\n\n");
		if (o->optionQ == 0) showTerminal(p1->map, c->mapSize); else showTerminalQD(pq1->qtree, c->mapSize);
	//cleanTerminal();


	if (o->optionR == 0) printf("------Player 2, coloque seus barcos:------\n");
	for (int i=0; i<c->numBarcos; i++) {
		if (o->optionQ == 0)
			readBoats(p2->map, p2->boat[i], c->mapSize, o->optionR);
		else
			readBoatsQT(pq2->qtree, pq2->boat[i], c->mapSize, o->optionR);
	}
	printf("\n\nMAPA DO PLAYER 2:\n\n");
		if (o->optionQ == 0) showTerminal(p2->map, c->mapSize); else showTerminalQD(pq2->qtree, c->mapSize);
	//cleanTerminal();

	//parte do jogo
	for (int i=0; i< c->numBarcos; i++) {
		if (o->optionQ == 0) lifes1 = lifes1 + p1->boat[i] -> lifes;
		else lifes1 = lifes1 + pq1->boat[i] -> lifes;
	}
	lifes2 = lifes1;
	do {
		if (o->optionQ == 0) {
			showHit(p2->map, c->mapSize);
			printf("Player 1, faça a sua jogada\n");
			if (turn(p2->map, c->mapSize) == 3) lifes2--;
		}
		else {
			showHitQD(pq2->qtree, c->mapSize);
			printf("Player 1, faça a sua jogada\n");
			if (turnQT(pq2->qtree, c->mapSize) == 3) lifes2--;
		}
		//cleanTerminal();

		if (o->optionQ == 0) {
			showHit(p1->map, c->mapSize);
			printf("Player 2, faça a sua jogada\n");
			if (turn(p1->map, c->mapSize) == 3) lifes1--;
		}
		else {
			showHitQD(pq1->qtree, c->mapSize);
			printf("Player 2, faça a sua jogada\n");
			if (turnQT(pq1->qtree, c->mapSize) == 3) lifes1--;
		}
		//cleanTerminal();
	} while(lifes1 > 0 && lifes2 > 0);

	//quem ganhou

	if (lifes1 == 0 && lifes2 == 0) printf ("\n\n\n Empate \n\n\n");
	if (lifes2 == 0 && lifes1 != 0) printf ("\n\n\n Player 1 ganhou \n\n\n");
	if (lifes1 == 0 && lifes2 != 0) printf ("\n\n\n Player 2 ganhou \n\n\n");

	return 0;
}