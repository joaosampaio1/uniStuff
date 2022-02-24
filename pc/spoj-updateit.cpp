#include <bits/stdc++.h>

using namespace std;

#define MAX 100000
/*
complexity = O(ulogn)
n=max integer
u=number of updates
*/
struct Bit {
	//bit struct
	long long tree[MAX];
	int MaxIdx;

	Bit(int MaxIdxx) : MaxIdx(MaxIdxx)  {
	}

	int read(int idx) {
		//since this is lazy propagation, it needs to calculate the sum
		int sum = 0;
		while (idx > 0) {
			sum += tree[idx];
			idx -= (idx & -idx);
		}
		return sum;
	}

	void update(int idx, int val) {
		while (idx <= MaxIdx) {
		    tree[idx] += val;
		    idx += (idx & -idx);
		}
	}

	void scale(int min, int max, int c) {
		/*
		this funtion is a range updates
		it updates from min to max 
		adds c from min to maxidx
		then removes c from max to maxidx
		*/
   		update(min,c);
   		update(max+1, -c);	
	}

};

int main() {
	int t, n, u, q,v1,v2,v3;

		cin>>t;
		for (int l=0;l<t;l++) {
			cin>>n;
			cin>>u;
			//Bit b(n+1);
			Bit* b = new Bit(n+1);
			for (int i=0;i<u;i++) {
				cin>>v1;
				cin>>v2;
				cin>>v3;
				b->scale(v1+1,v2+1,v3);
			}
			cin>>q;
			for (int i=0;i<q;i++) {
				cin>>v1;
				cout<< b->read(v1+1);
				putchar('\n');
			}
		}	
}