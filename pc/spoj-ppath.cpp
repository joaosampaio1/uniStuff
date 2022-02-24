#include <bits/stdc++.h>

using namespace std;

#define MAX 10005
#define INF 1000000

/*
complexity O(q)
q=number of queries
this is beacuse the time bfs is limited but its faster than searching all 1000-9999
*/

//https://stackoverflow.com/questions/4424374/determining-if-a-number-is-prime
bool isPrime(int number){

    if(number < 2) return false;
    if(number == 2) return true;
    if(number % 2 == 0) return false;
    for(int i=3; (i*i)<=number; i+=2){
        if(number % i == 0 ) return false;
    }
    return true;

}

int dequeue(queue<int> &q) {
	int r = q.front();
	q.pop();
	return r;
}

void bfs(int v, int o) {
	//cout<<isPrime(1033)<<endl;
	int visited[MAX];
	queue<int> q;
	int u, tmp;
	//memset(visited, 0, sizeof visited);
	fill(visited, visited+MAX, INF);

	q.push(v);
	visited[v] = 0;
	while (!q.empty()) {
		u=dequeue(q);
		//cout<<"dequeing "<<u<<endl;
		if (u==o) {
			cout<<visited[u]<<endl;
			return;
		}

		/*
		using bfs
		i add to the queue all prime numbers (not visited) with a change of character 
		for example for the number 1009
		i add 5009, 8009 then 1109 et cetera 
		using those new numbers in queue i dequeue one and i do the same with that
		until i find the objective
		*/
		tmp=u%1000;
		for (int i=1;i<10;i++) {
			tmp=tmp+1000;
			//cout<<"testing "<<tmp <<" visited= "<<visited[tmp]<<" INF = " <<INF<<endl;
			if (isPrime(tmp) && visited[tmp] == INF) {
				visited[tmp] = visited[u]+1;
				//cout<<"queing "<<tmp<<endl;
				q.push(tmp);
			}
		}

		tmp=u%100+floor(u/1000)*1000;
		for (int i=0;i<10;i++) {
			//cout<<"testing "<<tmp <<" visited= "<<visited[tmp]<<" INF = " <<INF<<endl;
			if (isPrime(tmp) && visited[tmp] == INF) {
				visited[tmp] = visited[u]+1;
				//cout<<"queing "<<tmp<<endl;
				q.push(tmp);
			}
			tmp=tmp+100;
		}

		tmp=u%10+floor(u/100)*100;
		for (int i=0;i<10;i++) {
			//cout<<"testing "<<tmp <<" visited= "<<visited[tmp]<<" INF = " <<INF<<endl;
			if (isPrime(tmp) && visited[tmp] == INF) {
				visited[tmp] = visited[u]+1;
				//cout<<"queing "<<tmp<<endl;
				q.push(tmp);
			}
			tmp=tmp+10;
		}

		tmp=floor(u/10)*10;
		for (int i=0;i<10;i++) {
			//cout<<"testing "<<tmp <<" visited= "<<visited[tmp]<<" INF = " <<INF<<endl;
			if (isPrime(tmp) && visited[tmp] == INF) {
				visited[tmp] = visited[u]+1;
				//cout<<"queing "<<tmp<<endl;
				q.push(tmp);
			}
			tmp=tmp+1;
		}
	}
	cout<<"Impossible"<<endl;
}

int main() {

	int t,v,o;

	cin>>t;
	for (int k=0;k<t;k++) {
		cin>>v>>o;
		bfs(v,o);
	}
}