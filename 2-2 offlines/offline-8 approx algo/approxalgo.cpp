#include <bits/stdc++.h>

using namespace std;

class Graph {
    int V;
    vector<vector<int>> Mat;

public:
    Graph(int vert) : V(vert) {
        Mat.resize(V, vector<int>(V, 0));
    }
    void addEdge(int u, int v, int weight) {
        if (u >= 0 && u < V && v >= 0 && v < V) {
            Mat[u][v] = weight;
            Mat[v][u] = weight;
        }
    }
    int getVertices() const {
        return V;
    }
    void print() {
        for (int i = 0; i < V; ++i) {
            for (int j = 0; j < V; ++j) {
                cout << Mat[i][j] << " ";
            }
            cout << endl;
        }
    }
    int getEdge(int u, int v) {
        if (u >= 0 && u < V && v >= 0 && v < V) {
            return Mat[u][v];
        } else {
            return -1; // Return a negative value to indicate an invalid edge
        }
    }
};

Graph Create_Random_Graph(int V) {
    if (V < 2) {
        cout << "invalid graph" << endl;
    }

    Graph graph(V);

    srand(time(nullptr));

    for (int u = 0; u < V; ++u) {
        for (int v = u + 1; v < V; ++v) {
            int weight = rand() % 151 + 50;
            graph.addEdge(u, v, weight);
        }
    }

    return graph;
}

int solve(int i, int mask, int n, vector<vector<int>> &cost, vector<vector<int>> &dp, vector<vector<int>> &path) {
    if (mask == ((1 << n) - 1))
        return cost[i][0];

    if (dp[i][mask] != -1)
        return dp[i][mask];

    int ans = INT_MAX;
    int best_next_city = -1;

    for (int j = 0; j < n; j++) {
        if (mask & (1 << j)) // if city is already visited
            continue;
        int new_cost = cost[i][j] + solve(j, mask | (1 << j), n, cost, dp, path);
        if (new_cost < ans) {
            ans = new_cost;
            best_next_city = j;
        }
    }

    dp[i][mask] = ans;
    path[i][mask] = best_next_city;

    return ans;
}

vector<int> getTSPPath(vector<vector<int>> &path, int n) {
    vector<int> tour;
    int current_city = 0;
    int mask = 1;
    for (int step = 0; step < n - 1; step++) {
        int next_city = path[current_city][mask];
        tour.push_back(next_city);
        mask |= (1 << next_city);
        current_city = next_city;
    }
    tour.push_back(0); // Return to the starting city to complete the tour
    return tour;
}

int Exact_TSP(Graph G) {
   int n = G.getVertices(); // Use G.getVertices() to get the number of vertices
    // Use G.V to get the number of vertices
    vector<vector<int>> cost(n, vector<int>(n));
    vector<vector<int>> dp(n, vector<int>(1 << n, -1));
    vector<vector<int>> path(n, vector<int>(1 << n, -1));

    // Initialize the cost matrix
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cost[i][j] = G.getEdge(i, j); // Use the getEdge function to get edge weights
        }
    }

    int minCost = solve(0, 1, n, cost, dp, path);
    vector<int> tour = getTSPPath(path, n);

   
     // Return to the starting city
    cout << "Optimum TSP Tour Path: ";
    for (int city =0;city<tour.size(); city++) {
        if(city==tour.size()-1){
                cout << city<<"->"<<0<<endl;
        }
        else{
            cout<<city<<"->";
        }
        
    }
    
   

    return minCost;
}


int main() {
    int V = 5; // Change this to the number of vertices you want.
    Graph randomGraph = Create_Random_Graph(V);
    int minTourLength = Exact_TSP(randomGraph);

    cout << "Optimum TSP Tour Length: " << minTourLength << endl;

    return 0;
}
