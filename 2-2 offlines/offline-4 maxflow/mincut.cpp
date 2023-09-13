#include <iostream>
#include <vector>
#include <queue>
#include <limits.h>

using namespace std;

// Data structure to represent a graph edge
struct Edge {
    int v, capacity, flow;
    Edge(int v, int capacity) : v(v), capacity(capacity), flow(0) {}
};

class Graph {
    int V; // Number of vertices
    vector<vector<Edge>> adj;

public:
    Graph(int V) : V(V), adj(V) {}

    // Function to add an edge to the graph
    void addEdge(int u, int v, int capacity) {
        Edge e1(v, capacity);
        Edge e2(u, 0); // Back edge with 0 capacity for residual flow
        adj[u].push_back(e1);
        adj[v].push_back(e2);
    }

    // Function to get the number of vertices
    int getVerticesCount() const {
        return V;
    }

    // BFS function to find if there is a path from source to sink
    bool bfs(int s, int t, vector<int>& parent) {
        vector<bool> visited(V, false);
        queue<int> q;
        q.push(s);
        visited[s] = true;
        parent[s] = -1;

        while (!q.empty()) {
            int u = q.front();
            q.pop();

            for (const Edge& e : adj[u]) {
                int v = e.v;
                if (!visited[v] && e.capacity > e.flow) {
                    q.push(v);
                    parent[v] = u;
                    visited[v] = true;
                }
            }
        }

        return visited[t];
    }

    // Ford-Fulkerson algorithm to find the maximum flow
    int fordFulkerson(int s, int t) {
        int maxFlow = 0;
        vector<int> parent(V);

        while (bfs(s, t, parent)) {
            int pathFlow = INT_MAX;
            for (int v = t; v != s; v = parent[v]) {
                int u = parent[v];
                for (const Edge& e : adj[u]) {
                    if (e.v == v) {
                        pathFlow = min(pathFlow, e.capacity - e.flow);
                        break;
                    }
                }
            }

            for (int v = t; v != s; v = parent[v]) {
                int u = parent[v];
                for (Edge& e : adj[u]) {
                    if (e.v == v) {
                        e.flow += pathFlow;
                        break;
                    }
                }

                // Update the back edge
                for (Edge& e : adj[v]) {
                    if (e.v == u) {
                        e.flow -= pathFlow;
                        break;
                    }
                }
            }

            maxFlow += pathFlow;
        }

        return maxFlow;
    }
};

// Function to find vertices of "s" and "t" parts
void findVerticesSTParts(Graph& graph, int s, vector<bool>& sPart, vector<bool>& tPart) {
    vector<int> parent(graph.getVerticesCount(), -1);
    graph.bfs(s, -1, parent);

    for (int i = 0; i < graph.getVerticesCount(); i++) {
        if (parent[i] != -1) {
            sPart[i] = true; // Vertex reachable from the source
        } else {
            tPart[i] = true; // Vertex not reachable from the source
        }
    }
}

int main() {
    int V, E;
    cout << "Enter the number of vertices and edges: ";
    cin >> V >> E;

    Graph graph(V);

    cout << "Enter the edges in the format (u, v, capacity):\n";
    int u, v, capacity;
    for (int i = 0; i < E; i++) {
        cin >> u >> v >> capacity;
        graph.addEdge(u, v, capacity);
    }

    int s = 0; // Source vertex
    int t = V - 1; // Sink vertex

    // Calculate the maximum flow in the graph
    int maxFlow = graph.fordFulkerson(s, t);

    // Find vertices of "s" and "t" parts
    vector<bool> sPart(V, false);
    vector<bool> tPart(V, false);
    findVerticesSTParts(graph, s, sPart, tPart);

    // Output the vertices of the "s" part
    cout << "Vertices in the 's' part: ";
    for (int i = 0; i < V; i++) {
        if (sPart[i]) {
            cout << i << " ";
        }
    }
    cout << endl;

    // Output the vertices of the "t" part
    cout << "Vertices in the 't' part: ";
    for (int i = 0; i < V; i++) {
        if (tPart[i]) {
            cout << i << " ";
        }
    }
    cout << endl;

    return 0;
}
