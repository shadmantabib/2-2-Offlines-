#include "bits/stdc++.h"
using namespace std;

class DSU
{
    vector<int> par, size;

public:
    DSU(int n) 
    {
        fill(size.begin(), size.end(), 1);
        for (int i = 0; i < n; i++)
            par[i] = i;
    }
    int Anc(int node)
    {
        if (par[node] == node)
            return node;
        return par[node] = Anc(par[node]);
    }
    bool same(int x, int y)
    {
        return Anc(x) == Anc(y);
    }
    void Union(int x, int y)
    {
        x = Anc(x), y = Anc(y);
        if (x == y)
            return;
        if (size[x] < size[y])
            swap(x, y);
        size[x] += size[y], par[y] = x;
    }
    int Size(int node)
    {
        return size[Anc(node)];
    }
};
struct edge
{
    int u, v, w;
    edge() {}
    edge(int a, int b, int c)
    {
        u = a, v = b, w = c;
    }
};
void solve(int tc)
{
    int n, m;
    cin >> n >> m;
    vector<edge> edges(m);
    DSU dsu1(n + 1), dsu2(n + 1);
    for (auto &e : edges)
        cin >> e.u >> e.v >> e.w;
    int c = 0;
    for (auto e : edges)
    {
        if (e.w == 3)
        {
            if (!dsu1.same(e.u, e.v) && !dsu2.same(e.u,e.v))
                dsu1.Union(e.u, e.v), dsu2.Union(e.u, e.v), c++;
        }
    }
    for (auto e : edges)
    {
        if (e.w == 1)
        {
            if (!dsu1.same(e.u, e.v))
                dsu1.Union(e.u, e.v), c++;
        }
    }
    for (auto e : edges)
    {
        if (e.w == 2)
        {
            if (!dsu2.same(e.u, e.v))
                dsu2.Union(e.u, e.v), c++;
        }
    }
    int comp1 = 0, comp2 = 0;
    for (int i = 1; i <= n; i++)
        if (dsu1.Anc(i) == i)
            comp1++;
    for (int i = 1; i <= n; i++)
        if (dsu2.Anc(i) == i)
            comp2++;
    if (comp1 == comp2 and comp1 == 1)
        cout << m - c << endl;
    else
        cout << -1 << endl;
}
int32_t main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int T = 1;
    // cin>>T;
    for (int t = 1; t <= T; t++)
        solve(t);
    return 0;
}