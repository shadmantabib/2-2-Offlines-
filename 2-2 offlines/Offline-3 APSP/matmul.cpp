#include <bits/stdc++.h>
using namespace std;
#define fo(i, n) for (int i = 0; i < n; i++)
const int inf = 1000;
int n, m;
vector<vector<int>> mat, sp;

const int N = 100;
struct Mat
{
    int sz;
    int arr[100][100];
    Mat(int n)
    {
        sz = n;
        memset(arr,sizeof(arr),inf);
    }
    void show(){
        
        fo(i,sz){
            fo(j,sz){
                cout<<arr[i][j]<<"";
            }
            cout<<endl;
        }
        
    }
};

Mat mult(Mat a, Mat b)
{
    int n=a.sz;
    Mat res(n);
    fo(i,n){
        fo(j,n){
        res.arr[i][j] = inf;
    
        }
    }
    fo(i, n)
    {
        fo(j, n)
        {
            fo(k, n)
            {
                res.arr[i][j]=min(res.arr[i][j],a.arr[i][k]+b.arr[k][j]);
            }
        }
    }
    return res;
}
Mat Power(Mat a,int p){
    if(p==1){
        return a;
    }
    Mat t=Power(a,p/2);
    t=mult(t,t);
    if(p%2==1){
        t=mult(t,a);
    }
    return t;


}
void smapsp(){
    Mat W(n);
    Mat SP(n);
    fo(i,n){
        fo(j,n){
            W.arr[i][j]=mat[i][j];
            SP.arr[i][j]=mat[i][j];
        }
    }
    /*fo(i,n){
        SP=mult(SP,W);

    }*/
    SP=Power(W,n);
    fo(i,n){
        fo(j,n){
            sp[i][j]=SP.arr[i][j];
        }
    }
}

int main()
{

    int u, v, w;

    cin >> n >> m;
    mat.resize(n + 5, vector<int>(n + 5, inf));
    sp.resize(n + 5, vector<int>(n + 5, inf));
    fo(i,n){
        mat[i][i]=0;
    }
    fo(i, m)
    {
        cin >> u >> v >> w;
        mat[u-1][v-1] = w;
        sp[u-1][v-1] = w;
    }
    smapsp();
    fo(i, n)
    {
        fo(j, n)
        {
            cout << sp[i][j] << " ";
        }
        cout << endl;
    }
}