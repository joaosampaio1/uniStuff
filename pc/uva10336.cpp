#include <bits/stdc++.h>

#define MAX 10005

using namespace std;

struct Letters {
	//i store the letter itself and how many times the state occurs
	char ch;
	int count;

	Letters(char chh) : ch(chh) {
		count=0;
	}

	//void incrCount() {count++;}
	char getCh() {return ch;}
	int getCount() {return count;}

};

bool visitado[MAX][MAX];
char states[MAX][MAX];
int t,l,c;


void printArray() { //debug
	for (int i=0;i<l;i++) {
		for (int j=0;j<c;j++) {
			cout<<visitado[i][j]<<" ";
		}
		cout<<endl;
	}
}

void searchIncrCount(char ch, vector<Letters> &v) { //searches for ch and increases count
	//cout<<v.size()<<endl;
	for (Letters &letters : v) {
		//cout<<"testin "<<ch<<endl;
		if (letters.getCh()==ch) {	
			letters.count=letters.count+1;
			//cout<<"increasing "<<ch<<" to "<<letters.getCount()<<endl;
		}
	}
}

vector<Letters> resetVec() { //vec = <a,b,c...,z>
	vector<Letters> v;
	for(int i=0;i<26;i++) {
		//cout<<"adding "<<char('a'+i)<<endl;
		v.push_back(Letters(char('a'+i)));
	}
	return v;
}


bool compare(Letters l1, Letters l2){ //sort via count and then char
	if(l1.count > l2.count) {
		return 1;
	}
	if (l1.count == l2.count) {
		if(l1.ch < l2.ch) {
			return 1;
		}
		else return 0;
	}
	return 0;
}


void dfs(int x, int y, char ch) { //search for all characters ch in matrix and mark them as visited
	if (states[x][y]!=ch) return;
	visitado[x][y]=1;
	if (x-1>=0 && !visitado[x-1][y]) dfs(x-1,y,ch);
	if (y-1>=0 && !visitado[x][y-1]) dfs(x,y-1,ch);
	if (x+1<l && !visitado[x+1][y]) dfs(x+1,y,ch);
	if (y+1<c && !visitado[x][y+1]) dfs(x,y+1,ch);
}

int main() {
	vector<Letters> v;
	char ch;
	cin>>t;	
	for (int k=0;k<t;k++) {
		memset(visitado,0,sizeof visitado);
		v=resetVec();
		//cout<<v.size()<<endl;
		cin>>l>>c;
		for (int i=0;i<l;i++) {
			for (int j=0;j<c;j++) {
				cin>>states[i][j];
			}
		}
		/*
		goes through the matrix when it finds a spot not visited it and marks the state visited (all ch with some path to ,becomes 1)
		aaaa | 0000		1111
		aabb | 0000		1100
		bbbb | 0000 =>  0000
		aaaa | 0000		0000
		aaaa | 0000		0000
		*/
		for (int i=0;i<l;i++) {
			for (int j=0;j<c;j++) {
				if (!visitado[i][j]) {
					char ch = states[i][j];
					searchIncrCount(ch, v);
					dfs(i,j,ch);
					//printArray();
					//cout<<endl;
				}
			}
		}
		sort(v.begin(),v.end(),compare); //sort to print
		cout<<"World #"<<k+1<<endl;
		for (Letters letters: v) {
			if (letters.getCount()!=0) {
				cout<<letters.getCh()<<": "<<letters.getCount()<<endl;
			}
		}
	}
}