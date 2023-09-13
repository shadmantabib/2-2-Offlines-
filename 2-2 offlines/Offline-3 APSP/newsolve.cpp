#include <iostream>
#include <fstream>
#include <unordered_map>
#include <vector>
#include <queue>
#include <climits>
#include <algorithm>

using namespace std;

typedef pair<string, int> StatePair;  // Pair of state name and travel time
typedef unordered_map<string, vector<StatePair>> Graph;

struct StateDistance {
    string state;
    int distance;

    StateDistance(const string& s, int d) : state(s), distance(d) {}

    bool operator>(const StateDistance& other) const {
        return distance > other.distance;
    }
};

vector<string> shortestPath(const Graph& graph, const string& start, const string& end) {
    unordered_map<string, int> distances;
    unordered_map<string, string> previous;

    for (const auto& entry : graph) {
        distances[entry.first] = INT_MAX;
    }
    distances[start] = 0;

    priority_queue<StateDistance, vector<StateDistance>, greater<StateDistance>> pq;
    pq.push(StateDistance(start, 0));

    while (!pq.empty()) {
        StateDistance current = pq.top();
        pq.pop();

        if (current.state == end)
            break;

        if (current.distance > distances[current.state])
            continue;

        const vector<StatePair>& neighbors = graph.at(current.state);
        for (const StatePair& neighbor : neighbors) {
            int newDistance = current.distance + neighbor.second;
            if (newDistance < distances[neighbor.first]) {
                distances[neighbor.first] = newDistance;
                previous[neighbor.first] = current.state;
                pq.push(StateDistance(neighbor.first, newDistance));
            }
        }
    }

    vector<string> path;
    string state = end;
    while (!state.empty()) {
        path.push_back(state);
        state = previous[state];
    }
    reverse(path.begin(), path.end());
    return path;
}

int main() {
    ifstream inputFile("inputss.txt");
    if (!inputFile) {
        cerr << "Failed to open the input file." << endl;
        return 1;
    }

    int n, f;
    inputFile >> n >> f;

    Graph graph;
    unordered_map<string, int> layoverTimes;

    for (int i = 0; i < n; ++i) {
        string state;
        int layoverTime;
        inputFile >> state >> layoverTime;
        layoverTimes[state] = layoverTime;
    }

    for (int i = 0; i < f; ++i) {
        string state1, state2;
        int travelTime;
        inputFile >> state1 >> state2 >> travelTime;
        graph[state1].emplace_back(state2, travelTime);
        graph[state2].emplace_back(state1, travelTime);
    }

    string start, end;
    inputFile >> start >> end;
    inputFile.close();

    vector<string> path = shortestPath(graph, start, end);
    int total_time = 0;
    for (size_t i = 0; i < path.size() - 1; ++i) {
        const string& state = path[i];
        total_time += layoverTimes[state] + graph[state][i].second;
    }

    ofstream outputFile("output.txt");
    if (!outputFile) {
        cerr << "Failed to open the output file." << endl;
        return 1;
    }

    outputFile << total_time << endl;
    for (size_t i = 0; i < path.size(); ++i) {
        outputFile << path[i];
        if (i != path.size() - 1)
            outputFile << " -> ";
    }
    outputFile.close();

    return 0;
}
