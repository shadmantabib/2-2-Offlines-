#include<bits/stdc++.h>
using namespace std;
ofstream fout("outs.txt");
#define MX 105
#define INF 1e9

struct node {
    int val;
    double cost;
    vector<int> path;
};

vector<node> G[MX];
bool vis[MX];
double dist[MX];

void reset() {
    for (int i = 0; i < MX; i++) {
        G[i].clear();
        vis[i] = 0;
        dist[i] = INF;
    }
}

void bellmanFord(int source) {
    dist[source] = 0;
    vector<int> parent(MX, -1);
    bool updated;

    for (int i = 1; i <= MX - 1; i++) {
        updated = false;
        for (int u = 0; u < MX; u++) {
            for (int j = 0; j < G[u].size(); j++) {
                int v = G[u][j].val;
                double w = G[u][j].cost;

                if (dist[u] != INF && dist[u] + w < dist[v]) {
                    dist[v] = dist[u] + w;
                    parent[v] = u;
                    updated = true;
                }
            }
        }
        if (!updated) {
            break;
        }
    }

    if (updated) {
        cout << "Anomaly detected: Risk-free profit opportunity\n";
        fout << "Anomaly detected: Risk-free profit opportunity\n";

        // Find and print the negative cycle
        vector<int> cycle;
        int u = -1;
        for (int i = 0; i < MX; i++) {
            for (int j = 0; j < G[i].size(); j++) {
                int v = G[i][j].val;
                double w = G[i][j].cost;

                if (dist[i] != INF && dist[i] + w < dist[v]) {
                    u = v;
                    break;
                }
            }
            if (u != -1)
                break;
        }

        for (int i = 0; i < MX; i++) {
            u = parent[u];
        }

        int start = u;
        cycle.push_back(start);
        u = parent[u];
        while (u != start) {
            cycle.push_back(u);
            u = parent[u];
        }
        cycle.push_back(start);

        cout << "Negative Cycle: ";
        fout << "Negative Cycle: ";
        for (int i = 0; i < cycle.size(); i++) {
            cout << cycle[i] << " ";
            fout << cycle[i] << " ";
        }
        cout << endl;
        fout << endl;
    } else {
        cout << "No anomaly detected in currency exchange rates.\n";
        fout << "No anomaly detected in currency exchange rates.\n";
    }
}

int main() {
    reset();
    ifstream fin("iocur.txt");
    
    int currencies, exchanges;
    fin >> currencies >> exchanges;

    for (int i = 0; i < exchanges; i++) {
        int ci, cj;
        double rate;
        fin >> ci >> cj >> rate;

        // Take the negative logarithm of the exchange rate to get the edge weight
        double weight = -log(rate);

        G[ci].push_back({cj, weight});
    }

    // Choose any source node for the Bellman-Ford algorithm
    int source = 0;

    bellmanFord(3);

    return 0;
}
