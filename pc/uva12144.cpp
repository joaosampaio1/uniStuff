//wiki https://pt.wikipedia.org/wiki/Algoritmo_de_Dijkstra

#include <bits/stdc++.h>
#define INFINITO 10000000

using namespace std;

int n, m;

/*
complexity = dijkstra using priority queue = O (v*elogv)
e=number of edges
v=number of vertices
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

	void removeAresta(int v1, int v2) {
		for (pair<int,int> p : adj[v1]) {
			if (p.first == v2) {
				adj[v1].remove(p);
				break; // WE ASSUME ONLY ONE PATH FOR V1 TO V2
			}
		}
	}

	// algoritmo de Dijkstra
	int dijkstra(int orig, int dest)
	{
		// vetor de distâncias
		int dist[V];
		vector<vector<int>> prev(V);


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
		dist[orig] = 0;
		//prev[orig] = vector<int>(V);

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
					if(dist[v] == (dist[u] + custo_aresta)) {
						prev[v].push_back(u);
						//cout<<"pushing "<<u<<" to "<<v<<endl;

					}
					if(dist[v] > (dist[u] + custo_aresta))
					{
						// atualiza a distância de "v" e insere na fila
						prev[v] = vector<int>(V);
						prev[v].push_back(u);
						//cout<<"new and pushing "<<u<<" to "<<v<<endl;
						dist[v] = dist[u] + custo_aresta;
						pq.push(make_pair(dist[v], v));
					}
				}
			}
		}
		/*
		remover as arestas dos caminhos mais curtos
		*/
		int v, u;
		v=dest;
		queue<int> q;
		q.push(v);
		while (!q.empty()) {
		

			v = q.front();
			q.pop();
			vector<int> vec= prev[v];
			//cout<<"top "<<v<<endl;

			for (int u: vec) {
				//cout<<"removing "<<u<<" to "<<v<<endl;
				removeAresta(u,v);
				if (u!=orig) {
					//cout<<"adding "<<u<<endl;
					q.push(u);
				}
			}
		}
		// retorna a distância mínima até o destino
		return dist[dest];
	}
};

int main()
{	
	while (true ) {
		int start, end,v1,v2,v3, min,path;
		cin>>n>>m;
		if (n==0 && m==0) return 0;
		cin>>start>>end;
		Grafo g(n+1);

		for (int i=0;i<m;i++) {
			cin>>v1>>v2>>v3;
			g.addAresta(v1+1,v2+1,v3);
		}
		g.dijkstra(start+1, end+1);
		path=g.dijkstra(start+1, end+1);
		if (path==INFINITO) {
			cout<<-1<<endl;
			
		}
		else cout<<path<<endl;
	}
	
	return 0;
}