#ifndef SETUP_H
#define SETUP_H

#define NUMBERBOATMAX 64

typedef struct{

  int optionR;
  int optionQ;  

} Options;

typedef struct{

	int mapSize;
	int numBarcos;
	int names[NUMBERBOATMAX];

} CustomSetup;

//setup do jogo

Options* newOptions();
CustomSetup* defineSetup(Options*);
CustomSetup* newSetup();
int transformBoatID(char*);
void readBoats(Map*,Boat*, int, int);
int transformRot(int); // transforma a rotaçao no ID
void readBoatsQT(QD_NODE*, Boat*, int, int);
int cmpfunc(const void * a, const void * b); //????

#endif