#include<bits/stdc++.h>
using namespace std;
#define MX 100005

struct edge{
    int u, v, w;
};
bool cmp(edge &a, edge &b){
    return a.w < b.w;
}
vector< edge > G; // edge list
int parent[MX];

// function to reset the data structures
void reset(int n){
    G.clear();
    for (int i = 1; i <= n; i++)
        parent[i] = i;
}

// function to find parent of a disjoint set
int Find(int u){
    if (u == parent[u]) return u;
    return parent[u] = Find(parent[u]);
}

// Kruskal's algorithm with Disjoint-Set Union method is used
// minimum spanning tree
int mst(){
    sort(G.begin(), G.end(), cmp);
    int cost = 0;
    for (int i = 0; i < G.size(); i++){
        int p = Find(G[i].u);
        int q = Find(G[i].v);
        if (p != q){
            parent[q] = p;
            cost += G[i].w;
        }
    }
    return cost;
}

int main()
{
    int T; scanf("%d", &T);
    for (int cs = 1; cs <= T; cs++){
        int n, m, airport;
        scanf("%d%d%d", &n, &m, &airport);

        reset(n);

        for (int i = 1; i <= m; i++){
            int u, v, w; scanf("%d%d%d", &u, &v, &w);
            // if edge weight is greater or equal to airport cost
            // we prefer building airport
            if (w >= airport) continue;
            G.push_back({u, v, w});
        }

        int mstCost = mst();

        set<int> comps; // number of components
        for (int i = 1; i <= n; i++){
            // insert parent of every node into the set
            // to get number of components in the graph
            comps.insert(Find(i));
        }
        int total = mstCost + comps.size() * airport;
        printf("Case %d: %d %d\n", cs, total, comps.size());
    }
    return 0;
}