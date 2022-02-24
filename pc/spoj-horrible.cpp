#include <bits/stdc++.h>

using namespace std;

#define MAX 100000000
#define ll long long
/*
complexity per test = O(ulogn)
n=max integer
u=number of updates/queries
*/
struct Bit {
	ll tree[MAX];
	ll MaxIdx;

	Bit(ll MaxIdxx) : MaxIdx(MaxIdxx)  {
	}

	ll read(ll idx) {
		ll sum = 0;
		while (idx > 0) {
			sum += tree[idx];
			idx -= (idx & -idx);
		}
		return sum;
	}

	void update(ll idx, ll val) {
		while (idx <= MaxIdx) {
		    tree[idx] += val;
		    idx += (idx & -idx);
		}
	}

	void scale(ll min, ll max, ll c, Bit* b) {
   		update(min,c);
   		update(max+1, -c);
   		b->update(min,c*(min-1));
   		b->update(max+1,-c*max);	
	}

};

//http://zobayer.blogspot.com/2013/11/various-usage-of-bit.html (III)
int main() {
	std::ios::sync_with_stdio(false);
	ll t, n, u, q,v1,v2,v3, v0;

		cin>>t;
		for (int l=0;l<t;l++) {
			cin>>n;
			cin>>u;
			Bit* b1 = new Bit(n+1);
			Bit* b2 = new Bit(n+1); //store the additive ammount
			for (int i=0;i<u;i++) {
				cin>>v0;
				cin>>v1;
				cin>>v2;
				if (v0==0) {
					cin>>v3;
					b1->scale(v1+1,v2+1,v3, b2);
				}
				else {
					v0=b1->read(v1)*v1 - b2->read(v1);
					v3=b1->read(v2+1)*(v2+1) - b2->read(v2+1);
					cout << v3-v0 << endl;
				}
			}
		}	
}