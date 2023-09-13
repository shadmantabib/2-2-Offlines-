#include <bits/stdc++.h>
using namespace std;
ifstream fin("input.txt");
ofstream fout("file_output3.txt");
const int N = 100;
const int INTMAX = 1000;
int n, m;
vector<vector<int>> mat, sp;
vector<vector<int>> next_vertex;

struct Mat
{
    int sz;
    int arr[N][N];
    Mat(int n)
    {
        sz = n;
        memset(arr, sizeof(arr), INTMAX);
    }
    void show()
    {

        for (int i = 0; i < sz; i++)
        {
            for (int j = 0; j < sz; j++)
            {
                cout << arr[i][j] << "";
                fout << arr[i][j] << "";
            }
            cout << endl;
            fout << endl;
        }
    }
};

Mat mult(Mat a, Mat b)
{
    int n = a.sz;
    Mat res(n);
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            res.arr[i][j] = INTMAX;
        }
    }
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            for (int k = 0; k < n; k++)
            {
                int new_dist = a.arr[i][k] + b.arr[k][j];
                if (new_dist < res.arr[i][j])
                {
                    res.arr[i][j] = new_dist;
                    next_vertex[i][j] = next_vertex[i][k];
                }
            }
        }
    }
    return res;
}

Mat repeatedSquare(Mat a, int p)
{
    if (p == 1)
    {
        return a;
    }
    Mat t = repeatedSquare(a, p / 2);
    t = mult(t, t);
    if (p % 2 == 1)
    {
        t = mult(t, a);
    }
    return t;
}

void APSP_using_MATMULT()
{
    Mat W(n);
    Mat SP(n);
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            W.arr[i][j] = mat[i][j];
            SP.arr[i][j] = mat[i][j];
        }
    }

    SP = repeatedSquare(W, n);

    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            sp[i][j] = SP.arr[i][j];
        }
    }
}

void floyd_warshall(int graph[N][N], int v)
{
    int dist[v][v];

    for (int i = 0; i < v; ++i)
        for (int j = 0; j < v; ++j)
            dist[i][j] = graph[i][j];

    for (int k = 0; k < v; ++k)
        for (int i = 0; i < v; ++i)
            for (int j = 0; j < v; ++j)
            {
                if (dist[i][k] == INT_MAX || dist[k][j] == INT_MAX)
                    continue;
                else if (dist[i][k] + dist[k][j] < dist[i][j])
                {
                    dist[i][j] = dist[i][k] + dist[k][j];
                    next_vertex[i][j] = next_vertex[k][j];
                }
            }

    for (int i = 0; i < v; ++i)
        if (dist[i][i] < 0)
        {
            cout << "Negative edge weight cycle is present\n";
            fout << "Negative edge weight cycle is present\n";
            return;
        }

    for (int i = 0; i < v; ++i)
    {
        for (int j = 0; j < v; ++j)
        {
            if (dist[i][j] == INT_MAX)
            {
                cout << "INF"
                     << " ";
                fout << "INF"
                     << " ";
            }
            else
            {
                cout << dist[i][j] << " ";
                fout << dist[i][j] << " ";
            }
        }
        cout << endl;
        fout << endl;
    }
}

void printPath(int start, int end)
{
    if (sp[start][end] == INTMAX)
    {
        cout << "No path exists from " << start << " to " << end << endl;
        fout << "No path exists from " << start << " to " << end << endl;
        return;
    }

    cout << "Shortest Path from " << start << " to " << end << ": " << start;
    fout << "Shortest Path from " << start << " to " << end << ": " << start;
    int current = start;
    while (current != end)
    {
        current = next_vertex[current][end];
        cout << " -> " << current;
        fout << " -> " << current;
    }
    cout << endl;
    fout << endl;
}

int main()
{
    int dist[N][N];
    int p, q;
    cout << "Which algorithm do you want to use?" << endl;
    cout << "For Floyd Warshall ---- press 1" << endl;
    cout << "For Matrix Multiplication ---- press 2" << endl;
    cin >> p;
    int v, e;
    fin >> v >> e;
    n = v;
    m = e;
    mat.resize(v, vector<int>(v, INTMAX));
    sp.resize(v, vector<int>(v, INTMAX));
    next_vertex.resize(v, vector<int>(v, -1));

    for (int i = 0; i < v; i++)
    {
        mat[i][i] = 0;
        sp[i][i] = 0;
        next_vertex[i][i] = i;
    }

    for (int i = 0; i < e; i++)
    {
        int x, y, wt;
        fin >> x >> y >> wt;
        dist[x - 1][y - 1] = wt;
        mat[x - 1][y - 1] = wt;
        sp[x - 1][y - 1] = wt;
        next_vertex[x - 1][y - 1] = y - 1;
    }

    if (p == 1)
    {
        cout << "Using Floyd Warshall " << endl;
        fout << "Using Floyd Warshall " << endl;
        cout << "Shortest Distance Matrix" << endl;
        fout << "Shortest Distance Matrix" << endl;
        floyd_warshall(dist, v);
    }
    else if (p == 2)
    {
        cout << "Using Matrix Multiplication " << endl;
        fout << "Using Matrix Multiplication " << endl;
        cout << "Shortest Distance Matrix" << endl;
        fout << "Shortest Distance Matrix" << endl;
        APSP_using_MATMULT();
        for (int i = 0; i < v; i++)
        {
            for (int j = 0; j < v; j++)
            {
                if (sp[i][j] == INTMAX)
                {
                    cout << "INF"
                         << " ";
                    fout << "INF"
                         << " ";
                }
                else
                {
                    cout << sp[i][j] << " ";
                    fout << sp[i][j] << " ";
                }
            }
            cout << endl;
            fout << endl;
        }
    }

    // Example: Print path from vertex 1 to vertex 3
    int start = 0; // vertex 1
    int end = 2;   // vertex 3
    printPath(start, end);

    return 0;
}
