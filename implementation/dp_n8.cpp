#include "dp_n8.h"

#include "common.h"

#include <unordered_set>
#include <algorithm>
#include <cassert>

class TDynamicProgrammingN8Solution
    : public ISolution
{
public:
    TDynamicProgrammingN8Solution(TAdjacencyMatrix graph)
        : Graph_(std::move(graph))
        , N_(Graph_.size())
    {
        Distances_ = CalculateAllPairDistances(Graph_);
        PairsByDistance_.resize(N_);
        for (int s = 0; s < N_; ++s) {
            for (int t = 0; t < N_; ++t) {
                assert(Distances_[s][t] != -1);
                PairsByDistance_[Distances_[s][t]].emplace_back(s, t);
            }
        }

        IsValid_.resize(N_);
        for (int s1 = 0; s1 < N_; ++s1) {
            IsValid_[s1].resize(N_);
            for (int t1 = 0; t1 < N_; ++t1) {
                IsValid_[s1][t1].resize(N_);
                for (int s2 = 0; s2 < N_; ++s2) {
                    IsValid_[s1][t1][s2].resize(N_);
                    for (int t2 = 0; t2 < N_; ++t2) {
                        IsValid_[s1][t1][s2][t2] = -1;
                    }
                }
            }
        }

        for (int d1 = 0; d1 < N_; d1++) {
            for (int d2 = 0; d2 < N_; d2++) {
                for (const auto& st1 : PairsByDistance_[d1]) {
                    for (const auto& st2 : PairsByDistance_[d2]) {
                        CheckQuadruple(st1.first, st1.second, st2.first, st2.second);
                    }
                }
            }
        }
    }

    virtual std::string Description() const override
    {
        return "dynamic_programming_in_N^8";
    }

    virtual bool TwoShortestPathsExist(int s1, int t1, int s2, int t2) override
    {
        auto result = IsValid_[s1][t1][s2][t2];
        assert(result != -1);
        return result == 1;
    }

private:
    TAdjacencyMatrix Graph_;
    int N_;
    std::vector<std::vector<int>> Distances_;
    std::vector<std::vector<std::vector<std::vector<char>>>> IsValid_;
    std::vector<std::vector<std::pair<int, int>>> PairsByDistance_;

    bool IsBetween(int s, int t, int x) const {
        return Distances_[s][t] == Distances_[s][x] + Distances_[x][t];
    }

    void CheckQuadruple(int s1, int t1, int s2, int t2) {
        bool isValid = false;
        if (s1 == t1 && s2 == t2 && s1 != s2) {
            isValid = true;
        } else if (!IsBetween(s2, t2, s1) && s1 != t1) {
            isValid = AnyValid(AdjacentBetween(s1, t1), {t1}, {s2}, {t2});
        } else if (!IsBetween(s2, t2, t1) && s1 != t1) {
            isValid = AnyValid({s1}, AdjacentBetween(t1, s1), {s2}, {t2});
        } else if (!IsBetween(s1, t1, s2) && s2 != t2) {
            isValid = AnyValid({s1}, {t1}, AdjacentBetween(s2, t2), {t2});
        } else if (!IsBetween(s1, t1, t2) && s2 != t2) {
            isValid = AnyValid({s1}, {t1}, {s2}, AdjacentBetween(t2, s2));
        } else {
            isValid |= AnyValid({s1}, AdjacentBetween(t1, s1, s2), {s2}, AdjacentBetween(t2, s2, s1));
            isValid |= AnyValid(AdjacentBetween(s1, t1, s2), {t1}, {s2}, AdjacentBetween(t2, s2, t1));
            isValid |= AnyValid({s1}, AdjacentBetween(t1, s1, t2), AdjacentBetween(s2, t2, s1), {t2});
            isValid |= AnyValid(AdjacentBetween(s1, t1, t2), {t1}, AdjacentBetween(s2, t2, t1), {t2});
            std::vector<bool> C(N_);
            for (int x = 0; x < N_; ++x) {
                if (IsBetween(s1, s2, x) || IsBetween(s1, t2, x) || IsBetween(t1, s2, x) || IsBetween(t1, t2, x)) {
                    C[x] = true;
                }
            }
            isValid |= AnyValid(AdjacentNotIn(s1, t1, C), {t1}, AdjacentNotIn(s2, t2, C), {t2});
            isValid |= AnyValid(AdjacentNotIn(s1, t1, C), {t1}, {s2}, AdjacentNotIn(t2, s2, C));
            isValid |= AnyValid({s1}, AdjacentNotIn(t1, s1, C), AdjacentNotIn(s2, t2, C), {t2});
            isValid |= AnyValid({s1}, AdjacentNotIn(t1, s1, C), {s2}, AdjacentNotIn(t2, s2, C));

            isValid |= AnyValid({s1}, AdjacentBetween(t1, s1, s2), {s2}, AdjacentNotIn(t2, s2, C));
            isValid |= AnyValid({s1}, AdjacentBetween(t1, s1, t2), AdjacentNotIn(s2, t2, C), {t2});
            isValid |= AnyValid(AdjacentBetween(s1, t1, s2), {t1}, {s2}, AdjacentNotIn(t2, s2, C));
            isValid |= AnyValid(AdjacentBetween(s1, t1, t2), {t1}, AdjacentNotIn(s2, t2, C), {t2});
            isValid |= AnyValid({s1}, AdjacentNotIn(t1, s1, C), {s2}, AdjacentBetween(t2, s2, s1));
            isValid |= AnyValid(AdjacentNotIn(s1, t1, C), {t1}, {s2}, AdjacentBetween(t2, s2, t1));
            isValid |= AnyValid({s1}, AdjacentNotIn(t1, s1, C), AdjacentBetween(s2, t2, s1), {t2});
            isValid |= AnyValid(AdjacentNotIn(s1, t1, C), {t1}, AdjacentBetween(s2, t2, t1), {t2});

            isValid |= AnyValid(AdjacentBetween(s1, t1, t2), AdjacentBetween(t1, s1, t1), AdjacentBetween(s2, t2, s1), AdjacentBetween(t2, s2, s2));
            isValid |= AnyValid(AdjacentBetween(s1, t1, s2), AdjacentBetween(t1, s1, s1), AdjacentBetween(s2, t2, t1), AdjacentBetween(t2, s2, t2));
        }
        IsValid_[s1][t1][s2][t2] = isValid;
    }

    std::vector<int> AdjacentBetween(int s, int t) {
        std::vector<int> result;
        for (int x = 0; x < N_; x++) {
            if (Graph_[s][x] && IsBetween(s, t, x)) {
                result.push_back(x);
            }
        }
        return result;
    }

    std::vector<int> AdjacentBetween(int s, int t1, int t2) {
        std::vector<int> result;
        for (int x = 0; x < N_; x++) {
            if (Graph_[s][x] && IsBetween(s, t1, x) && IsBetween(s, t2, x)) {
                result.push_back(x);
            }
        }
        return result;
    }

    std::vector<int> AdjacentNotIn(int s, int t, const std::vector<bool>& vertexIsBlocked) {
        std::vector<int> result;
        for (int x = 0; x < N_; x++) {
            if (Graph_[s][x] && IsBetween(s, t, x) && !vertexIsBlocked[x]) {
                result.push_back(x);
            }
        }
        return result;
    }

    bool AnyValid(std::vector<int> possibleS1, std::vector<int> possibleT1, std::vector<int> possibleS2, std::vector<int> possibleT2)
    {
        for (int s1 : possibleS1) {
            for (int t1 : possibleT1) {
                for (int s2 : possibleS2) {
                    for (int t2 : possibleT2) {
                        if (TwoShortestPathsExist(s1, t1, s2, t2)) {
                            return true;
                        }
                    }
                }
            }
        }
        return false;
    }
};

std::unique_ptr<ISolution> CreateDynamicProgrammingN8Solution(TAdjacencyMatrix graph)
{
    return std::make_unique<TDynamicProgrammingN8Solution>(std::move(graph));
}
