#include <bits/stdc++.h>
using namespace std;
ifstream fin("input.txt");
ofstream fout("file_output.txt");
const int N = 100;
const int INTMAX = 1000;
int n, m;
vector<vector<int>> mat, sp;
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
                res.arr[i][j] = min(res.arr[i][j], a.arr[i][k] + b.arr[k][j]);
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

    /*fo(i,n){
        SP=mult(SP,W);

    }*/
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
                    dist[i][j] = dist[i][k] + dist[k][j];
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
int main()
{
    int dist[N][N];
    int p, q;
    cout << "Which algorithm do you want to use?" << endl;
    cout << "For Floyd Warshall----press 1" << endl;
    cout << "For Matrix Multiplication----press 2" << endl;
    cin >> p;
    int v, e;
    // cin >> v >> e;1

    fin >> v >> e;
    n = v;
    m = e;
    mat.resize(v, vector<int>(v, INTMAX));
    sp.resize(v, vector<int>(v, INTMAX));
    for (int i = 0; i < v; i++)
    {
        mat[i][i] = 0;
    }
    for (int i = 0; i < v; i++)
    {
        for (int j = 0; j < v; j++)
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

    for (int i = 0; i < e; i++)
    {
        int x, y, wt;
        fin >> x >> y >> wt;
        // cin >> x >> y >> wt;

        dist[x - 1][y - 1] = wt;
        mat[x - 1][y - 1] = wt;
        sp[x - 1][y - 1] = wt;
    }

    if (p == 1)
    {
        cout << "Using floyd warshall " << endl;
        fout << "Using floyd warshall " << endl;
        cout << "Shortest Distance Matrix" << endl;
        fout << "Shortest Distance Matrix" << endl;
        floyd_warshall(dist, v);
    }
    else if (p == 2)
    {
        cout << "Using matrix multiplication " << endl;
        fout << "Using matrix multiplication " << endl;
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
}
