#include<bits/stdc++.h>
using namespace std;

#define fastio ios_base::sync_with_stdio(false);cin.tie(NULL)

#define INF 1000000

int n,m;
int capacity[300][300];
vector<int> adj[300];

int bfs(int s, int t, vector<int>& parent)
{
    fill(parent.begin(), parent.end(), -1);
    parent[s] = -2;
    queue<pair<int, int>> q;
    q.push(make_pair(s, INF));

    while (!q.empty())
    {
        int cur = q.front().first;
        int new_flow = q.front().second;
        q.pop();

        for (int i=0; i<adj[cur].size(); i++)
        {
            int next=adj[cur][i];
            if (parent[next] == -1 && capacity[cur][next]>0)
            {
                parent[next] = cur;
                new_flow = min(new_flow, capacity[cur][next]);
                if (next == t)
                    return new_flow;
                q.push({next, new_flow});
            }
        }
    }

    return 0;
}

int edmond_karps(int s, int t)
{
    int flow = 0;
    vector<int> parent(m+6*n+5);
    int new_flow;

    while (new_flow = bfs(s, t, parent))
    {
        flow += new_flow;
        int cur = t;
        while (cur != s)
        {
            int prev = parent[cur];
            capacity[prev][cur] -= new_flow;
            capacity[cur][prev] += new_flow;
            cur = prev;
        }
    }

    return flow;
}


int main()
{
    fastio;
    int t,i,j,source,sink;
    cin>>t;
    string s,s1,s2;
    for(int test=1; test<=t; test++)
    {
        cin>>n>>m;
        //source=m+6*n;
        source=n+(n-1)*n;

        //sink=m+6*n+1;
        sink=n+(n-1)*n+1;
        string t;
        vector<string>team;
        vector<int>rank;
        vector<int>code;
        //cin.get();
        for(i=0; i<n; i++)
        {
             cin>>team[i]>>rank[i]>>code[i];
            capacity[source][i]=m;
            adj[source].push_back(i);
            adj[i].push_back(source);
            //getline(cin,s);
           
        }
        
            for(int i=0;i<team.size();i++){
                for(int j=0;j<team.size();j++){
                    if(i!=j && ((rank[i]%2==0 && rank[j]%2==1)||(rank[j]%2==0 && rank[i]%2==1) ) && code[i]!=code[j]){
                        capacity[i][n+j*(n-1)]=1;
                        adj[i].push_back(n+j*(n-1));
                        adj[n+j*(n-1)].push_back(i);
                    }
                }
            }
           

        for(i=0; i<(n-1)*n; i++)
        {
            capacity[n+i][sink]=1;
            adj[n+i].push_back(sink);
            adj[sink].push_back(n+i);
        }
        int x=edmond_karps(source,sink);
        int flag=0;
        for(i=0; i<adj[source].size(); i++)
        {
            if(capacity[source][adj[source][i]]!=0)
            {
                flag=1;
                break;
            }
            //cout<<adj[source][i]<<" "<<capacity[source][adj[source][i]]<<"\n";
        }
        if(flag==1)
            cout<<"Case "<<test<<": "<<"NO"<<"\n";
        else
            cout<<"Case "<<test<<": "<<"YES"<<"\n";
        for(i=0; i<=sink; i++)
        {
            for(j=0; j<=sink; j++)
                capacity[i][j]=0;
        }
        for(i=0; i<=sink; i++)
            adj[i].clear();
    }

    /*for(int team=0;team<n;team++)
    {
        int x=edmond_karps(source,sink);
        int flag=0;
        for(i=0;i<adj[source].size();i++)
        {
            if(capacity[source][adj[source][i]]!=0)
            {
                flag=1;
                break;
            }
            //cout<<adj[source][i]<<" "<<capacity[source][adj[source][i]]<<"\n";
        }
        if(flag==1)
            cout<<name[team]<<" is eliminated\n";

        //clearing the adj and capacity
        for(i=0;i<=sink;i++)
        {
            for(j=0;j<=sink;j++)
                capacity[i][j]=0;
        }
        for(i=0;i<=sink;i++)
            adj[i].clear();*/

    return 0;
}
