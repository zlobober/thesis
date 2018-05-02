#undef NDEBUG

#include <iostream>
#include <fstream>
#include <cassert>
#include <vector>
#include <cstring>

#include "generators.h"
#include "common.h"
#include "bruteforce.h"
#include "dp.h"

std::ostream* debug = new std::ofstream();
std::ostream* out = new std::ofstream();

void QueryAllSolutions(const TAdjacencyMatrix& graph, const std::vector<std::unique_ptr<ISolution>>& solutions, int s1, int t1, int s2, int t2) {
    *debug << "Query: (" << s1 << ", " << t1 << ", " << s2 << ", " << t2 << ")" << std::endl;
    std::vector<ISolution*> positive, negative;
    for (const auto& solution : solutions) {
        auto result = solution->TwoShortestPathsExist(s1, t1, s2, t2);
        (result ? positive : negative).push_back(solution.get());
    }
    if (!positive.empty() && !negative.empty()) {
        *debug << "Result: not OK" << std::endl;
        *debug << "Positive solutions:";
        for (const auto* solution : positive) {
            *debug << " " << solution->Description();
        }
        *debug << std::endl;
        *debug << "Negative solutions:";
        for (const auto* solution : negative) {
            *debug << " " << solution->Description();
        }
        *debug << std::endl;

        *out << "graph=";
        for (int i = 0; i < graph.size(); ++i) {
            for (int j = 0; j < graph.size(); ++j) {
                *out << graph[i][j];
            }
        }
        *out << " s1=" << s1 << " t1=" << t1 << " s2=" << s2 << " t2=" << t2 << std::endl;
    } else {
        *debug << "Result: OK, all solutions " << (negative.empty() ? "positive" : "negative") << std::endl;
    }
}

std::vector<std::unique_ptr<ISolution>> CreateSolutions()
{
    std::vector<std::unique_ptr<ISolution>> solutions;
    solutions.emplace_back(CreateBruteforceSolution());
    solutions.emplace_back(CreateDynamicProgrammingN8Solution());
    solutions.emplace_back(CreateDynamicProgrammingN7Solution());
    return solutions;
}

void MakeAllQueries(const TAdjacencyMatrix& graph)
{
    auto solutions = CreateSolutions();
    for (const auto& solution : solutions) {
        solution->Initialize(graph);
    }
    for (int s1 = 0; s1 < graph.size(); ++s1) {
        for (int t1 = 0; t1 < graph.size(); ++t1) {
            for (int s2 = 0; s2 < graph.size(); ++s2) {
                for (int t2 = 0; t2 < graph.size(); ++t2) {
                    QueryAllSolutions(graph, solutions, s1, t1, s2, t2);
                }
            }
        }
    }
}

void ReadFromStdin()
{
    TAdjacencyMatrix graph;
    while (ReadGraph(graph)) {
        *debug << "Processing graph: N = " << graph.size() << std::endl;
        for (int i = 0; i < graph.size(); ++i) {
            for (int j = 0; j < graph.size(); ++j) {
                *debug << graph[i][j];
            }
            *debug << std::endl;
        }
        int queryCount;
        std::cin >> queryCount;
        if (queryCount) {
            auto solutions = CreateSolutions();
            for (const auto& solution : solutions) {
                solution->Initialize(graph);
            }
            for (int i = 0; i < queryCount; ++i) {
                int s1, t1, s2, t2;
                std::cin >> s1 >> t1 >> s2 >> t2;
                QueryAllSolutions(graph, solutions, s1, t1, s2, t2);
            }
        } else {
            MakeAllQueries(graph);
        }
    }
}

void ShowHelp() {
    std::cerr << "Usage: ./main (--stdin|--all|--random) [-v] [-n N] [-t T] [--dump-failed] [-h]" << std::endl;
    std::cerr << "Compiled solutions:";
    auto solutions = CreateSolutions();
    for (const auto& solution : solutions) {
        std::cerr << " " << solution->Description();
    }
    std::cerr << std::endl;
}

int main(int argc, char* argv[])
{
    bool readFromStdin = false;
    bool generateAll = false;
    bool generateRandom = false;
    bool dumpFailed = false;
    int n = -1;
    int t = -1;
    int seed = -1;
    bool help = false;
    for (int i = 1; i < argc; ++i) {
        if (strcmp(argv[i], "-v") == 0) {
            debug = &std::cerr;
        }
        if (strcmp(argv[i], "--stdin") == 0) {
            readFromStdin = true;
        }
        if (strcmp(argv[i], "--all") == 0) {
            generateAll = true;
        }
        if (strcmp(argv[i], "--random") == 0) {
            generateRandom = true;
        }
        if (strcmp(argv[i], "-n") == 0) {
            assert(i + 1 != argc);
            n = atoi(argv[i + 1]);
            ++i;
        }
        if (strcmp(argv[i], "-t") == 0) {
            assert(i + 1 != argc);
            t = atoi(argv[i + 1]);
            ++i;
        }
        if (strcmp(argv[i], "--dump-failed") == 0) {
            out = &std::cout;
        }
        if (strcmp(argv[i], "--seed") == 0) {
            assert(i + 1 != argc);
            seed = atoi(argv[i + 1]);
            ++i;
        }
        if (strcmp(argv[i], "-h") == 0) {
            help = true;
        }
    }
    if (help) {
        ShowHelp();
        return 0;
    }
    srand(seed);
    assert(readFromStdin + generateAll + generateRandom == 1);

    if (readFromStdin) {
        ReadFromStdin();
    } else if (generateAll) {
        assert(n != -1);
        GenerateAll(n, MakeAllQueries);
    } else {
        assert(n != -1);
        assert(t != -1);
        for (int i = 0; i < t; ++i) {
            GenerateRandom(n, MakeAllQueries);
        }
    }
}
