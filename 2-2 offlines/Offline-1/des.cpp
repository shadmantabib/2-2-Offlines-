#include <bits/stdc++.h>
using namespace std;
ifstream fin("targets.txt");
const int N = 1e5 + 10;
int parent[N];
int size[N];
struct Edge
{
    int src, dest;
    double weight;
};
struct Subset
{
    int parent, rank;
};
int findsub(vector<Subset> &subsets, int i)
{
    if (subsets[i].parent != i)
        subsets[i].parent = findsub(subsets, subsets[i].parent);
    return subsets[i].parent;
}
void unionSubsets(vector<Subset> &subsets, int x, int y)
{
    int xroot = findsub(subsets, x);
    int yroot = findsub(subsets, y);
    if (subsets[xroot].rank < subsets[yroot].rank)
        subsets[xroot].parent = yroot;
    else if (subsets[xroot].rank > subsets[yroot].rank)
        subsets[yroot].parent = xroot;
    else
    {
        subsets[yroot].parent = xroot;
        subsets[xroot].rank++;
    }
}
void make(int v)
{
    parent[v] = v;
    size[v] = 1;
}
int find(int v)
{
    if (v == parent[v])
        return v;
    return parent[v] = find(parent[v]);
}
// reverse acjerman function
void Union(int a, int b)
{
    a = find(a);
    b = find(b);
    if (a != b)
    {
        if (size[a] < size[b])
        {
            swap(a, b);
        }
        parent[b] = a;
        size[a] += size[b];
    }
}
int main()
{

    int V, m;
    fin >> V >> m;
    vector<Edge> result;
    vector<Subset> subsets(V);
    vector<Subset> subsets2(V);
    for (int i = 0; i < V; i++)
    {
        subsets[i].parent = i;
        subsets[i].rank = 0;
    }

    vector<Edge> edges1;
    vector<Edge> edges2;
    vector<Edge> edges3;

    for (int i = 0; i < m; ++i)
    {
        Edge edge;
        int u, v;
        double weight;
        fin >> u >> v >> weight;
        cout << u << v << weight << endl;
        edge.src = u - 1;
        edge.dest = v - 1;
        edge.weight = weight;
        if (weight == 3)
        {
            edges3.push_back(edge);
        }
        if (weight == 2)
        {
            edges2.push_back(edge);
        }
        if (weight == 1)
        {
            edges1.push_back(edge);
        }
    }

    for (auto i : edges1)
    {
        cout<<"edges1" << i.src << endl;
    }
    int index = 0;
    set<int> verticesSet;
    set<int> verticesSetstore;
    while (index < edges3.size())
    {
        cout << "hello" << endl;
        Edge nextEdge = edges3[index++];
        int srcParent = findsub(subsets, nextEdge.src);
        int destParent = findsub(subsets, nextEdge.dest);

        if (srcParent != destParent)
        {
            result.push_back(nextEdge);
            verticesSet.insert(nextEdge.src);
            verticesSet.insert(nextEdge.dest);
            unionSubsets(subsets, srcParent, destParent);
            cout << "notice" << endl;
        }
    }
    for (const auto &element : verticesSet)
    {
        verticesSetstore.insert(element);
    }
    cout << verticesSet.size() << endl;

    for (auto it : result)
    {
        cout << it.src << " " << it.dest << endl;
    }
    cout << V << "V size" << endl;
    cout << subsets.size() << endl;
    subsets2=subsets;

    if (verticesSet.size() < V)
    {
        int index = 0;
        while (verticesSet.size() <= V)
        {
            cout << "hellothere" << V << endl;
            Edge nextEdge = edges2[index++];
            int srcParent = findsub(subsets, nextEdge.src);
            int destParent = findsub(subsets, nextEdge.dest);
            cout << verticesSet.size() << endl;
            if (verticesSet.size() == V)
            {
                break;
            }
            if (srcParent != destParent)
            {
                result.push_back(nextEdge);
                verticesSet.insert(nextEdge.src);
                verticesSet.insert(nextEdge.dest);
                unionSubsets(subsets, srcParent, destParent);
                cout << "notice" << endl;
            }
        }
    }
    cout << subsets.size() << endl;
    cout << verticesSetstore.size() << V<<endl;
    for(auto i: verticesSetstore){
        cout<<i<<endl;
    }
    if (verticesSetstore.size() < V)
    {
        int index = 0;
        while (verticesSetstore.size() <= V && index<edges1.size())
        {
            cout << "hellotheressss " << V << endl;
            Edge nextEdge = edges1[index++];
            int srcParent = findsub(subsets2, nextEdge.src);
            int destParent = findsub(subsets2, nextEdge.dest);
            cout << verticesSetstore.size() << endl;

            if (verticesSetstore.size() == V)
            {
                break;
            }
            if (srcParent != destParent)
            {
                result.push_back(nextEdge);
                verticesSetstore.insert(nextEdge.src);
                verticesSetstore.insert(nextEdge.dest);
                unionSubsets(subsets2, srcParent, destParent);
                cout << "notice" << endl;
            }
        }
    }
    cout<<m-result.size()<<endl;
}
