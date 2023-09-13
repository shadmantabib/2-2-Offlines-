#include<bits/stdc++.h>
using namespace std;
ofstream fout("outs.txt");
#define MX 105
#define INF 1000000000

struct node {
    int val;
    int cost;
  
    vector<int> path;
};


vector<node> G[MX];
vector<node> G1[MX];
bool vis[MX];
int dist[MX];


void reset() {
    for (int i = 0; i < MX; i++) {
        G[i].clear();
        G1[i].clear();
        vis[i] = 0;
        dist[i] = INF;
    }
}

class cmp {
public:
    bool operator() (node& A, node& B) {
        if (A.cost > B.cost) return true;
        return false;
    }
};
/*
void bellmanFord(int source, int destination) {
    dist[source] = 0;
    vector<int> parent(MX, -1);
    bool updated;

    for (int i = 1; i <= MX - 1; i++) {
        updated=false;
        for (int u = 0; u < MX; u++) {
            for (int j = 0; j < G[u].size(); j++) {
                int v = G1[u][j].val;
                int w = G1[u][j].cost;

                if (dist[u] != INF && dist[u] + w < dist[v]) {
                    dist[v] = dist[u] + w;
                    parent[v] = u;
                    updated=true;
                }
            }
            if(updated==false){
                break;
            }
        }
    }
    cout<<"Here is the flag"<<updated<<endl;

    for (int u = 0; u < MX; u++) {
        for (int j = 0; j < G1[u].size(); j++) {
            int v = G1[u][j].val;
            int w = G1[u][j].cost;

            if (dist[u] != INF && dist[u] + w < dist[v]) {
                cout << "Bellman-Ford Algorithm:\n";
                fout << "Bellman-Ford Algorithm:\n";
                cout << "Negative weight cycle present\n";
                fout << "Negative weight cycle present\n";
                return;
            }
        }
    }

    if (dist[destination] == INF) {
        cout << "No path found from source to destination.\n";
        fout << "No path found from source to destination.\n";
    } else {
        cout << "Bellman-Ford Algorithm:\n";
        fout << "Bellman-Ford Algorithm:\n";
        cout << "Minimum cost: " << dist[destination] << "\n";
        fout << "Minimum cost: " << dist[destination] << "\n";
        cout << "Path: ";
        fout << "Path: ";

        vector<int> path;
        int current = destination;
        path.push_back(current);

        while (parent[current] != -1) {
            current = parent[current];
            path.push_back(current);
        }
       // cout<<source<<" -> ";
       // fout<<source<<" -> ";
        reverse(path.begin(), path.end());
        for (int i = 0; i < path.size(); i++) {
            if (i == 0) {
                cout << path[i];
                fout << path[i];
            } else {
                cout << " -> " << path[i];
                fout << " -> " << path[i];
            }
        }
        cout << endl;
        fout << endl;
    }
}
*/
void dijkstra(int source, int destination,int gr[]) {
    priority_queue<node, vector<node>, cmp> PQ;
    PQ.push({source, gr[0], {source}});

    while (!PQ.empty()) {
        node current = PQ.top();
        PQ.pop();

        int val = current.val;
        int cost = current.cost;
       
        vector<int> path = current.path;

        if (vis[val] == 1) continue;

        dist[val] = cost;
        vis[val] = 1;

        if (val == destination) {
            cout << "Dijkstra Algorithm:\n";
            fout << "Dijkstra Algorithm:\n";
            for(int i=0;i<path.size()-1;i++){
                cost=cost-gr[path[i]];
            }
            cout << "Minimum cost: " << cost << "\n";
            fout << "Minimum cost: " << cost << "\n";
            cout << "Path: ";
            fout << "Path: ";
            for (int i = 0; i < path.size(); i++) {
                if (i == 0) {
                    cout << path[i];
                    fout << path[i];
                } else {
                    cout << " -> " << path[i];
                    fout << " -> " << path[i];
                }
            }
            cout << endl;
            fout << endl;
            cout<<dist[path[2]]<<endl;
            return;
        }

        for (int i = 0; i < G[val].size(); i++) {
            int nxt = G[val][i].val;
            int nxtCost = G[val][i].cost;
           
            if (vis[nxt] == 0) {
                vector<int> newPath = path;
                newPath.push_back(nxt);
                PQ.push({nxt, cost + nxtCost, newPath});
            }
        }
    }

    cout << "No path found from source to destination.\n";
    fout << "No path found from source to destination.\n";
}
int find(string p,vector<string> &city)
{
    for(int i=0;i<city.size();i++){
        if(city[i]=="p"){
            return i;
        }
    }
}

int main() {
    reset();
    ifstream fin("ion.txt");
    int nodes, edges;
    int gr[nodes];
    
    fin >> nodes >> edges;
    map<string,int> mymap;
 
    // mapping strings to integers
    mymap["Cal"] = 0;
    mymap["Rho"] = 1;
    mymap["Vir"] = 2;
    mymap["Neb"] = 3;
    mymap["low"] = 4;
     mymap["Flo"] = 5;
     mymap["Con"] = 6;
      mymap["Mis"] = 7;
       mymap["Mas"] = 8;
        mymap["Njy"] = 9; 
    vector<string> city;
 
    // printing the integer mapped
    // by string "thanks"
    cout << mymap.at("thanks");
    
    
    for(int i = 0; i < nodes; i++){
            
            string ver;
            int cva;
            fin>>ver>>cva;
            city[i]=ver;
           
    }
    for (int i = 0; i < edges; i++) {
        string u,v;
        int w;
        fin >> u >> v >> w;

        G[find(u,city)].push_back({find(v,city), abs(w)+gr[find(u,city)]+gr[find(v,city)]});
        //G1[u].push_back({v, w});
    }

    string source, destination;
    
    fin >> source >> destination;
    //bellmanFord(source, destination);

    dijkstra(find(source,city), find(destination,city),gr);
    

    return 0;
}
