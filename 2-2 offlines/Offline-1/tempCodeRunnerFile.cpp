double prim(const vector<vector<pair<int, double>>>& graph, int n, vector<int>& parent) {
    double totalWeight = 0;

    vector<double> disc(n, numeric_limits<double>::max()); 
    vector<bool> visited(n, false);   

    priority_queue<pair<double, int>, vector<pair<double, int>>, greater<pair<double, int>>> pq; 
    pq.push({0.0, 0}); 

    while (!pq.empty()) {
        int u = pq.top().second;
        double weight = pq.top().first;
        pq.pop();

        if (visited[u]) {
            continue;
        }

        visited[u] = true;
        totalWeight += weight;

        for (const pair<int, double>& nb : graph[u]) {
            int v = nb.first;
            double ew = nb.second;
            if (!visited[v] && ew < disc[v]) {
                disc[v] = ew;
                pq.push({disc[v], v});
                parent[v] = u;
            }
        }
    }

    return totalWeight;
}