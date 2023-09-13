#include<bits/stdc++.h>
using namespace std;
const int N = 100;


void floyd_warshall(int graph[N][N],int v)
{
	int dist[v][v];

	
	for(int i=0;i<v;++i)
		for(int j=0;j<v;++j)
			dist[i][j] = graph[i][j];

	
	for(int k=0;k<v;++k)	
		for(int i=0;i<v;++i)	
			for(int j=0;j<v;++j)	
			{
				if(dist[i][k]==INT_MAX || dist[k][j]==INT_MAX)	
					continue;
				else if(dist[i][k]+dist[k][j] < dist[i][j])		
					dist[i][j] = dist[i][k] + dist[k][j];
			}

	
	for(int i=0;i<v;++i)
		if(dist[i][i] < 0)
		{
			cout<<"Negative edge weight cycle is present\n";
			return;
		}

	
	for(int i=0;i<v;++i)
	{
		for(int j=0;j<v;++j){
            if(dist[i][j]==INT_MAX){
                cout<<"INF"<<" ";
            }
            else{
			cout<<dist[i][j]<<" ";
            }
        }cout<<endl;
	}
}
int main()
{   
    int dist[N][N];
    int v,e;
    cin>>v>>e;
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
  
  
  for(int i = 0; i < e; i++){
    int x,y,wt;
    cin>>x>>y>>wt;
    dist[x-1][y-1]=wt;

  }
	

	floyd_warshall(dist,v);
	return 0;
}
