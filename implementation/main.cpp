#include <iostream>
#include <cassert>
#include <vector>

#include "common.h"
#include "bruteforce.h"
#include "dp_n8.h"

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

void QueryAllSolutions(const std::vector<ISolution*>& solutions, int s1, int t1, int s2, int t2) {
    std::cout << "Query: (" << s1 << ", " << t1 << ", " << s2 << ", " << t2 << ")" << std::endl;
    std::vector<ISolution*> positive, negative;
    for (auto* solution : solutions) {
        auto result = solution->TwoShortestPathsExist(s1, t1, s2, t2);
        (result ? positive : negative).push_back(solution);
    }
    if (!positive.empty() && !negative.empty()) {
        std::cout << "Result: not OK" << std::endl;
        std::cout << "Positive solutions:";
        for (const auto* solution : positive) {
            std::cout << " " << solution->Description();
        }
        std::cout << std::endl;
        std::cout << "Negative solutions:";
        for (const auto* solution : negative) {
            std::cout << " " << solution->Description();
        }
        std::cout << std::endl;
    } else {
        std::cout << "Result: OK, all solutions " << (negative.empty() ? "positive" : "negative") << std::endl;
    }
}

int main()
{
    TAdjacencyMatrix graph;
    while (ReadGraph(graph)) {
        std::cout << "Processing graph: N = " << graph.size() << std::endl;
        for (int i = 0; i < graph.size(); ++i) {
            for (int j = 0; j < graph.size(); ++j) {
                std::cout << graph[i][j];
            }
            std::cout << std::endl;
        }
        auto bruteforceSolution = CreateBruteforceSolution(graph);
        auto dpN8Solution = CreateDynamicProgrammingN8Solution(graph);

        std::vector<ISolution*> solutions = {bruteforceSolution.get(), dpN8Solution.get()};
        std::cout << "Solutions:";
        for (const auto* solution : solutions) {
            std::cout << " " << solution->Description();
        }
        std::cout << std::endl;

        int queryCount;
        std::cin >> queryCount;
        if (queryCount) {
            for (int i = 0; i < queryCount; ++i) {
                int s1, t1, s2, t2;
                std::cin >> s1 >> t1 >> s2 >> t2;
                QueryAllSolutions(solutions, s1, t1, s2, t2);
            }
        } else {
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
}
