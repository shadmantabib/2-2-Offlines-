#include<bits/stdc++.h>
#include<string>
using namespace std;
#define fastio ios_base::sync_with_stdio(false);cin.tie(NULL)

#define INTMAX 1000000

int n,w[15],l[15],r[15],g[15][15];
vector<string> name;

int cap[300][300];
vector<int> adj[300];

int bfs(int s, int t, vector<int>& parent) {
    fill(parent.begin(), parent.end(), -1);
    parent[s] = -2;
    queue<pair<int, int>> q;
    q.push(make_pair(s, INTMAX));

    while (!q.empty())
    {
        int cur = q.front().first;
        int new_flow = q.front().second;
        q.pop();

        for (int i=0;i<adj[cur].size();i++)
        {
            int next=adj[cur][i];
            if (parent[next] == -1 && cap[cur][next]>0) {
                parent[next] = cur;
                new_flow = min(new_flow, cap[cur][next]);
                if (next == t)
                    return new_flow;
                q.push({next, new_flow});
            }
        }
    }

    return 0;
}

int edmond_karps(int s, int t) {
    int flow = 0;
    vector<int> parent(n*n+5);
    int new_flow;

    while (new_flow = bfs(s, t, parent)) {
        flow += new_flow;
        int cur = t;
        while (cur != s) {
            int prev = parent[cur];
            cap[prev][cur] -= new_flow;
            cap[cur][prev] += new_flow;
            cur = prev;
        }
    }
    int lol=bfs(s,t,parent);

    return flow;
}


int main()
{
    fastio;
    int i,j,source,sink;
    string s;
    cin>>n;
    for(int k=0;k<n;k++)
    {
        cin>>s>>w[k]>>l[k]>>r[k];
        name.push_back(s);
        for(i=0;i<n;i++){
            cin>>g[k][i];
        }
    }
    source=n*n;
    sink=n*n+1;
    for(int team=0;team<n;team++)
    {
        int gvert=n;
        for(i=0;i<n;i++)
        {
            if(i==team)
                continue;
            for(j=i+1;j<n;j++)
            {
                if(j==team)
                    continue;
                cout<<source<<' '<<gvert<<' '<<i<<' '<<j<<endl;
                cap[gvert][i]=INTMAX;
                cap[gvert][j]=INTMAX;
                cap[source][gvert]=g[i][j];
                adj[gvert].push_back(i);
                adj[gvert].push_back(j);
                adj[source].push_back(gvert);
                adj[i].push_back(gvert);
                adj[j].push_back(gvert);
                adj[gvert].push_back(source);
                gvert++;
            }
        }

        for(i=0;i<n;i++)
        {
            if(i==team)
                continue;
            cap[i][sink]=w[team]+r[team]-w[i];
            adj[i].push_back(sink);
            adj[sink].push_back(i);
        }

        int x=edmond_karps(source,sink);
        int flag=0;
        for(i=0;i<adj[source].size();i++)
        {
            if(cap[source][adj[source][i]]!=0)
            {
                flag=1;
                break;
            }
            //cout<<adj[source][i]<<" "<<cap[source][adj[source][i]]<<"\n";
        }
        if(flag==1)
            cout<<name[team]<<" is eliminated\n";

        //clearing the adj and cap
        for(i=0;i<=sink;i++)
        {
            for(j=0;j<=sink;j++)
                cap[i][j]=0;
        }
        for(i=0;i<=sink;i++)
            adj[i].clear();
    }
    return 0;
}