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

    int getEdge(int u, int v) const {
        if (u >= 0 && u < V && v >= 0 && v < V) {
            return Mat[u][v];
        } else {
            return -1; 
        }
    }

};

Graph Create_Random_Graph(int V) {
    if (V < 2) {
        cout << "Invalid graph size" << endl;
        exit(1);
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


int solve(int i, int mask, int n, vector<vector<int>>& cost, vector<vector<int>>& dp, vector<vector<int>>& path) {
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

vector<int> getTSPPath(vector<vector<int>>& path, int n) {
    vector<int> tour;
    int current_city = 0;
    int mask = 1;
    for (int step = 0; step < n - 1; step++) {
        int next_city = path[current_city][mask];
        tour.push_back(next_city);
        mask |= (1 << next_city);
        current_city = next_city;
    }
    tour.push_back(0); 
    return tour;
}

int Exact_TSP(Graph G) {
    int n = G.getVertices();
    vector<vector<int>> cost(n, vector<int>(1 << n, -1));
    vector<vector<int>> dp(n, vector<int>(1 << n, -1));
    vector<vector<int>> path(n, vector<int>(1 << n, -1));

 
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cost[i][j] = G.getEdge(i, j);
        }
    }

    int minCost = solve(0, 1, n, cost, dp, path);
    vector<int> tour = getTSPPath(path, n);


    cout << "Optimum TSP Tour Path: ";
    cout<<0<<"->";
    for (int city=0;city<tour.size(); city++) {
        if(city==tour.size()-1){
        cout << tour[city] ;
        }
        else{
            cout<<tour[city]<<"->";
        }
    }
    cout<<endl;
    

    return minCost;
}


vector<pair<int, int>> PrimMST(const Graph& G) {
    int n = G.getVertices();
    vector<pair<int, int>> mstEdges;

    vector<int> key(n, INT_MAX);
    vector<int> parent(n, -1);
    vector<bool> inMST(n, false);

    key[0] = 0;

    for (int count = 0; count < n - 1; count++) {
        int u = -1;
        for (int v = 0; v < n; v++) {
            if (!inMST[v] && (u == -1 || key[v] < key[u])) {
                u = v;
            }
        }

        inMST[u] = true;

        for (int v = 0; v < n; v++) {
            int weight = G.getEdge(u, v);
            if (!inMST[v] && weight > 0 && weight < key[v]) {
                parent[v] = u;
                key[v] = weight;
            }
        }
    }

    for (int i = 1; i < n; i++) {
        mstEdges.push_back({parent[i], i});
    }

    return mstEdges;
}





vector<int> FindEulerianTour(const vector<pair<int, int>>& eulerianEdges, int n) {
    vector<vector<int>> adj(n);
    for (const pair<int, int>& edge : eulerianEdges) {
        adj[edge.first].push_back(edge.second);
        adj[edge.second].push_back(edge.first);
    }

    vector<int> tour;
    stack<int> stk;
    int current_vertex = 0;

    while (!stk.empty() || !adj[current_vertex].empty()) {
        if (adj[current_vertex].empty()) {
            tour.push_back(current_vertex);
            current_vertex = stk.top();
            stk.pop();
        } else {
            int next_vertex = adj[current_vertex].back();
            adj[current_vertex].pop_back();
            stk.push(current_vertex);
            current_vertex = next_vertex;
        }
    }

    tour.push_back(current_vertex);

    reverse(tour.begin(), tour.end()); 
    return tour;
}

int Calculate_Tour_Length(const vector<int>& tour, const Graph& G) {
    int length = 0;
    int n = tour.size();

    for (int i = 0; i < n - 1; i++) {
        length += G.getEdge(tour[i], tour[i + 1]);
    }

    length += G.getEdge(tour[n - 1], tour[0]);

    return length;
}
int Metric_Approximation_TSP(Graph G) {
    int n = G.getVertices();
    
   
    vector<pair<int, int>> mstEdges = PrimMST(G);

    vector<int> eulerianTour = FindEulerianTour(mstEdges, n);

  
    unordered_set<int> visited;
    vector<int> tourC;
    for (int vertex : eulerianTour) {
        if (!visited.count(vertex)) {
            visited.insert(vertex);
            tourC.push_back(vertex);
        }
    }


    int tourLength = Calculate_Tour_Length(tourC, G);

    
    cout << "Metric Approximation TSP Tour Path: ";
    for (int city : tourC) {
        cout << city << " -> ";
    }
    cout << tourC[0] << endl;

    return tourLength;
}

int main() {
    int X;
    cout << "Enter the number of test cases (X): ";
    cin >> X;

    for (int x = 1; x <= X; x++) {
        Graph randomGraph = Create_Random_Graph(20);
        int optimalTourLength = Exact_TSP(randomGraph);
        int approxTourLength = Metric_Approximation_TSP(randomGraph);

        double ratio = (double)(approxTourLength) / optimalTourLength;
        cout << "(" << x << ": " << ratio <<")"<< endl;
    }

    return 0;
}