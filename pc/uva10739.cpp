#include <bits/stdc++.h>

using namespace std;

#define MAX 1000

/*
complexity per test = O(s²)
s=size of string
*/
int min3(int a,int b, int c) {
	return min(min(a,b),c);
}

string invert(string s) { 
	string rs;
	int size = s.size();
	for (int i=size-1;i>=0;i--) {
		rs=rs+s.at(i);
	}
	//cout<<rs<<endl;
	return rs;
}

int solve(string s) {
	int v[MAX][MAX]; //number of operations v[size][size] = final
	string s1,s2;
	int size;

	//s1 = s.substr(0,s.size()/2);
	//s2 = s.substr(0,s.size()/2); 
	s1 = s;
	s2 = invert(s);
	size = s.size();
	v[0][0]=0;
	for (int i=1;i<=size ;i++) {
		v[i][0] = i;
		v[0][i] = i;
	}

	for (int i=1;i<=size;i++) {
		for (int j=1;j<=size;j++) {
			if (s1.at(i-1)==s2.at(j-1)) //same char in inverse s string
			v[i][j] = v[i-1][j-1];
			else v[i][j] = 1+min3(v[i-1][j-1],v[i][j-1],v[i-1][j]); //adds a change (+1) to the best previous combination of operations
		}
	}

	//debug
	/*cout<<s2<<" "<<s1<<endl;
	for (int i=0;i<=size;i++) {
		for (int j=0;j<=size;j++) {
			cout<<v[i][j]<<" ";
		}
		cout<<endl;
	}*/
	//if(s1size!=s2size) return v[s1size][s2size]-1;

	return v[size][size]/2; //we return half since we only need to change half of string to become a palindrome

}

int main() {
	int t;
	string s;
	int min, tmp;
	string s2;
	min = MAX;
	int flag,size;

	cin>>t;
	for (int k=0;k<t;k++) {
		cin>>s;
		min = solve(s);
		/*size = s.size();
		min = MAX;
		for (int i=0;i<size;i++) {
			s2=s;
			if (size%2!=0 && 1+size/2==i) flag = 0; //odd check
			else flag=1;
			tmp = flag+solve(s2.replace(i,1,""));
			if (tmp<min) min = tmp;
		}*/
		cout<<"Case "<<k+1<<": "<<min<<endl;
	}
}