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

    for (int i = 0; i < v; ++i)
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
    }
    double sum = 0;
   
    //cin >> p;
    for (int i = 0; i < v; i++)
    {
        for(int j=0; j<v ;j++)
        {
            if(i!=j){
                    sum += dist[i][j];
            }
        }
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
    
    
    int dist[N][N];
    for(int i = 0; i < N; ++i){
        for(int j = 0; j < N; ++j){
            if(i==j){
                dist[i][j] = 0;
            }
            else{
            dist[i][j] = INT_MAX;
            }
        }
    }
    while(1){
        int u,v;
        cin>>u>>v;
        if(u==0 && v==0){
            break;
        }
        else{
            dist[u-1][v-1] = 1;
        }
        
    }

       for (int i = 0; i < 4; ++i)
    {
        for (int j = 0; j < 4; ++j)
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
    } 
        floyd_warshall(dist,4 );
    
    }
  

