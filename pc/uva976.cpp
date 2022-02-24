#include <bits/stdc++.h>

using namespace std;

#define MAX 1005
#define INF 10000000;
int R, C, B, D;
/*
i use dfs algorithm instead of dp to solve the problem
complexity O(R*C)
R=ROWS
C=COLS
*/
using namespace std;

void fillC(int m[MAX][MAX], int c, int a, int b,int value) { //fill column from a to b with value default=1
	for (int i=a;i<b;i++) {
		m[i][c]=value;
	}
}

void printM2(bool M[MAX][MAX]) {
	 for (int i = 1; i <= R; i++) {
        for (int j = 1; j <= C; j++) {
        	cout<<M[i][j]<<" ";
        }
        cout<<endl;
    }
}

//https://www.geeksforgeeks.org/number-of-connected-components-in-a-2-d-matrix-of-strings/
//CONNECTED GRAPH
bool visited[MAX][MAX] = { 0 };
 
// Function that return true if mat[row][col]
// is valid and hasn't been visited
bool isSafe(int M[MAX][MAX], int row, int col, int c,
                                    int n, int l)
{
    // If row and column are valid and element
    // is matched and hasn't been visited then
    // the cell is safe
    //cout<<row<<" "<<col<<" "<<c<<" "<<n<<" "<<l<<" "<<M[row][col]<<endl;
    return (row >= 0 && row <= n)
           && (col >= 0 && col <= l)
           && (M[row][col] == c && !visited[row][col]);
}
 
// Function for depth first search
void DFS(int M[MAX][MAX], int row, int col, int c,
                                 int n, int l)
{
    // These arrays are used to get row and column
    // numbers of 4 neighbours of a given cell
    int rowNbr[] = { -1, 1, 0, 0 };
    int colNbr[] = { 0, 0, 1, -1 };
 
    // Mark this cell as visited
    visited[row][col] = true;
 
    // Recur for all connected neighbours
    for (int k = 0; k < 4; ++k) 
        if (isSafe(M, row + rowNbr[k],
                  col + colNbr[k], c, n, l)) {
        	
 
            DFS(M, row + rowNbr[k],
                col + colNbr[k], c, n, l);
        }
}

void f(int M[MAX][MAX])
/*
fill gaps in graph
#####		#####
#.#.#		###.#
###.. => 	###..
..... 		.....
#####		#####
*/
{
	DFS(M, 1, 1, 1, R, C);
	for (int i = 1; i <= R; i++) {
        for (int j = 1; j <= C; j++) {
        	if (visited[i][j]) {
        		fillC(M,j,1,i,1);
        	}
        }
    }
 
    memset(visited, 0, sizeof visited);
    DFS(M, R,1, 1, R, C);
    for (int i = 1; i <= R; i++) {
        for (int j = 1; j <= C; j++) {
        	if (visited[i][j]) {
        		//DFS(M, R,1, 1, R, C);
        		//cout<<i<<" "<<j<<endl;
        		fillC(M,j,i,R,1);
        	}
        }
    }
    //printM2(visited);
    memset(visited, 0, sizeof visited);
}

void printM(int M[MAX][MAX]) { //debug
	 for (int i = 1; i <= C; i++) {
        for (int j = 1; j <= B; j++) {
        	cout<<M[i][j]<<" ";
        }
        cout<<endl;
    }
}



int solve() {
	int r=R;
	int c=C;
	int b=B;
	int d=D;
	int m[MAX];
	int mat[MAX][MAX];
	int p[MAX][MAX];
	int tmp=0;
	memset(m, 0, sizeof m);
	memset(p, 0, sizeof p);
	char ch;
	for(int i=1;i<=r;i++) {
		for(int j=1;j<=c;j++) {
			cin>>ch;
			if(ch=='.') p[i][j] = 0;
			else p[i][j] = 1;
		}
	}
	f(p);
	for(int i=1;i<=r;i++) {
		for(int j=1;j<=c;j++) {
			if(p[i][j]==0) m[j]++;
		}
	}

	mat[1][1] = m[1];
	for(int i=2;i<=c;i++) {
		//cout<<m[i]<<" "<<mat[i-1][1]<<endl;
		if (m[i]<mat[i-1][1]) mat[i][1] = m[i];
		else mat[i][1] = mat[i-1][1];
	}

	for(int i=2;i<=b;i++) {
		mat[1][i] = INF;
	}

	//printArray(mat);
	//printM2(p);

	for(int i=2;i<=b;i++) {
		for(int j=2;j<=c;j++) {
			//cout<<m[j]<<" "<<mat[j-d-1][i-1]<<" "<<mat[j-1][i]<<endl;
			if (j<(d+1)*(i-1)+1) {
				mat[j][i] = INF;
			}
			else if (m[j]+mat[j-d-1][i-1]<mat[j-1][i]) {
				mat[j][i]=m[j]+mat[j-d-1][i-1];
				
			}
				else {
					mat[j][i] = mat[j-1][i];
				}

		}
	}
	//cout<<endl<<endl;
	//printM(mat);

	return mat[c][b];

}

int main() {
	while (!(cin.eof())) {
		//if (cin.peek()=="\n") break;
		cin>>R>>C>>B>>D;
		cout<<solve()<<endl;
		while(cin.peek()=='\n') {
			getchar();
		}
	}

	return 0;
}