#pragma once

#include <memory>
#include <vector>

using TAdjacencyMatrix = std::vector<std::vector<bool>>;

//! Calculate distances from a given vertex to all others possibly ignoring the given blocked vertices.
std::vector<int> CalculateDistances(const TAdjacencyMatrix& graph, int s, const std::vector<bool>& vertexIsBlocked = std::vector<bool>());

//! Calculate all pairwise distances using the Floyd-Warshall algorithm.
std::vector<std::vector<int>> CalculateAllPairDistances(const TAdjacencyMatrix& graph);

struct ISolution
{
    virtual bool TwoShortestPathsExist(int s1, int t1, int s2, int t2) = 0;
    virtual std::string Description() const = 0;
};
