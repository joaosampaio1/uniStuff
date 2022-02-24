#include <bits/stdc++.h>

using namespace std;

#define MAX 140000005
#define ll long long

/*
java was slow in this problem
*/

//highway x to y
struct HW {
	int x;
	int y;

	HW(int xx, int yy) : x(xx), y(yy) {}
};

struct less_than_key
{
    inline bool operator() (const HW& struct1, const HW& struct2)
    {	
    	if (struct1.x == struct2.x) {
    		return (struct1.y < struct2.y);
    	}
        return (struct1.x < struct2.x);
    }
};

struct Bit {
	//bittree struct
	int tree[MAX];
	int MaxIdx;

	Bit(int MaxIdxx) : MaxIdx(MaxIdxx)  {
	}

	int read(int idx) {
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

	ll solve(int k, vector<HW> a) {
		//this solution was found on http://bitdevu.blogspot.com/
		ll ans = 0;
		int j;
		for (int i=k;i>=1;i--) {
			for (j=i;j>=i && a[j-1].x==a[i-1].x;j--) ans += read(a[j-1].y-1);
			for (j=i;j>=i && a[j-1].x==a[i-1].x;j--) update(a[j-1].y,1);
			i=j+1;
		}
		return ans;
	}

};

int main() {
		std::ios::sync_with_stdio(false); //cin is slow
		int t, k, n ,m, v1, v2;
		vector <HW> vec;

		cin>>t;
		for (int l=0;l<t;l++) {
			cin>>n;
			cin>>m;
			cin>>k;
			Bit* b = new Bit(m+1);
			vec.clear();			
			for (int i=1;i<=k;i++) {
				cin>>v1;
				cin>>v2;
				vec.push_back(HW(v1,v2));
			}
			sort(vec.begin(), vec.end(), less_than_key());
			cout << "Test case "<<(l+1)<<": "<<b->solve(k, vec)<<"\n";
		}
		return 0;
	}