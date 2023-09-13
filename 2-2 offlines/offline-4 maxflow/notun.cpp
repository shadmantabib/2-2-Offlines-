#include <bits/stdc++.h>
using namespace std;

#define fastio ios_base::sync_with_stdio(false);cin.tie(NULL)

#define INF 1000000

int n, m;
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
    int t;
    cin >> t;

    for (int test = 1; test <= t; test++)
    {
        cin >> n >> m;

        vector<string> team(n);
        vector<int> rank(n);
        vector<int> code(n);

        int source = n+n *(n-1);
        int sink = n + (n-1)*n + 1;

        // Input reading fixed
        for (int i = 0; i < n; i++)
        {
            cin >> team[i] >> rank[i] >> code[i];
            capacity[source][i] = 2;
            adj[source].push_back(i);
            adj[i].push_back(source);
        }

        for (int i = 0; i < team.size(); i++)
        {
            for (int j = 0; j < team.size(); j++)
            {
                if (i != j && ((rank[i] % 2 == 0 && rank[j] % 2 == 1) || (rank[j] % 2 == 0 && rank[i] % 2 == 1)) && code[i] != code[j])
                {
                    capacity[i][n + j * (n - 1)] = 1;
                    adj[i].push_back(n + j * (n - 1));
                    adj[n + j * (n - 1)].push_back(i);
                }
            }
        }

        for (int i = 0; i < (n - 1) * n; i++)
        {
            capacity[n + i][sink] = 1;
            adj[n + i].push_back(sink);
            adj[sink].push_back(n + i);
        }

        int x = edmond_karps(source, sink);
        int flag = 0;
        for (int i = 0; i < adj[source].size(); i++)
        {
            if (capacity[source][adj[source][i]] == 0)
            {
                flag = 1;
                break;
            }
        }

        if (flag == 1)
            cout << "Case " << test << ": " << "yes" << "\n";
        else
            cout << "Case " << test << ": " << "no" << "\n";

        // Clearing the adj and capacity
        for (int i = 0; i <= sink; i++)
        {
            for (int j = 0; j <= sink; j++)
                capacity[i][j] = 0;
        }
        for (int i = 0; i <= sink; i++)
            adj[i].clear();
    }

    return 0;
}
