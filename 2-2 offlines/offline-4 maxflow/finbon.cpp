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
int n, wins[100], losses[100], remaining[100], games_played[100][100];

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
void clear_graph()
{
    for (int i = 0; i < 250; i++)
    {
        adj[i].clear();
        for (int j = 0; j < 250; j++)
            cap[i][j] = 0;
    }
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
    if(n==2){

        /*cout << team_names[team] << " is eliminated.\n";
            cout << "They can win at most " << wins[team] << "+" << remaining[team] << "=" << wins[team] + remaining[team] << " games.\n";
*/
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
            marker=(marker+1)%2;
            if(wins[marker]+remaining[marker]< wins[(marker+1)%2]){

            
            cout << team_names[marker] << " is eliminated.\n";
            cout << "They can win at most " << wins[marker] << "+" << remaining[marker] << "=" << wins[marker] + remaining[marker] << " games.\n";
            
            cout << team_names[(marker+1)%2] << " has won a total of " << max_wins << endl;
            cout << "They play each other " << 0 << " times" << endl;
            cout << "So on average, each of the teams in this group wins " << max_wins << "/" << 1 << "=" << max_wins / 1 << " games";
            }


    }
    
    else{
    for (int team = 0; team < n; team++)
    {
        source = n * n;//assigning source index like this 
        //because in case of n*(n-1) there must be any faceoff 
        //index .so to avoid I have taken this
        
        sink = n * n + 1;//....sink index

        clear_graph();

        int gvert = n;
        /*assigning the game vertex index.From here we can go through team nodes assigning 
        their cap to corresponding team nodes 
        which we will denote as i,j.These indexes are the teams 
        played between in the game*/
        for (i = 0; i < n; i++)
        {
            if (i == team)
                continue;
            for (j = i + 1; j < n; j++)
            {
                if (j == team)
                    continue;
                //cout<<"red"<<endl;    
                cap[gvert][i] = INTMAX;
                cap[gvert][j] = INTMAX;
                /*
                assigning the max capacity of game to
                team nodes as INTMAXinity since they are 
                will be constrained by source to game 
                nodes capacity later on
                */
                cap[source][gvert] = games_played[i][j];
                /*
                    source to capacity node will 
                    be the remaining games to be played
                    by the faceoff team pairs in game
                    nodes
                */
                
                adj[gvert].push_back(i);
                adj[gvert].push_back(j);
                /*
                    connecting game and team nodes 
                    with corresponding pair
                
                */
                adj[source].push_back(gvert);
               // cout<<"hellodoctor"<<adj[source].size()<<endl;
               // cout<< adj[source]<<endl;
                adj[i].push_back(gvert);
                adj[j].push_back(gvert);
                adj[gvert].push_back(source);
                gvert++;
            }
        }
        //cout<<"here"<<adj[source].size()<<endl;

        for (i = 0; i < n; i++)
        {
            if (i == team)
                continue;
            cap[i][sink] = wins[team] + remaining[team] - wins[i];
            adj[i].push_back(sink);
            adj[sink].push_back(i);
        }
        //cout<<"hello"<<endl;
        int x = edmonds_karp(source, sink);
        //cout<<x<<endl;
        int flag = 0;
        //cout<<adj[source].size()<<endl;
        for (i = 0; i < adj[source].size(); i++)
        {
            cout<<cap[source][adj[source][i]];
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
                cout << team_names[marker] << " has won a total of " << max_wins << endl;
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
                vector<string> other_teams;
                vector<int> trace;
                for (i = 0; i < n; i++)
                {
                    if (i == team)
                        continue;
                    if (inR[i])
                    {
                        other_wins += wins[i];
                        other_teams.push_back(team_names[i]);
                        trace.push_back(i);
                        
                    }
                }
                
                int matches=0;
                for(int i=0;i<(trace.size());i++){
                    for(int j=0;j<trace.size();j++){
                        if(i<=j ){
                                matches+=games_played[trace[i]][trace[j]];
                        }
                }
                }
                //cout<<matches<<endl;
                /*for(int i=0;i<sizeof(other_teams);i++){
                    cout<<other_teams[i]<<endl;
                }*/

                cout << other_teams[0];
                for (int idx = 1; idx < other_teams.size(); idx++)
                {
                    cout << " and " << other_teams[idx];
                }
                cout << " have won a total of " << other_wins << " games.\n";

                cout << "They play each other " << matches << " times.\n";
                cout << "So on average, each of the teams wins " << ((double)other_wins + matches) << "/" << other_teams.size() << "=" << fixed << setprecision(1) << ((double)other_wins + matches) / other_teams.size() << " games.\n";
                clear_graph();
            }
        }
    }
    }

    return 0;
}
