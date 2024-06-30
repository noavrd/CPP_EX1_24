// noavrd@gmail.com
#ifndef ALGORITHMS_HPP
#define ALGORITHMS_HPP

#include "Graph.hpp"
#include <vector>
#include <queue>
#include <string>
#include <limits>

namespace ariel {

    class Algorithms {
    public:
        static bool isConnected(const Graph& g);

        static std::string shortestPath(const Graph& g, int start, int end);

        static bool isContainsCycle(const Graph& g);

        static std::string isBipartite(const Graph& g);

        static bool negativeCycle(const Graph& g);
    };

}

#endif