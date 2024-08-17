// noavrd@gmail.com

#include "Graph.hpp"

namespace ariel {

    void Graph::loadGraph(const std::vector<std::vector<int>>& matrix) {
        size_t rows = matrix.size();
        size_t cols = matrix[0].size();
        if (rows != cols)
            throw std::invalid_argument("Invalid graph: The graph is not a square matrix.");

        adjMatrix = matrix;
    }

    void Graph::printGraph() const {
        size_t numVertices = adjMatrix.size();
        size_t numEdges = 0;

        // Count edges, considering undirected graph (count each edge once)
        for (size_t i = 0; i < numVertices; ++i) {
            for (size_t j = i + 1; j < numVertices; ++j) {
                if (adjMatrix[i][j] != 0) {
                    ++numEdges;
                }
            }
        }

        // Print the adjacency matrix
        for (size_t i = 0; i < numVertices; ++i) {
            for (size_t j = 0; j < numVertices; ++j) {
                std::cout << adjMatrix[i][j] << " ";
            }
            std::cout << "\n";
        }

        // Print the summary
        std::cout << "Graph with " << numVertices << " vertices and " << numEdges << " edges." << std::endl;
    }

}
