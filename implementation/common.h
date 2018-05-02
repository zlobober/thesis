#pragma once

#include <memory>
#include <vector>

using TAdjacencyMatrix = std::vector<std::vector<bool>>;

std::vector<int> CalculateDistances(const TAdjacencyMatrix& graph, int s, const std::vector<bool>& vertexIsBlocked = std::vector<bool>());

struct ISolution
{
    virtual bool TwoShortestPathsExist(int s1, int t1, int s2, int t2) = 0;
    virtual std::string Description() const = 0;
};
