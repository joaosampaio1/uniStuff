#include "point.h"
#include "boat.h"
#include "map.h"
#include "quadtree.h"
#include "visual.h"
#include "setup.h"
#include "player.h"

#include <stdlib.h>

Player* newPlayer(CustomSetup* c) {
  Player* p = (Player *) malloc(sizeof(Player));
  Map* m = newMap(c->mapSize);
  p -> map = m;
  return p;
}

PlayerQT* newPlayerQT(CustomSetup* c) {
  PlayerQT* p = (PlayerQT *) malloc(sizeof(PlayerQT));
  QD_NODE* qd = newQuadtree(c->mapSize);
  p -> qtree = qd;
  return p;
}