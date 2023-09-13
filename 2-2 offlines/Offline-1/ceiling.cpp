// Add some code
#include<bits/stdc++.h>
using namespace std;
#define MAX 55

struct edge{
    int u, v, w;
};

vector <edge> G; // Edge List (used in Kruskal's)
vector <int> graph[MAX]; // Adjacency List (Used in DFS)

bool cmp( edge A, edge B ){
    return A.w < B.w;
}

int parent[MAX];
bool vis[MAX];
int n; // total nodes
int cnt; // counter variable to check how many nodes are visited in dfs

// reset data structures for every test case
void reset(){
    G.clear();
    for (int i = 0; i < MAX; i++){
        parent[i] = i;
        graph[i].clear();
        vis[i] = 0;
    }
    cnt = 0;
}

// dfs function to traverse the graph
void dfs(int n){
    vis[n] = 1;
    cnt++; // increment counter as we visit a node
    for (int i = 0; i < graph[n].size(); i++){
        int v = graph[n][i];
        if (!vis[v])
            dfs(v);
    }
}

// find parent of a disjoint-set
// used in MST
int Find(int u){
    if (u == parent[u]) return u;
    return parent[u] = Find(parent[u]);
}

// compute MST cost
// Uses Kruskal's Algorithm with Disjoint-Set Union method
int MST (){
    int cost = 0;
    sort(G.begin(), G.end(), cmp);

    for (int i = 0; i < G.size(); i++){
        int u = G[i].u;
        int v = G[i].v;
        int w = G[i].w;

        int p = Find(u);
        int q = Find(v);
        if (p!=q){
            parent[q] = p;
            cost += w;
        }
    }

    return cost;
}

// function to check if every node is reachable from any other
bool check(int node){
    dfs(node);
    return cnt == n;
}


int main()
{
    int T; scanf("%d", &T);
    for (int cs = 1; cs <= T; cs++){
        reset(); // reset all data structures

        scanf("%d", &n);

        int totalLength = 0; // sum of all cable lengths
        for (int i = 1; i <= n; i++){
            for (int j = 1; j <= n; j++){
                int w; scanf("%d", &w);
                if (w){ // if weight is non-zero
                    // insert into edge list
                    G.push_back({i, j, w});
                    // insert into adjacency list
                    graph[i].push_back(j);
                    graph[j].push_back(i);
                }
                totalLength += w; // update total length
            }
        }

        // if the graph is not connected, print "-1"
        // we run dfs from node 1, any node can be used
        if (!check(1)){
            printf("Case %d: -1\n", cs);
            continue;
        }

        int mst = MST();
        int answer = totalLength - mst;
        printf("Case %d: %d\n", cs, answer);
    }

    return 0;
}