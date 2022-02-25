#include "point.h"
#include "boat.h"
#include "map.h"
#include "quadtree.h"
#include "visual.h"
#include "setup.h"
#include "player.h"

#include <stdio.h>
#include <stdlib.h>

void showTerminal(Map* m, int sizeMap) {
	printf("\n    ");
	for (int i=1;i<=sizeMap;i++) {
		printf("%d ",i);
		if (i < 10) {putchar (' ');}
	}
	printf("\n    ");
	for (int i=1; i<=sizeMap;i++) {
		printf("___");
	}
	printf("\n");
	for (int i=1;i<=sizeMap;i++) {
		printf("%d ", i);
		if (i < 10) {putchar (' ');}
		putchar ('|');
		for (int j=1; j<=sizeMap;j++) {
			if (m -> field[i][j] -> value == 1) printf("X  ");
			if (m -> field[i][j] -> value == 0) printf(".  ");
		}
		printf("\b|\n");	
	}
	printf("   ");
	for (int i=1; i<=sizeMap;i++) {
		printf("===");
	}
	putchar('\n');	
}

void showHit(Map* m, int sizeMap) {
		printf("\n    ");
	for (int i=1;i<=sizeMap;i++) {
		printf("%d ",i);
		if (i < 10) {putchar (' ');}
	}
	printf("\n    ");
	for (int i=1; i<=sizeMap;i++) {
		printf("___");
	}
	printf("\n");
	for (int i=1;i<=sizeMap;i++) {
		printf("%d ", i);
		if (i < 10) {putchar (' ');}
		putchar ('|');
		for (int j=1; j<=sizeMap;j++) {
			switch (m -> field[i][j] -> value) {
				case 3: printf("X  "); break;
				case 2: printf("O  "); break;
				case 1: printf(".  "); break;
				case 0: printf(".  "); break;
			}
		}
		printf("\b|\n");	
	}
	printf("   ");
	for (int i=1; i<=sizeMap;i++) {
		printf("===");
	}
	putchar('\n');	
}

void cleanTerminal() {
	for (int i=0; i<200; i++) {
		printf("\n");
	}
}

void showTerminalQD(QD_NODE* quadtree, int sizeMap) {
	printf("\n    ");
	Point* p = newPoint(0,0);
	Point* ne = newPoint(1,1);
	QD_NODE* qd;
  int size;
    if (sizeMap <= 32) size = 32; else size = 64;
    	Point* sw = newPoint(size,size);

	for (int i=1;i<=sizeMap;i++) {
		printf("%d ",i);
		if (i < 10) {putchar (' ');}
	}
	printf("\n    ");
	for (int i=1; i<=sizeMap;i++) {
		printf("___");
	}
	printf("\n");
	for (int i=1;i<=sizeMap;i++) {
		printf("%d ", i);
		if (i < 10) {putchar (' ');}
		putchar ('|');
		for (int j=1; j<=sizeMap;j++) {
			p->x=i;
			p->y=j;
			qd = search(quadtree, p, sw,ne, size);
			if (qd == NULL) printf(".  ");
			else
			if (qd -> type == QDNODE) printf(".  "); else printf("X  ");
		}
		printf("\b|\n");	
	}
	printf("   ");
	for (int i=1; i<=sizeMap;i++) {
		printf("===");
	}
	putchar('\n');
	free(sw);
	free(p);	
	free(qd);
}

void showHitQD(QD_NODE* quadtree, int sizeMap) {
	Point* p = newPoint(0,0);
	Point* ne = newPoint(1,1);
	QD_NODE* qd;
	int size;
  if (sizeMap <= 32) size = 32; else size = 64;
	Point* sw = newPoint(size,size);
	printf("\n    ");
	for (int i=1;i<=sizeMap;i++) {
		printf("%d ",i);
		if (i < 10) {putchar (' ');}
	}
	printf("\n    ");
	for (int i=1; i<=sizeMap;i++) {
		printf("___");
	}
	printf("\n");
	for (int i=1;i<=sizeMap;i++) {
		printf("%d ", i);
		if (i < 10) {putchar (' ');}
		putchar ('|');
		for (int j=1; j<=sizeMap;j++) {
			p->x=i;
			p->y=j;
			qd = search(quadtree, p, sw,ne, size);
			if (qd == NULL) printf(".  ");
			else
			if (qd -> type == QDNODE) {
				printf(".  ");
			}
			else 
			switch (qd -> node.leaf.value -> value) {
				case 3: printf("X  "); break;
				//case 2: printf("O  "); break;
				case 1: printf(".  "); break;
			}
		}
		printf("\b|\n");	
	}
	printf("   ");
	for (int i=1; i<=sizeMap;i++) {
		printf("===");
	}
	putchar('\n');
	free(sw);
	free(p);
	free(qd);	
}