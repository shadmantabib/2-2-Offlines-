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
        source=m+6*n;
        sink=m+6*n+1;
        cin.get();
        for(i=0; i<m; i++)
        {
            capacity[source][i]=1;
            adj[source].push_back(i);
            adj[i].push_back(source);
            getline(cin,s);
            for(j=0; j<s.size(); j++)
            {
                if(s[j]==' ')
                {
                    s1=s.substr(0,j);
                    s2=s.substr(j+1,s.size());
                    break;
                }
            }
            for(j=0; j<n; j++)
            {
                if(s1=="XS" || s2=="XS")
                {
                    capacity[i][m+j*6]=1;
                    
                    adj[i].push_back(m+j*6);
                    adj[m+j*6].push_back(i);
                }
                if(s1=="S" || s2=="S")
                {
                    capacity[i][m+j*6+1]=1;
                    adj[m+j*6+1].push_back(i);
                    adj[i].push_back(m+j*6+1);
                }
                if(s1=="M" || s2=="M")
                {
                    capacity[i][m+j*6+2]=1;
                    adj[m+j*6+2].push_back(i);
                    adj[i].push_back(m+j*6+2);
                }
                if(s1=="L" || s2=="L")
                {
                    capacity[i][m+j*6+3]=1;
                    adj[m+j*6+3].push_back(i);
                    adj[i].push_back(m+j*6+3);
                }
                if(s1=="XL" || s2=="XL")
                {
                    capacity[i][m+j*6+4]=1;
                    adj[m+j*6+4].push_back(i);
                    adj[i].push_back(m+j*6+4);
                }
                if(s1=="XXL" || s2=="XXL")
                {
                    capacity[i][m+j*6+5]=1;
                    adj[m+j*6+5].push_back(i);
                    adj[i].push_back(m+j*6+5);
                }
            }
        }
        
        for(i=0; i<6*n; i++)
        {
            capacity[m+i][sink]=1;
            adj[m+i].push_back(sink);
            adj[sink].push_back(m+i);
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
