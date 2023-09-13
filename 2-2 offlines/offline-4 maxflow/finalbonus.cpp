/*#pragma GCC optimize("Ofast")
#pragma GCC optimize ("unroll-loops")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,tune=native")*/
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace std;

#define INTMAX 5000000

vector<string> team_names;

int cap[250][250];
vector<int> adj[250];
int n, wins[50], losses[50], remaining[50], games_played[50][50];


int bfs(int s, int t, vector<int> &parent)
{
    fill(parent.begin(), parent.end(), -1);
    parent[s] = -2;
    queue<pair<int, int>> q;
    q.push(make_pair(s, INTMAX));

    while (!q.empty())
    {
        int cur = q.front().first;
        int new_flow = q.front().second;
        q.pop();

        for (int i = 0; i < adj[cur].size(); i++)
        {
            int next = adj[cur][i];
            if (parent[next] == -1 && cap[cur][next] > 0)
            {
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

int edmonds_karp(int s, int t)
{
    int flow = 0;
    vector<int> parent(n * n + 5);
    int new_flow;

    while ((new_flow = bfs(s, t, parent)))
    {
        flow += new_flow;
        int cur = t;
        while (cur != s)
        {
            int prev = parent[cur];
            cap[prev][cur] -= new_flow;
            cap[cur][prev] += new_flow;
            cur = prev;
        }
    }

    return flow;
}

int main()
{
    ios_base::sync_with_stdio(false);
    int i, j, source, sink;
    string s;
    cin >> n;
    for (int k = 0; k < n; k++)
    {
        cin >> s >> wins[k] >> losses[k] >> remaining[k];
        team_names.push_back(s);
        for (i = 0; i < n; i++)
        {
            cin >> games_played[k][i];
        }
    }

    for (int team = 0; team < n; team++)
    {
        source = n * n;
        sink = n * n + 1;

        // Clearing the adjacency list and cap matrix
        for (i = 0; i <= sink; i++)
        {
            for (j = 0; j <= sink; j++)
                cap[i][j] = 0;
        }

        for (i = 0; i <= sink; i++)
            adj[i].clear();

        int gvert = n;
        for (i = 0; i < n; i++)
        {
            if (i == team)
                continue;
            for (j = i + 1; j < n; j++)
            {
                if (j == team)
                    continue;
                cap[gvert][i] = INTMAX;
                cap[gvert][j] = INTMAX;
                cap[source][gvert] = games_played[i][j];
                adj[gvert].push_back(i);
                adj[gvert].push_back(j);
                adj[source].push_back(gvert);
                adj[i].push_back(gvert);
                adj[j].push_back(gvert);
                adj[gvert].push_back(source);
                gvert++;
            }
        }

        for (i = 0; i < n; i++)
        {
            if (i == team)
                continue;
            cap[i][sink] = wins[team] + remaining[team] - wins[i];
            adj[i].push_back(sink);
            adj[sink].push_back(i);
        }

        int x = edmonds_karp(source, sink);
        int flag = 0;
        for (i = 0; i < adj[source].size(); i++)
        {
            if (cap[source][adj[source][i]] != 0)
            {
                flag = 1;
                break;
            }
        }

        if (flag == 1)
        {
            cout << team_names[team] << " is eliminated.\n";
            cout << "They can win at most " << wins[team] << "+" << remaining[team] << "=" << wins[team] + remaining[team] << " games.\n";
            // Finding the subset of teams R by choosing the team gvertices on the source side of the min s-t cut
            int max_wins = INT_MIN;
            int marker = -1;
            for (int k = 0; k < n; k++)
            {
                if (wins[k] > max_wins)
                {
                    max_wins = wins[k];
                    marker = k;
                }
            }
            if (max_wins > wins[team] + remaining[team])
            {
                cout << team_names[marker] << " "
                     << "has won a total of " << max_wins << endl;
                cout << "They play each other " << 0 << " times" << endl;
                cout << "So on average, each of the teams in this group wins " << max_wins << "/" << 1 << "=" << max_wins / 1 << " games";
            }
            else
            {

                queue<int> q;
                q.push(source);
                vector<bool> inR(n, false);
                inR[source] = true;
                while (!q.empty())
                {
                    int cur = q.front();
                    q.pop();
                    for (int next : adj[cur])
                    {
                        if (!inR[next] && cap[cur][next] > 0)
                        {
                            inR[next] = true;
                            q.push(next);
                        }
                    }
                }

                int other_wins = 0;
                vector<string> other_teams; // Storing the names of other teams
                for (i = 0; i < n; i++)
                {
                    if (i == team)
                        continue;
                    if (inR[i])
                    {
                        other_wins += wins[i];
                        other_teams.push_back(team_names[i]);
                    }
                }

                cout << other_teams[0];
                for (int idx = 1; idx < other_teams.size(); idx++)
                {
                    cout << " and " << other_teams[idx];
                }
                cout << " have won a total of " << other_wins << " games.\n";
                cout << "They play each other " << x << " times.\n";
                cout << "So on average, each of the teams wins " << ((double)other_wins + x) << "/" << other_teams.size() << "=" << fixed << setprecision(1) << ((double)other_wins + x) / other_teams.size() << " games.\n";
                for (i = 0; i <= sink; i++)
                {
                    for (j = 0; j <= sink; j++)
                        cap[i][j] = 0;
                }
                for (i = 0; i <= sink; i++)
                    adj[i].clear();
            }
        }
    }

    return 0;
}
