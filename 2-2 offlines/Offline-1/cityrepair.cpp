// Add some code
#include <bits/stdc++.h>

using namespace std;

struct NewData
{
    string city1, city2;
    int cost;
};

bool operator<(const NewData& d1, const NewData& d2)
{
    return d1.cost < d2.cost;
}

vector<NewData> graph;
map<string, bool> Checked;
map<string, string> parent;
set<string> st;
map<string, set<string>> mp;

void ClearAll()
{
    graph.clear();
    Checked.clear();
    parent.clear();
    st.clear();
    mp.clear();
}

string findParent(const string& s)
{
    if (parent[s] == s)
        return s;
    return findParent(parent[s]);
}

int MinCost()
{
    int res = 0;
    for (const auto& x : st)
    {
        parent[x] = x;
    }
    for (const auto& x : graph)
    {
        const string& s = x.city1;
        const string& s2 = x.city2;
        string ps = findParent(s);
        string ps2 = findParent(s2);
        if (ps != ps2)
        {
            res += x.cost;
            parent[ps2] = ps;
        }
    }
    return res;
}

int bfs(const string& s)
{
    int res = 0;
    queue<string> q;
    q.push(s);
    Checked[s] = true;
    res++;
    while (!q.empty())
    {
        const string& cur = q.front();
        q.pop();
        for (const auto& x : mp[cur])
        {
            if (!Checked[x])
            {
                Checked[x] = true;
                q.push(x);
                res++;
            }
        }
    }
    return res;
}

int main()
{
    int t, cs = 1;
    cin >> t;
    while (t--)
    {
        int n;
        cin >> n;
        ClearAll();
        while (n--)
        {
            NewData connection;
            cin >> connection.city1 >> connection.city2 >> connection.cost;
            graph.push_back(connection);
            st.insert(connection.city1);
            st.insert(connection.city2);
            mp[connection.city1].insert(connection.city2);
            mp[connection.city2].insert(connection.city1);
        }
        sort(graph.begin(), graph.end());
        string ans = "";
        int mnCost = MinCost();
        if (bfs(*st.begin()) != st.size())
            ans = "Impossible\n";
        cout << "Case " << cs++ << ": ";
        if (!ans.empty())
            cout << ans;
        else
            cout << mnCost << endl;
    }
    return 0;
}
