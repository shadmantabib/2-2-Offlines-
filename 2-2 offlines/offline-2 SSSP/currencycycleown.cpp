#include<bits/stdc++.h>
using namespace std;
ofstream fout("outss.txt");
#define MX 105
#define INF 1000000000.0

struct node {
    int val;
    double cost;
    vector<int> path;
};


vector<node> G[MX];
vector<node> G1[MX];
bool vis[MX];
double dist[MX];

void reset() {
    for (int i = 0; i < MX; i++) {
        G[i].clear();
        G1[i].clear();
        vis[i] = 0;
        dist[i] = INF;
    }
}

class cmp {
public:
    bool operator() (node& A, node& B) {
        if (A.cost >B.cost) return true;
        return false;
    }
};
void bellmanFord(int source) {
    dist[source] = 0;
    vector<int> parent(MX, -1);
    bool updated;

    for (int i = 1; i <= MX - 1; i++) {
        updated = false;
        for (int u = 0; u < MX; u++) {
            for (int j = 0; j < G1[u].size(); j++) {
                int v = G1[u][j].val;
                double w = G1[u][j].cost;

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
            for (int j = 0; j < G1[i].size(); j++) {
                int v = G1[i][j].val;
                double w = G1[i][j].cost;

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



void dijkstra(int source, int destination) {
    priority_queue<node, vector<node>, cmp> PQ;
    PQ.push({source, 1, {source}});

    while (!PQ.empty()) {
        node current = PQ.top();
        PQ.pop();

        int val = current.val;
        double cost = current.cost;
        cout<<"Her eis cost"<<cost<<endl;
        vector<int> path = current.path;

        if (vis[val] == 1) continue;

        dist[val] = cost;
        vis[val] = 1;

        if (val == destination) {
            cout << "Dijkstra Algorithm:\n";
            fout << "Dijkstra Algorithm:\n";
            cout << "Minimum cost: " << cost << "\n";
            fout << "Minimum cost: " << cost << "\n";
            cout << "Path: ";
            fout << "Path: ";
            for (int i = 0; i < path.size(); i++) {
                if (i == 0) {
                    cout << path[i];
                    fout << path[i];
                } else {
                    cout << " -> " << path[i];
                    fout << " -> " << path[i];
                }
            }
            cout << endl;
            fout << endl;
            cout<<path.size()-1<< endl;
             double exp=1;
          for (int i = 0; i < path.size(); i++) {
            cout<<dist[path[i]]<<endl;
            exp*=dist[path[i]];
          }
          cout<<exp<<endl;
            return;
        }


        for (int i = 0; i < G[val].size(); i++) {
            int nxt = G[val][i].val;
            double nxtCost = G[val][i].cost;

            if (vis[nxt] == 0) {
                vector<int> newPath = path;
                newPath.push_back(nxt);
                PQ.push({nxt, cost * nxtCost, newPath});
            }
        }
    }
   
    cout << "No path found from source to destination.\n";
    fout << "No path found from source to destination.\n";
}


int main() {
    reset();
    ifstream fin("iocur.txt");
    
    int nodes, edges;
    fin >> nodes >> edges;

    for (int i = 0; i < edges; i++) {
        int u, v;
        double w;
        fin >> u >> v >> w;
        cout<<w<<endl;

        G[u].push_back({v, abs(w)});
        G1[u].push_back({v, -log(w)});
    }

    int source, destination;
    
    fin >> source >> destination;
    bellmanFord(source);
    dijkstra(source, destination);
    

    return 0;
}
