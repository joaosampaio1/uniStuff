/*
complexity per case = floydwarshall algorithm = O(n³)
n = number of currencies
*/

//https://www.geeksforgeeks.org/floyd-warshall-algorithm-dp-16/

// C++ Program for Floyd Warshall Algorithm
#include <bits/stdc++.h>
using namespace std;
 
// Number of vertices in the graph
#define V 35
 
/* Define Infinite as a large enough
value.This value will be used for
vertices not connected to each other */
#define INF -99999
int currencies;
int ca=1;
 
// A function to print the solution matrix
void printSolution(float dist[][V]);
void canScam(float dist[][V]);

 
// Solves the all-pairs shortest path
// problem using Floyd Warshall algorithm
void floydWarshall(float graph[][V])
{
    /* dist[][] will be the output matrix
    that will finally have the shortest
    distances between every pair of vertices */
    float dist[V][V];
    int i, j, k;
 
    /* Initialize the solution matrix same
    as input graph matrix. Or we can say
    the initial values of shortest distances
    are based on shortest paths considering
    no intermediate vertex. */
    for (i = 0; i < V; i++)
        for (j = 0; j < V; j++)
            dist[i][j] = graph[i][j];
 
    /* Add all vertices one by one to
    the set of intermediate vertices.
    ---> Before start of an iteration,
    we have shortest distances between all
    pairs of vertices such that the
    shortest distances consider only the
    vertices in set {0, 1, 2, .. k-1} as
    intermediate vertices.
    ----> After the end of an iteration,
    vertex no. k is added to the set of
    intermediate vertices and the set becomes {0, 1, 2, ..
    k} */
    for (k = 0; k < V; k++) {
        // Pick all vertices as source one by one
        for (i = 0; i < V; i++) {
            // Pick all vertices as destination for the
            // above picked source
            for (j = 0; j < V; j++) {
                // If vertex k is on the shortest path from
                // i to j, then update the value of
                // dist[i][j]
                if (dist[i][j] < (dist[i][k] * dist[k][j])
                    && (dist[k][j] != INF
                        && dist[i][k] != INF)) {
                        dist[i][j] = dist[i][k] * dist[k][j];
                    //cout<<i<<" "<<j<<" "<<k<<" "<<endl;
                }
            }
        }
    }
 
    // Print the shortest distance matrix
    //printSolution(dist);
    canScam(dist);
}

void canScam(float dist[][V]) { //if its possible to arbitrage
    for (int i = 0; i < currencies; i++) {
        for (int j = 0; j < currencies; j++) {
            if (dist[i][j]*dist[j][i]>1) {
                cout<<"Case "<<ca<<": Yes"<<endl;
                return;
            }
        }
    }
    cout<<"Case "<<ca<<": No"<<endl;
    return;
} 
/* A utility function to print solution */
void printSolution(float dist[][V])
{
    cout << "The following matrix shows the shortest "
            "distances"
            " between every pair of vertices \n";
    for (int i = 0; i < currencies; i++) {
        for (int j = 0; j < currencies; j++) {
            if (dist[i][j] == INF)
                cout << "INF"
                     << " ";
            else
                cout << dist[i][j] << " ";
        }
        cout << endl;
    }
}
int findd(string coin[], string s, int size) { //where is s (currency)?
    for (int i=0;i<size;i++) {
        if (coin[i].compare(s)==0) return i;
    }
    return -1; //shouldnt get here
} 
// Driver code
int main()
{
    //cin>>n;
    int exchange;
    //for (int i=0;i<n;i++) {
    while (true) {
        cin>>currencies;
        if (currencies==0) return 0;
        string coin[V];
        string s,s2;
        for (int j=0;j<currencies;j++) {
            cin>>s;
            coin[j]=s;
            //cout<<j<<" "<<s<<endl;
        }
        cin>>exchange;
        float rate;
        float graph[V][V];
        for (int j=0;j<V;j++) {
            for (int k=0;k<V;k++) {
                graph[j][k] = INF;
                if (j==k) graph[j][k] = 0;
            }
        }
        for (int j=0;j<exchange;j++) {
            cin>>s;
            cin>>rate;
            cin>>s2;
            int p1 = findd (coin,s,currencies);
            int p2 = findd (coin,s2,currencies);
            //cout<<p1<<" "<<p2<<endl;

            graph[p1][p2] = rate;
        }

        /*int graph[V][V] = { { 0, 5, INF, 10 },
                        { INF, 0, 3, INF },
                        { INF, INF, 0, 1 },
                        { INF, INF, INF, 0 } };*/
    
 
    // Print the solution
        floydWarshall(graph);
        ca++;
    }
    return 0;
}