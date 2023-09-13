#include <bits/stdc++.h>
using namespace std;

const int INTMAX = 1000;
int n, m;
vector<vector<int>> mat, sp;

const int N = 100;
struct Mat
{
    int sz;
    int arr[N][N];
    Mat(int n)
    {
        sz = n;
        memset(arr,sizeof(arr),INTMAX);
    }
    void show(){
        
        for(int i=0;i<sz;i++){
            for(int j=0;j<sz;j++){
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
   for(int i=0;i<n;i++){
        for(int j=0;j<n;j++){
        res.arr[i][j] = INTMAX;
    
        }
    }
    for(int i=0;i<n;i++)
    {
        for(int j=0;j<n;j++)
        {
            for(int k=0;k<n;k++)
            {
                res.arr[i][j]=min(res.arr[i][j],a.arr[i][k]+b.arr[k][j]);
            }
        }
    }
    return res;
}
Mat repeatedSquare(Mat a,int p){
    if(p==1){
        return a;
    }
    Mat t=repeatedSquare(a,p/2);
    t=mult(t,t);
    if(p%2==1){
        t=mult(t,a);
    }
    return t;


}
void smapsp(){
    Mat W(n);
    Mat SP(n);
   for(int i=0;i<n;i++){
        for(int j=0;j<n;j++){
            W.arr[i][j]=mat[i][j];
            SP.arr[i][j]=mat[i][j];
        }
    }
    /*fo(i,n){
        SP=mult(SP,W);

    }*/
    SP=repeatedSquare(W,n);
   for(int i=0;i<n;i++){
        for(int j=0;j<n;j++){
            sp[i][j]=SP.arr[i][j];
        }
    }
}

int main()
{

    int u, v, w;

    cin >> n >> m;
    mat.resize(n + 5, vector<int>(n + 5, INTMAX));
    sp.resize(n + 5, vector<int>(n + 5, INTMAX));
   for(int i=0;i<n;i++){
        mat[i][i]=0;
    }
    for(int i=0;i<m;i++)
    {
        cin >> u >> v >> w;
        mat[u-1][v-1] = w;
        sp[u-1][v-1] = w;
    }
    smapsp();
    for(int i=0;i<n;i++)
    {
        for(int j=0;j<n;j++)
        {
            if(sp[i][j]==INTMAX){
                cout<<"INF"<<" ";
            }
            else{
            cout << sp[i][j] << " ";
            }
        }
        cout << endl;
    }
}