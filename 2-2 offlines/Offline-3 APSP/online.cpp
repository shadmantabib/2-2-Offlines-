#include <iostream>
#include <fstream>
#include <vector>
#include <limits>
using namespace std;

const int N = 100;
const int INTMAX = 1000;

vector<vector<int>> mat, sp;

void showMatrix(const vector<vector<int>>& matrix, int size, ofstream& fout)
{
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            if (matrix[i][j] == INTMAX) {
                cout << "INF" << " ";
                fout << "INF" << " ";
            } else {
                cout << matrix[i][j] << " ";
                fout << matrix[i][j] << " ";
            }
        }
        cout << endl;
        fout << endl;
    }
}

vector<vector<int>> matrixMultiplication(const vector<vector<int>>& a, const vector<vector<int>>& b)
{
    int n = a.size();
    vector<vector<int>> res(n, vector<int>(n, INTMAX));

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            res[i][j] = INTMAX;
        }
    }

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            for (int k = 0; k < n; k++) {
                res[i][j] = min(res[i][j], a[i][k] + b[k][j]);
            }
        }
    }

    return res;
}

vector<vector<int>> repeatedSquare(const vector<vector<int>>& a, int p)
{
    int n = a.size();
    if (p == 1) {
        return a;
    }

    vector<vector<int>> t = repeatedSquare(a, p / 2);
    t = matrixMultiplication(t, t);
    if (p % 2 == 1) {
        t = matrixMultiplication(t, a);
    }

    return t;
}

void APSP_using_MATMULT()
{
    int n = mat.size();
    vector<vector<int>> res(n, vector<int>(n, INTMAX));

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            res[i][j] = mat[i][j];
        }
    }

    res = repeatedSquare(res, n);

    sp = res;
}

void floydWarshall(int v)
{
    int n = mat.size();
    vector<vector<int>> dist(mat);

    for (int k = 0; k < n; ++k) {
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j) {
                if (dist[i][k] != INTMAX && dist[k][j] != INTMAX && dist[i][k] + dist[k][j] < dist[i][j]) {
                    dist[i][j] = dist[i][k] + dist[k][j];
                }
            }
        }
    }

    for (int i = 0; i < n; ++i) {
        if (dist[i][i] < 0) {
            cout << "Yes" << endl;
            return;
        }
        
    }
    
            cout<<"No"<<endl;
        

    sp = dist;
}

int main()
{
    ifstream fin("inputo.txt");
    ofstream fout("file_output8.txt");

    int dist[N][N];
    int p, v, e;
   // cout << "Which algorithm do you want to use?" << endl;
    //cout << "For Floyd Warshall ---- press 1" << endl;
    //cout << "For Matrix Multiplication ---- press 2" << endl;
     p=1;

    fin >> v >> e;
    mat.resize(v, vector<int>(v, INTMAX));
    sp.resize(v, vector<int>(v, INTMAX));

    for (int i = 0; i < v; i++) {
        mat[i][i] = 0;
    }

    for (int i = 0; i < e; i++) {
        int x, y, wt;
        fin >> x >> y >> wt;

        mat[x - 1][y - 1] = wt;
        sp[x - 1][y - 1] = wt;
    }

    if (p == 1) {
        //cout << "Using Floyd Warshall" << endl;
        //fout << "Using Floyd Warshall" << endl;
        //cout << "Shortest Distance Matrix" << endl;
        //fout << "Shortest Distance Matrix" << endl;
        floydWarshall(v);
        //showMatrix(sp, v, fout);
    } else if (p == 2) {
        cout << "Using Matrix Multiplication" << endl;
        fout << "Using Matrix Multiplication" << endl;
        cout << "Shortest Distance Matrix" << endl;
        fout << "Shortest Distance Matrix" << endl;
        APSP_using_MATMULT();
        showMatrix(sp, v, fout);
    }

    fin.close();
    fout.close();
    return 0;
}
