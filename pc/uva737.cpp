#include <bits/stdc++.h>

using namespace std;

#define MAX 100005

struct Point {
	int x;
	int y;
	int z;

	Point(int x, int y, int z) {
		this->x = x;
		this->y = y;
		this->z = z;
	}

};

struct Cube {
	Point* p1;
	Point* p2;

	Cube(int x, int y, int z, int e) {
		p1 = new Point(x,y,z);
		p2 = new Point(x+e,y+e,z+e);
	}
	Cube(Point* p1, Point* p2) {
		this->p1 = p1;
		this->p2 = p2;
	}

};

Cube* intersect(Cube* c1, Cube* c2) {
	int x1 = max(c1->p1->x, c2->p1->x);
	int x2 = min(c1->p2->x, c2->p2->x);
	int y1 = max(c1->p1->y, c2->p1->y);
	int y2 = min(c1->p2->y, c2->p2->y);
	int z1 = max(c1->p1->z, c2->p1->z);
	int z2 = min(c1->p2->z, c2->p2->z);
	if (x1<x2 && y1<y2 && z1<z2) {
		Point* p1 = new Point(x1,y1,z1); 
		Point* p2 = new Point(x2,y2,z2); 
		return new Cube(p1,p2);
	}
	return NULL;
}

int volume(Cube* c) {
	return (c->p2->x-c->p1->x)*(c->p2->y-c->p1->y)*(c->p2->z-c->p1->z);
}

int main() {
	while (true) {
		int n,x,y,z,e;
		cin>>n;
		if (n==0) break;
		cin>>x>>y>>z>>e;
		int flag=0;
		Cube* c1 = new Cube(x,y,z,e);
		for (int i = 0; i < n-1; ++i)
		{
			cin>>x>>y>>z>>e;
			Cube* c2 = new Cube(x,y,z,e);
			if (flag!=1)c1=intersect(c1,c2);
			if (c1==NULL)
			{
				flag=1;
			}
		}
		if (flag==1)
		 {
		 	cout<<0<<endl;
		 } 
		 else
		cout<<volume(c1)<<endl;
	}
}
