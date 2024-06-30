// noavrd@gmail.com

#include "Algorithms.hpp"
#include <queue>
#include <stack>
#include <unordered_set>
#include <unordered_map>
#include <limits>
#include <iostream>
#include <algorithm>

namespace ariel {
    vector<vector<int>> Algorithms::adjMatrix;
    // vector <int> Algorithms::dist;

    bool Algorithms::isConnected(const Graph& graph) {
        adjMatrix = graph.getAdjMatrix();
        // num of Vertices(kodkod)
        int numVertices = adjMatrix.size();
        // check if the graph is empty - if so then it's connected
        if (numVertices == 0) return true;

        // check how much vertices I checked
        std::vector<bool> visited(numVertices, false);
        std::queue<int> queue;
        // add the first vertex to the queue
        queue.push(0);
        visited[0] = true;
        int count = 1;

        // use BFS algorithm
        while (!queue.empty()) {
            int vertex = queue.front();
            queue.pop();
            for (int secVertex = 0; secVertex < numVertices; ++secVertex) {
                // check if there is an edge between vertex and secVertex and secVertex has not been visited
                if (adjMatrix[vertex][secVertex] != 0 && !visited[secVertex]) {
                    // mark secVertex as visited
                    visited[secVertex] = true;
                    queue.push(secVertex);
                    count++;
                }
            }
        }
        // check if the graph is connected by checking if all vertices are visited
        return count == numVertices;
    }
}
