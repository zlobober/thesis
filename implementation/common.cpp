#include "common.h"

#include <iostream>
#include <algorithm>
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

bool IsConnected(const TAdjacencyMatrix& graph)
{
    if (graph.empty()) {
        return true;
    }
    auto distances = CalculateDistances(graph, 0);
    return std::find(distances.begin(), distances.end(), -1) == distances.end();
}

void PrintGraph(const TAdjacencyMatrix& graph)
{
    std::cout << graph.size() << std::endl;
    for (int i = 0; i < graph.size(); ++i) {
        for (int j = 0; j < graph.size(); ++j) {
            std::cout << graph[i][j];
        }
        std::cout << std::endl;
    }
}

bool ReadGraph(TAdjacencyMatrix& graph)
{
    int n;
    if (!(std::cin >> n)) {
        return false;
    }

    graph.assign(n, std::vector<bool>(n, false));
    for (int i = 0; i < n; i++) {
        std::string row;
        std::cin >> row;
        for (int j = 0; j < n; j++) {
            if (row[j] == '1') {
                graph[i][j] = true;
            }
        }
    }
    return true;
}
