// noavrd@gmail.com
#ifndef ALGORITHMS_HPP
#define ALGORITHMS_HPP

#include "Graph.hpp"
#include <vector>
#include <queue>
#include <string>
#include <limits>
#include <sstream>
#include <stack>
#include <unordered_set>

namespace ariel {

    class Algorithms {
    public:
        static bool isConnected(const Graph& g);

        static std::string shortestPath(const Graph& g, int start, int end);

        static bool isContainsCycle(const Graph& g);

        static std::string isBipartite(const Graph& g);

        static void negativeCycle(const Graph& g);

        static std::vector<std::vector<int>> adjMatrix;

    private:
        static bool bfs(const Graph& g, int start, std::vector<int>& distance, std::vector<int>& predecessor);
    };

}

#endif
