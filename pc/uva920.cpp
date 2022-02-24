#include <bits/stdc++.h>

using namespace std;

#define MAX 100005

struct Point {
	int x;
	int y;

	Point(int x, int y) {
		this->x = x;
		this->y = y;
	}

};

struct less_than_key
{
    inline bool operator() (const Point& struct1, const Point& struct2)
    {	
    	/*if (struct1.x == struct2.x) {
    		return (struct1.y < struct2.y);
    	}*/
        return (struct1.x > struct2.x);
    }
};

float lineFromPoints(Point P, Point Q, int h)
{
	//i find the f(x)=kx+b
	//from two points 
	//then return x on h=ax+b
    double a = Q.y - P.y;
    double b = P.x - Q.x;
    double c = a * (P.x) + b * (P.y);
 
 	return (c-h*b)/a;
}
int main() {
	cout << setprecision(2) << fixed;
	int t, n,x,y;
	int h;
	float sum;
	cin>>t;
	for (int i = 0; i < t; ++i)
	{
		cin>>n;
		vector<Point> vec;
		h=sum=0;
		for (int j = 0; j < n; ++j)
		{
			cin>>x>>y;
			vec.push_back(Point(x,y));
		}
		sort(vec.begin(), vec.end(), less_than_key()); //we need to sort the mountains
		for (int j = 0; j < n; ++j)
		{	
			//cout<<vec[j+1].x<< " "<<vec[j].x<< " "<<vec[j+1].y<< " "<<vec[j].y<<endl;

			if (vec[j].y>h) {
				sum=sum+sqrt(pow(vec[j].x-lineFromPoints(vec[j],vec[j-1],h), 2) + pow(vec[j].y-h, 2)); //euclidean 
				h=vec[j].y;
			}
		}
		cout<<sum<<endl;
	}
}