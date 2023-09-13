#include <bits/stdc++.h>
using namespace std;

struct Edge {
    int src, dest, weight;
};

struct Subset {
    int parent, rank;
};

bool compedge(const Edge& a, const Edge& b) {
    return a.weight < b.weight;
}

int finsub(vector<Subset>& subsets, int i) {
    if (subsets[i].parent != i)
        subsets[i].parent = finsub(subsets, subsets[i].parent);
    return subsets[i].parent;
}

void unionsubs(vector<Subset>& subsets, int x, int y) {
    int xroot = finsub(subsets, x);
    int yroot = finsub(subsets, y);
    if (subsets[xroot].rank < subsets[yroot].rank)
        subsets[xroot].parent = yroot;
    else if (subsets[xroot].rank > subsets[yroot].rank)
        subsets[yroot].parent = xroot;
    else {
        subsets[yroot].parent = xroot;
        subsets[xroot].rank++;
    }
}

vector<Edge> kruskalMST(vector<Edge>& edges, int V) {
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
        int srcParent = finsub(subsets, nextEdge.src);
        int destParent = finsub(subsets, nextEdge.dest);

        if (srcParent != destParent) {
            result.push_back(nextEdge);
            unionsubs(subsets, srcParent, destParent);
            edgeCount++;
        }
    }

    return result;
}

void printMST(const vector<Edge>& MST) {
    cout << "Edges in the Minimum Spanning Tree:" << endl;
    for (const Edge& edge : MST) {
        cout << edge.src << " - " << edge.dest << " (weight: " << edge.weight << ")" << endl;
    }
}

int main() {
    ifstream fin("input.txt");
    if (!fin) {
        cout << "Error opening the file." << endl;
        return 1;
    }

    int V, E;
    fin >> V >> E;

    vector<Edge> edges;
    for (int i = 0; i < E; i++) {
        Edge edge;
        fin >> edge.src >> edge.dest >> edge.weight;
        edges.push_back(edge);
    }

    fin.close();

    vector<Edge> MST = kruskalMST(edges, V);
    printMST(MST);

    return 0;
}
