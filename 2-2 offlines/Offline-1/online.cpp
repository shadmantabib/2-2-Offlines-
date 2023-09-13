#include<bits/stdc++.h>
using namespace std;
ifstream fin("online.txt");
ofstream fout("outputprim.txt");
ofstream fout2("outputkruskal.txt");

typedef pair<int, int> ip; 

struct Edge {
    int src, dest;
    double weight;
};

struct Subset {
    int parent, rank;
};

bool compedge(const Edge& a, const Edge& b) {
    return a.weight < b.weight;
}

int findsub(vector<Subset>& subsets, int i) {
    if (subsets[i].parent != i)
        subsets[i].parent = findsub(subsets, subsets[i].parent);
    return subsets[i].parent;
}

void unionSubsets(vector<Subset>& subsets, int x, int y) {
    int xroot = findsub(subsets, x);
    int yroot = findsub(subsets, y);
    if (subsets[xroot].rank < subsets[yroot].rank)
        subsets[xroot].parent = yroot;
    else if (subsets[xroot].rank > subsets[yroot].rank)
        subsets[yroot].parent = xroot;
    else {
        subsets[yroot].parent = xroot;
        subsets[xroot].rank++;
    }
}

vector<Edge> krus(vector<Edge>& edges, int V) {
    vector<Edge> result;
    
    vector<Subset> subsets(V);
    for (int i = 0; i < V; i++) {
        subsets[i].parent = i;
        subsets[i].rank = 0;
    }

    sort(edges.begin(), edges.end(), compedge);

    int edgeCount = 0;
    int index = 0;
    while (edgeCount < V - 1 && index < edges.size()) {
        Edge nextEdge = edges[index++];
        int srcParent = findsub(subsets, nextEdge.src);
        int destParent = findsub(subsets, nextEdge.dest);

        if (srcParent != destParent) {
            result.push_back(nextEdge);
            unionSubsets(subsets, srcParent, destParent);
            edgeCount++;
        }
    }

    return result;
}
double prim(const vector<vector<pair<int, double>>>& graph, int n, vector<int>& parent) {
    double totalWeight = 0;

    vector<double> disc(n, INT_MAX); 
    vector<bool> visited(n, false);   

    priority_queue<pair<double, int>, vector<pair<double, int>>, greater<pair<double, int>>> pq; 
    pq.push({0.0, 0}); 

    while (!pq.empty()) {
        int u = pq.top().second;
        cout << "hello " << u << endl;
        double weight = pq.top().first;
        pq.pop();

        if (visited[u]) {
            continue;
        }

        visited[u] = true;
        totalWeight += weight;

        for(const pair<int, double>& nb : graph[u]) {
            int v = nb.first;
            double ew = nb.second;
            if(!visited[v] && ew < disc[v]) {
                disc[v] = ew;
                pq.push({disc[v], v});
                parent[v] = u;
            }
        }
    }

    return totalWeight;
}

void printMST(const vector<int>& parent, const vector<vector<pair<int, double>>>& graph) {
    int n = parent.size();
    cout << "Edges in the Minimum Spanning Tree using Prim:" << endl;
    for (int i = 1; i < n; ++i) {
        int u = parent[i];
        int v = i;
        double weight = 0; 
        for (const ip& neighbor : graph[u]) {
            if (neighbor.first == v) {
                weight = neighbor.second;
                break;
            }
        }
        cout << u << " - " << v << endl;
        fout << u << " - " << v << endl;
    }
}
void printMST1(const vector<Edge>& MST) {
    cout << "Edges in the Minimum Spanning Tree using Kruskal:" << endl;
    for (const Edge& edge : MST) {
        cout << edge.src << " - " << edge.dest  << endl;
        fout2 << edge.src << " - " << edge.dest << endl;
    }
}

int main() {
   
    if (!fin) {
        cout<< "Error" << endl;
        return 1;
    }

    int n, m;
    double w;
    fin >> n >> m>>w;

    vector<vector<pair<int, double>>> graph(n);
    vector<Edge> edges;

    for (int i = 0; i < m; ++i) {
        Edge edge;
        int u, v;
        double weight;
        fin >> u >> v >> weight;
        edge.src=u;
        edge.dest=v;
        edge.weight=min(weight,w);
        edges.push_back(edge);
        graph[u].push_back({v, weight});
        graph[v].push_back({u, weight});
    }

    fin.close();

    vector<int> parent(n, -1);
    double totalWeight = prim(graph, n, parent);
    vector<Edge> MST = krus(edges, n);
    double totalWeight2 = 0;
    for (const Edge& edge : MST) {
        totalWeight2 += edge.weight;
    }
    cout << "Total weight = " << totalWeight2<< endl;
    fout << "Total weight = " << totalWeight2<< endl;
    
    printMST1(MST);


  
}
