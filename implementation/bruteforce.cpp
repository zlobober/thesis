#include "bruteforce.h"

#include <string>
#include <queue>
#include <iostream>

class TBruteforceSolution
    : public ISolution
{
public:
    TBruteforceSolution(TAdjacencyMatrix graph)
        : Graph_(std::move(graph))
    { }

    virtual std::string Description() const override
    {
        return "bruteforce";
    }

    virtual bool TwoShortestPathsExist(int s1, int t1, int s2, int t2) override
    {
        S1_ = s1;
        T1_ = t1;
        S2_ = s2;
        T2_ = t2;
        VertexIsBlocked_.assign(Graph_.size(), false);

        DistancesFromT1_ = CalculateDistances(Graph_, t1);
        auto distancesFromT2_ = CalculateDistances(Graph_, t2);
        S2T2Distance_ = distancesFromT2_[s2];

        return DoBruteforce(s1);
    }

private:
    TAdjacencyMatrix Graph_;
    std::vector<bool> VertexIsBlocked_;
    std::vector<int> DistancesFromT1_;
    int S1_ = -1, T1_ = -1, S2_ = -1, T2_ = -1;
    int S2T2Distance_ = -1;

    bool DoBruteforce(int currentVertex)
    {
        VertexIsBlocked_[currentVertex] = true;
        if (currentVertex == T1_) {
            auto distancesFromT2 = CalculateDistances(Graph_, T2_, VertexIsBlocked_);
            if (distancesFromT2[S2_] == S2T2Distance_) {
                return true;
            }
        } else {
            for (int nextVertex = 0; nextVertex < Graph_.size(); ++nextVertex) {
                if (Graph_[currentVertex][nextVertex] && DistancesFromT1_[nextVertex] == DistancesFromT1_[currentVertex] - 1) {
                    if (DoBruteforce(nextVertex)) {
                        return true;
                    }
                }
            }
        }
        VertexIsBlocked_[currentVertex] = false;
        return false;
    }
};

std::unique_ptr<ISolution> CreateBruteforceSolution(TAdjacencyMatrix graph)
{
    return std::make_unique<TBruteforceSolution>(std::move(graph));
}
