//wiki https://pt.wikipedia.org/wiki/Algoritmo_de_Dijkstra

#include <bits/stdc++.h>
#define INFINITO 10000000

using namespace std;

int t,l,c,inicio,tmp;

/*
this exercise is to use dijkstra
each cell in matrix is a node
we simply need to find the min path to 
bottom right corner 

complexity = O(V+ElogV) = dijstrka using priority queue
V= vertices
E= edges

*/

class Grafo
{
private:
	int V; // número de vértices

	// ponteiro para um array contendo as listas de adjacências
	list<pair<int, int> > * adj;

public:

	// construtor
	Grafo(int V)
	{
		this->V = V; // atribui o número de vértices

		/*
			cria as listas onde cada lista é uma lista de pairs
			onde cada pair é formado pelo vértice destino e o custo
		*/
		adj = new list<pair<int, int> >[V];
	}

	// adiciona uma aresta ao grafo de v1 à v2
	void addAresta(int v1, int v2, int custo)
	{
		adj[v1].push_back(make_pair(v2, custo));
	}

	// algoritmo de Dijkstra
	int dijkstra(int orig, int dest, int inicio)
	{
		// vetor de distâncias
		int dist[V];

		/*
		   vetor de visitados serve para caso o vértice já tenha sido
		   expandido (visitado), não expandir mais
		*/
		int visitados[V];

		// fila de prioridades de pair (distancia, vértice)
		priority_queue < pair<int, int>,
					   vector<pair<int, int> >, greater<pair<int, int> > > pq;

		// inicia o vetor de distâncias e visitados
		for(int i = 0; i < V; i++)
		{
			dist[i] = INFINITO;
			visitados[i] = false;
		}

		// a distância de orig para orig é 0
		dist[orig] = inicio;

		// insere na fila
		pq.push(make_pair(dist[orig], orig));

		// loop do algoritmo
		while(!pq.empty())
		{
			pair<int, int> p = pq.top(); // extrai o pair do topo
			int u = p.second; // obtém o vértice do pair
			pq.pop(); // remove da fila

			// verifica se o vértice não foi expandido
			if(visitados[u] == false)
			{
				// marca como visitado
				visitados[u] = true;

				list<pair<int, int> >::iterator it;

				// percorre os vértices "v" adjacentes de "u"
				for(it = adj[u].begin(); it != adj[u].end(); it++)
				{
					// obtém o vértice adjacente e o custo da aresta
					int v = it->first;
					int custo_aresta = it->second;

					// relaxamento (u, v)
					if(dist[v] > (dist[u] + custo_aresta))
					{
						// atualiza a distância de "v" e insere na fila
						dist[v] = dist[u] + custo_aresta;
						pq.push(make_pair(dist[v], v));
					}
				}
			}
		}
		/*for (int i=0;i<=l*c-1;i++) {
			cout<< "dist["<<i<<"] is "<<dist[i]<<endl;
		}*/
		// retorna a distância mínima até o destino
		return dist[dest];
	}
};

int main()
{	
	
	cin>>t;
	for (int i=0;i<t;i++) {
		cin>>l>>c;
		Grafo g(l*c);
		//cout<<l<<" "<<c<<endl;
		int mat[1000][1000];
		memset(mat,0,sizeof (mat));
		for (int j=0;j<l;j++) {
			for (int k=0;k<c;k++) {
				cin>>tmp;
				mat[j][k]=tmp;
			}
		}
		inicio=mat[0][0];
		for (int j=1;j<c;j++) {
			//cin>>tmp;
			//cout<< "I ADD "<<tmp<<" FROM "<<j<<" TO "<<j-1<<endl;
			g.addAresta(j-1,j,mat[0][j]);
			g.addAresta(j,j-1,mat[0][j-1]);
		}
		//add edges between the cells of the matrix
		for (int j=1;j<l;j++) {
			for (int k=0;k<c;k++) {
				//cin>>tmp;
				if (k>0) {
					g.addAresta(k-1+j*c,k+j*c,mat[j][k]);
					g.addAresta(k+j*c,k-1+j*c,mat[j][k-1]);
					//cout<< "I ADD "<<tmp<<" FROM "<<k-1+j*c<<" TO "<<k+j*c<<endl;
				}
				g.addAresta(k+(j-1)*c,k+j*c,mat[j][k]);
				g.addAresta(k+j*c,k+(j-1)*c,mat[j-1][k]);
				//cout<< "I ADD "<<tmp<<" FROM "<<k+(j-1)*c<<" TO "<<k+j*c<<endl;
			}
		}

		cout << g.dijkstra(0, l*c-1,inicio) << endl;

	}
	
	return 0;
}