#include <bits/stdc++.h>

using namespace std;

/*
complexity O(s*z)
s=size of string 1
z=size of string 2

*/
#define MAX 1000
#define ll long long

struct Node{
	ll lenght;
	string s;

	Node(ll lenghtt, string ss) : lenght(lenghtt), s(ss)  {}

	ll getLenght() {return lenght;}
	string getS() {return s;}
};

int main() {

	std::ios::sync_with_stdio(false);
	int k,t1,t2;
	string s;
	while (!cin.eof() ) {
		
		Node* v[MAX][MAX];
		v[0][0] = new Node(0,""); //dummy
		string sv1[MAX];
		string sv2[MAX];
		k = 1;
		t1 = 1;
		t2 = 1;
		cin>>s;
		//if (s.compare("\n")) return 0;
		while (s.compare("#")!=0) { //add strings to sv1
			v[k][0]=new Node(0,"");
			sv1[k] = s+" ";
			cin>>s;
			t1++; k++;
		}

		k = 1;
		cin>>s;
		while (s.compare("#")!=0) { //add strings to sv2
			v[0][k]=new Node(0,"");
			sv2[k] = s+" ";
			cin>>s;
			t2++; k++;
		}
		
		//meat of alghorithm
		for (int i=1;i<t1;i++) {
			for (int j=1;j<t2;j++) {
				if (sv2[j]==sv1[i]) { //if equal adds a word to matrix v
					v[i][j] = new Node(v[i-1][j-1]->getLenght()+1,
										v[i-1][j-1]->getS()+sv1[i]);
				}
				else { //where does bigger lenght come from in the matrix, top or left
					if (v[i-1][j]->getLenght()>v[i][j-1]->getLenght())
					v[i][j] = new Node(max(v[i-1][j]->getLenght(),v[i][j-1]->getLenght()),
										v[i-1][j]->getS());
					else {
						v[i][j] = new Node(max(v[i-1][j]->getLenght(),v[i][j-1]->getLenght()),
											v[i][j-1]->getS());
					}
				}
			}
		}
		string ss=v[t1-1][t2-1]->getS();
		if(ss!="") {
			ss.replace(ss.end()-1,ss.end(),"");
			cout << ss<<endl;
		}
	}
}