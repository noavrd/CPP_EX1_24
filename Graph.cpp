// noavrd@gmail.com

#include "Graph.hpp"

namespace ariel {

    void Graph::loadGraph(const std::vector<std::vector<int>>& matrix) {
        size_t rows = matrix.size();
        size_t cols = matrix[0].size();
        if (rows != cols)
            throw std::invalid_argument("Can't load to the graph, matrix is not squared");

        adjMatrix = matrix;
    }

    void Graph::printGraph() const {
        for (size_t i = 0; i < adjMatrix.size(); i++) {
            for (size_t j = 0; j < adjMatrix[0].size(); j++) {
                cout << adjMatrix[i][j] << " ";
            }
            cout << "\n";
        }
    }

}
