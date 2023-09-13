#include <vector>

// Define a helper function to find the parent (representative) of a vertex
int findParent(int vertex, std::vector<int>& parent) {
    if (parent[vertex] == vertex)
        return vertex;
    return findParent(parent[vertex], parent);
}

// Define a helper function to perform the union of two sets
void unionSets(int u, int v, std::vector<int>& parent) {
    int parentU = findParent(u, parent);
    int parentV = findParent(v, parent);
    parent[parentV] = parentU;
}

// Function to check if adding an edge creates a cycle
bool createsCycle(int u, int v, std::vector<int>& parent) {
    int parentU = findParent(u, parent);
    int parentV = findParent(v, parent);
    return parentU == parentV; // If they are the same, a cycle is created
}

bool hasCycle(const std::vector<std::pair<int, int>>& edges, int numVertices) {
    std::vector<int> parent(numVertices);
    // Initialize parent of each vertex as itself
    for (int i = 0; i < numVertices; ++i) {
        parent[i] = i;
    }

    for (const auto& edge : edges) {
        int u = edge.first;
        int v = edge.second;

        // Check if adding this edge creates a cycle
        if (createsCycle(u, v, parent)) {
            return true; // Cycle is detected
        }

        // Merge the sets representing the endpoints of the edge
        unionSets(u, v, parent);
    }

    return false; // No cycle is found
}
