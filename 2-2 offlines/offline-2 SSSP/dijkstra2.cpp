#include<bits/stdc++.h>
using namespace std;

#define MX 105
#define INF 1000000000

struct node {
    int val;
    int cost;
    vector<int> path;
};

vector<node> G[MX];
bool vis[MX];
int dist[MX];

void reset() {
    for (int i = 0; i < MX; i++) {
        G[i].clear();
        vis[i] = 0;
        dist[i] = INF;
    }
}

class cmp {
public:
    bool operator() (node& A, node& B) {
        if (A.cost > B.cost) return true;
        return false;
    }
};

void dijkstra(int source, int destination) {
    priority_queue<node, vector<node>, cmp> PQ;
    PQ.push({source, 0, {source}});

    while (!PQ.empty()) {
        node current = PQ.top();
        PQ.pop();

        int val = current.val;
        int cost = current.cost;
        vector<int> path = current.path;

        if (vis[val] == 1) continue;

        dist[val] = cost;
        vis[val] = 1;

        if (val == destination) {
            cout << "Dijkstra Algorithm:\n";
            cout << "Minimum cost: " << cost << "\n";
            cout << "Path: ";
            for (int i = 0; i < path.size(); i++) {
                if (i == 0) {
                    cout << path[i];
                } else {
                    cout << " -> " << path[i];
                }
            }
            cout << endl;
            return;
        }

        for (int i = 0; i < G[val].size(); i++) {
            int nxt = G[val][i].val;
            int nxtCost = G[val][i].cost;

            if (vis[nxt] == 0) {
                vector<int> newPath = path;
                newPath.push_back(nxt);
                PQ.push({nxt, cost + nxtCost, newPath});
            }
        }
    }

    cout << "No path found from source to destination.\n";
}

int main() {
    reset();

    int nodes, edges;
    cin >> nodes >> edges;

    for (int i = 0; i < edges; i++) {
        int u, v, w;
        cin >> u >> v >> w;
        G[u].push_back({v, abs(w)});
    }

    int source, destination;
    cout << "Enter the source and destination nodes: ";
    cin >> source >> destination;

    dijkstra(source, destination);

    return 0;
}
