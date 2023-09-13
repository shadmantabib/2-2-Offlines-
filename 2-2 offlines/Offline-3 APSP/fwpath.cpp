#include<bits/stdc++.h>
using namespace std;
const int N = 100;

void floyd_warshall(int graph[N][N], int v, int start, int end)
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
                cout << "INF" << " ";
            }
            else
            {
                cout << dist[i][j] << " ";
            }
        }
        cout << endl;
    }

    if (next[start][end] == -1)
    {
        cout << "No path exists from " << start << " to " << end << endl;
        return;
    }

    cout << "Shortest Path from " << start << " to " << end << ": " << start;
    while (start != end)
    {
        start = next[start][end];
        cout << " -> " << start;
    }
    cout << endl;
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


int main()
{
    int dist[N][N];
    int v, e;
    cin >> v >> e;

    for (int i = 0; i < v; ++i)
    {
        for (int j = 0; j < v; ++j)
        {
            if (i == j)
            {
                dist[i][j] = 0;
            }
            else
            {
                dist[i][j] = INT_MAX;
            }
        }
    }

    for (int i = 0; i < e; ++i)
    {
        int x, y, wt;
        cin >> x >> y >> wt;
        dist[x - 1][y - 1] = wt;
    }

    int start, end;
    cout << "Enter the start vertex: ";
    cin >> start;
    cout << "Enter the end vertex: ";
    cin >> end;

    floyd_warshall(dist, v, start - 1, end - 1);
    cout<<findMinDistance(dist, v);
    /*
    here is the code for finding the min elements storing them into  a vector and sorting them 
    vector<int> getElements(int dist[N][N], int v)
{
    vector<int> elements;

    for (int i = 0; i < v; ++i)
    {
        for (int j = 0; j < v; ++j)
        {
            if (dist[i][j] != INT_MAX)
            {
                elements.push_back(dist[i][j]);
            }
        }
    }

    return elements;
}

int findSecondMin(vector<int> elements)
{
    sort(elements.begin(), elements.end());
    
    if (elements.size() >= 2)
    {
        return elements[1]; // Assuming at least two elements are present
    }
    else
    {
        // Handle the case where there are not enough elements
        // Return a sentinel value or throw an exception
        // In this example, we'll return -1
        return -1;
    }
}

    
    */
    return 0;
}
