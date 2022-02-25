#ifndef QUADTREE_H
#define QUADTREE_H


typedef enum { QDNODE, QDLEAF} QD_TNODE;

typedef struct QD_Node_ {
  QD_TNODE  type;    // defines the type of node (internal node or leaf)
                                       
  union {

    struct QD_Node_ *quadrants[4];    // internal node                                                    

    struct {

      Cell* value;   // VALUE --  board cell ou pointer para board cell?                                  

      Point* p;    // coords of the board cell                                                             

    } leaf;     //  almost a board cell together with its coordinates

  } node;

} QD_NODE;

QD_NODE* newQuadtree(int);
int insertQt(QD_NODE*, QD_NODE*, Point*, Point*, int);
int insideQt(Point*, QD_NODE*);
QD_NODE* search(QD_NODE*, Point*, Point*, Point*, int);
int changeCellValue(QD_NODE*, int);
QD_NODE* newQuadleaf(Cell*, Point*);

int boatValidQT(int,int,QD_NODE*, int, Boat*); //MAP.H FUNÇÃO NAO QT
void boatToMapQT(int,int,QD_NODE*, int, Boat*); //MAP.H FUNÇÃO NAO QT


#endif