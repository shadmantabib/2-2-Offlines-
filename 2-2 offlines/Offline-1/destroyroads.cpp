
#include <bits/stdc++.h>
using namespace std;

typedef pair<int, int> iPair;

class Graph
{
	int V;
	list<int> *adj;
	vector<pair<int, iPair>> edges;
	void DFS(int v, bool visited[]);

public:
	Graph(int V);

	void addEdge(int u, int v, int w);

	bool isConnected();

	void reverseDeleteMST();
};

Graph::Graph(int V)
{
	this->V = V;
	adj = new list<int>[V];
}

void Graph::addEdge(int u, int v, int w)
{
	adj[u].push_back(v);
	adj[v].push_back(u);
	edges.push_back({w, {u, v}});
}

void Graph::DFS(int v, bool visited[])
{

	visited[v] = true;

	list<int>::iterator i;
	for (i = adj[v].begin(); i != adj[v].end(); ++i)
		if (!visited[*i])
			DFS(*i, visited);
}

bool Graph::isConnected()
{
	bool visited[V];
	memset(visited, false, sizeof(visited));

	DFS(0, visited);

	for (int i = 1; i < V; i++)
		if (visited[i] == false)
			return false;

	return true;
}

void Graph::reverseDeleteMST()
{

	int mst_wt = 0;

	cout << "Edges in MST\n";

	// vector<int>trace;
	int maxc = 0;

	for (int i = edges.size() - 1; i >= 0; i--)
	{
		set<int> mySet;
		cout << "tracing" << endl;

		int u = edges[i].second.first;
		int v = edges[i].second.second;
		// cout << "edges " << edges.size() << endl;

		adj[u].remove(v);
		adj[v].remove(u);

		// cout << "edges " << edges.size() << endl;

		
		vector<pair<int, pair<int, int>>> modifiedEdges = edges;
		
		modifiedEdges.erase(modifiedEdges.begin() + i);
		edges= modifiedEdges;

		if (isConnected())
		{
			for (auto &e : modifiedEdges)
			{
				if (e.first == 1 || e.first == 2 || e.first == 3)
				{
					cout << e.first << " ";
					mySet.insert(e.first);
				}
			}
			if (mySet.size() == 3)
			{
				maxc++;
				cout << "edge decremented " << maxc << endl;
			}
		}
		else
		{
			continue;
		}
	}

	if (maxc > 0)
	{
		cout << "Total count: " << maxc << endl;
	}
	else
	{
		cout << -1 << endl;
	}
}

int main()
{

	ifstream finp("inputs.txt");

	int n, m;
	finp >> n >> m;
	cout << n << " " << m << endl;
	Graph g(n);

	for (int i = 0; i < m; ++i)
	{

		int u, v, weight;
		finp >> u >> v >> weight;
		u = u - 1;
		v = v - 1;
		cout << "pip" << endl;
		g.addEdge(u, v, weight);
	}

	finp.close();
	g.reverseDeleteMST();

	return 0;
}
