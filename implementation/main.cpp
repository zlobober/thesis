#include <iostream>
#include <cassert>
#include <vector>

#include "common.h"
#include "bruteforce.h"

TAdjacencyMatrix ReadGraph()
{
    int n;
    std::cin >> n;
    TAdjacencyMatrix graph(n, std::vector<bool>(n, false));
    for (int i = 0; i < n; i++) {
        std::string row;

        std::cin >> row;
        for (int j = 0; j < n; j++) {
            if (row[j] == '1') {
                graph[i][j] = true;
            }
        }
    }
    return graph;
}

void QueryAllSolutions(const std::vector<ISolution*>& solutions, int s1, int t1, int s2, int t2) {
    std::cerr << "Query: (" << s1 << ", " << t1 << ", " << s2 << ", " << t2 << ")" << std::endl;
    std::vector<ISolution*> positive, negative;
    for (auto* solution : solutions) {
        auto result = solution->TwoShortestPathsExist(s1, t1, s2, t2);
        (result ? positive : negative).push_back(solution);
    }
    if (!positive.empty() && !negative.empty()) {
        std::cerr << "Result: not OK" << std::endl;
        std::cerr << "Positive solutions:";
        for (const auto* solution : positive) {
            std::cerr << " " << solution->Description();
        }
        std::cerr << std::endl;
        std::cerr << "Negative solutions:";
        for (const auto* solution : negative) {
            std::cerr << " " << solution->Description();
        }
        std::cerr << std::endl;
    } else {
        std::cerr << "Result: OK, all solutions " << (negative.empty() ? "positive" : "negative") << std::endl;
    }
}

int main()
{
    auto graph = ReadGraph();
    auto bruteforceSolution = CreateBruteforceSolution(graph);
    std::vector<ISolution*> solutions = {bruteforceSolution.get()};
    bool checkAllPairs = true;
    {
        int s1, t1, s2, t2;
        while (std::cin >> s1 >> t1 >> s2 >> t2) {
            checkAllPairs = false;
            QueryAllSolutions(solutions, s1, t1, s2, t2);
        }
    }
    if (checkAllPairs) {
        for (int s1 = 0; s1 < graph.size(); ++s1) {
            for (int t1 = 0; t1 < graph.size(); ++t1) {
                for (int s2 = 0; s2 < graph.size(); ++s2) {
                    for (int t2 = 0; t2 < graph.size(); ++t2) {
                        QueryAllSolutions(solutions, s1, t1, s2, t2);
                    }
                }
            }
        }
    }
}
