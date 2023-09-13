#include <bits/stdc++.h>
#define int long long
using namespace std;
const int N = 100;

void floyd_warshall(int graph[N][N], int v)
{
    int dist[v][v];
    int next[v][v];

    for (int i = 0; i < v; ++i)
    {
        for (int j = 0; j < v; ++j)
        {
            dist[i][j] = graph[i][j];
            if (graph[i][j] != INT_MAX && i != j)
            {
                next[i][j] = j;
            }
            else
            {
                next[i][j] = -1;
            }
        }
    }

    for (int k = 0; k < v; ++k)
    {
        for (int i = 0; i < v; ++i)
        {
            for (int j = 0; j < v; ++j)
            {
                if (dist[i][k] == INT_MAX || dist[k][j] == INT_MAX)
                {
                    continue;
                }
                else if (dist[i][k] + dist[k][j] < dist[i][j])
                {
                    dist[i][j] = dist[i][k] + dist[k][j];
                    next[i][j] = next[i][k];
                }
            }
        }
    }

    /*for (int i = 0; i < v; ++i)
    {
        for (int j = 0; j < v; ++j)
        {
            if (dist[i][j] == INT_MAX)
            {
                cout << "INF"
                     << " ";
            }
            else
            {
                cout << dist[i][j] << " ";
            }
        }
        cout << endl;
    }*/
    long long sum = 0;
    int p=1;
    //cin >> p;
    for (int i = 0; i < p; i++)
    {
        int start, end;
        cin >> start >> end;
        sum += dist[start - 1][end - 1];
    }

    cout<<sum << endl;

}
int findMinDistance(int dist[N][N], int v)
{
    int minDist = INT_MAX;

    for (int i = 0; i < v; ++i)
    {
        for (int j = 0; j < v; ++j)
        {
            if (dist[i][j] != INT_MAX && dist[i][j] < minDist)
            {
                minDist = dist[i][j];
            }
        }
    }

    return minDist;
}

int32_t main()
{
    
    int t;
    cin>>t;
    for(int i=0;i<t;i++){
        int n;
        int dist[N][N];
        cin >> n;

        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < n; j++)
            {
                cin >> dist[i][j];
            }
        }


        
        floyd_warshall(dist, n);
    
    }
  
}
