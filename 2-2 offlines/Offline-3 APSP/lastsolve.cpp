#include <bits/stdc++.h>
using namespace std;

vector<bool> vis;
vector<int> dis_from_s, dis_from_d;
vector<vector<int> > graph;

void bfs(int node, vector<int>& dis)
{
    queue<int> q;
    vis[node] = true;
    q.push(node);

    while(!q.empty())
    {
        int u = q.front();
        q.pop();

        for(auto v: graph[u])
        {
            if(!vis[v])
            {
                vis[v] = true;
                dis[v] = dis[u]+1;
                q.push(v);
            }
        }
    }
}

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    int t;
    cin>>t;

    for(int cs=1; cs<=t; cs++)
    {
        int n, r, s, d, ans = 0;
        cin>>n>>r;
        vis.assign(n, false);
        dis_from_s.assign(n, 0);
        dis_from_d.assign(n, 0);
        graph.assign(n, vector<int>());

        for(int i=0; i<r; i++)
        {
            int u, v;
            cin>>u>>v;
            graph[u].push_back(v);
            graph[v].push_back(u);
        }

        cin>>s>>d;
        bfs(s, dis_from_s);
        fill(vis.begin(), vis.end(), false);
        bfs(d, dis_from_d);

        for(int i=0; i<n; i++)
            ans = max(ans, dis_from_s[i]+dis_from_d[i]);

        cout<<"Case "<<cs<<": "<<ans<<"\n";
    }

    return 0;
}