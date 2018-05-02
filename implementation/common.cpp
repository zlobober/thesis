#include "common.h"
#include <queue>

std::vector<int> CalculateDistances(const TAdjacencyMatrix& graph, int s, const std::vector<bool>& vertexIsBlocked)
{
    std::vector<int> distances(graph.size(), -1);
    if (!vertexIsBlocked.empty() && vertexIsBlocked[s]) {
        return distances;
    }
    std::queue<int> queue;
    distances[s] = 0;
    queue.push(s);
    while (!queue.empty()) {
        int u = queue.front();
        queue.pop();
        for (int v = 0; v < graph[u].size(); ++v) {
            if (graph[u][v] && distances[v] == -1 && (vertexIsBlocked.empty() || !vertexIsBlocked[v])) {
                distances[v] = distances[u] + 1;
                queue.push(v);
            }
        }
    }
    return distances;
}

std::vector<std::vector<int>> CalculateAllPairDistances(const TAdjacencyMatrix& graph)
{
    std::vector<std::vector<int>> distances(graph.size(), std::vector<int>(graph.size()));
    for (int i = 0; i < graph.size(); i++) {
        for (int j = 0; j < graph.size(); j++) {
            if (i == j) {
                distances[i][j] = 0;
            } else if (graph[i][j]) {
                distances[i][j] = 1;
            } else {
                distances[i][j] = graph.size();
            }
        }
    }
    for (int k = 0; k < graph.size(); k++) {
        for (int i = 0; i < graph.size(); i++) {
            for (int j = 0; j < graph.size(); j++) {
                distances[i][j] = std::min(distances[i][j], distances[i][k] + distances[k][j]);
            }
        }
    }
    for (int i = 0; i < graph.size(); i++) {
        for (int j = 0; j < graph.size(); j++) {
            if (distances[i][j] == graph.size()) {
                distances[i][j] = -1;
            }
        }
    }
    return distances;
}
