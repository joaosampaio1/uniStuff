#ifndef PLAYER_H
#define PLAYER_H

#define NUMEROMAXBOAT 64

typedef struct {
	Map* map;
	Boat* boat[NUMEROMAXBOAT];
} Player;

typedef struct {
	QD_NODE* qtree;
	Boat* boat[NUMEROMAXBOAT];
} PlayerQT;

Player* newPlayer(CustomSetup*);
PlayerQT* newPlayerQT(CustomSetup*);

#endif