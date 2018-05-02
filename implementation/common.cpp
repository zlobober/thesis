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
