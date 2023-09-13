#include<bits/stdc++.h>
using namespace std;

typedef pair<int,int>temp1;
typedef vector<vector<temp1>> Gr;

vector<temp1> prim(Gr& graph){

    int sz=graph.size();
    vector<bool>visited(sz,false);
    vector<double>value(sz,INT_MAX);

    vector<temp1> tree;
    priority_queue<temp1,vector<temp1>,greater<temp1>>pqueue;
    value[0]=0;
    pqueue.push(make_pair(0,0));
    while(!pqueue.empty()){

        int temp=pqueue.top().second;
        pqueue.pop();
        visited[temp]=true;


    
    for(auto& p : graph[temp]){
        int v=p.first;
        int w=p.second;
        if(!visited[v] && w<value[v]){
            value[v]=w;
            pqueue.push({value[v],v});
        }
    }
    }
    for (int v = 1; v < sz; ++v) {
        tree.push_back(make_pair(v, value[v]));
    }
    return tree;
}
int main() {
    // Open the input file
    ifstream inputFile("input.txt");
    if (!inputFile) {
        cout << "Failed to open the input file." << endl;
        return 1;
    }

    int n, m;
    inputFile >> n >> m;

    // Create the graph
    Gr graph(n);

    for (int i = 0; i < m; ++i) {
        int u, v;
        double d;
        inputFile >> u >> v >> d;
        graph[u].push_back(make_pair(v, d));
        graph[v].push_back(make_pair(u, d));
    }

    inputFile.close();

    vector<temp1> mst = prim(graph);

    cout << "Minimum Spanning Tree:" << endl;
    for (const temp1& edge : mst) {
        int u = edge.first;
        double weight = edge.second;
        cout << u << " - " << weight << endl;
    }

    return 0;
}



