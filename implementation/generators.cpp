#include <iostream>
#include <functional>
#include <cstdlib>

#include "common.h"

bool GenerateEdge(int i, int j, TAdjacencyMatrix& graph, std::function<bool(TAdjacencyMatrix&)> callback)
{
    if (i == j) {
        if (!GenerateEdge(0, j + 1, graph, callback)) {
            return false;
        }
    } else if (j == graph.size()) {
        if (IsConnected(graph)) {
            return callback(graph);
        }
    } else {
        int f = rand() % 2;
        for (int t = 0; t < 2; ++t) {
            graph[i][j] = graph[j][i] = t ^ f;
            if (!GenerateEdge(i + 1, j, graph, callback)) {
                return false;
            }
            graph[i][j] = graph[j][i] = 0;
        }
    }
    return true;
}

void GenerateAll(int n, std::function<void(TAdjacencyMatrix&)> callback)
{
    TAdjacencyMatrix graph(n, std::vector<bool>(n, false));
    GenerateEdge(0, 1, graph, [&] (TAdjacencyMatrix& graph) { callback(graph); return true; });
}

void GenerateRandom(int n, std::function<void(TAdjacencyMatrix&)> callback)
{
    TAdjacencyMatrix graph(n, std::vector<bool>(n, false));
    GenerateEdge(0, 1, graph, [&] (TAdjacencyMatrix& graph) { callback(graph); return false; });
}
