// noavrd@gmail.com
#include "Graph.hpp"
#include <iostream>
#include <vector>
#include <stdexcept>
#include <sstream>
#include <ostream>
#include <string>

using namespace std;
using namespace ariel;

Graph::Graph() {}

/*
*  A function that loads the graph.
*/
void Graph::loadGraph(const vector<vector<int>> &adjMatrix) {
    size_t size = adjMatrix.size();
    for (const vector<int> &row : adjMatrix) {
        if (row.size() != size) {
             throw std::invalid_argument("Invalid graph: The graph is not a square matrix.");
        }
    }
    this->matrix = adjMatrix;
}

/*
*   Print graph function.
*
*   It uses graphSize and countEdges helper function to print the grapg vertics and edges.
*/
void Graph::printGraph() const {
    size_t size = graphSize();
    size_t edges = countEdges();

    std::cout << "Graph with " << size << " vertices and " << edges << " edges." << std::endl;
}


const vector<vector<int>> &Graph::getMatrix() const {
    return this->matrix;
}

/*
*   Helper function to get the size of the current graph.
*/
size_t Graph::graphSize() const {
    return this->matrix.size();
}

/*
*   Helper function to count the edges of the current graph.
*/
size_t Graph::countEdges() const {
    size_t count = 0;

    for (size_t i = 0; i < this->graphSize(); ++i) {
        for (size_t j = 0; j < this->graphSize(); ++j) {
            if ((*this).matrix[i][j] != 0) {
                count++;
            }
        }
    }

    return count;
}

/*
*   Helper function to check if 2 graphs are in the same size to make calculations.
*/
bool Graph::checkValid(const Graph &secGraph) const {
    if (this->matrix.size() != secGraph.getMatrix().size()) {
       throw invalid_argument("Graphs must be the same size.");
    }
    return true;
}

/*
*   Helper function to intiazlize result matrix
*/
vector<vector<int>> initializeResultMatrix(size_t size) {
    return vector<vector<int>>(size, vector<int>(size));
}


Graph Graph::operator+() const {
    return *this;
}

Graph Graph::operator+(const Graph &secGraph) const {
    checkValid(secGraph);

        vector<vector<int>> result = initializeResultMatrix(this->matrix.size());

    for (size_t i = 0; i < this->matrix.size(); ++i) {
        for (size_t j = 0; j < this->matrix.size(); ++j) {
            result[i][j] = this->matrix[i][j] + secGraph.matrix[i][j];
        }
    }

    Graph newGraph;
    newGraph.loadGraph(result);
    return newGraph;
}

Graph &Graph::operator++() {
    for (size_t i = 0; i < this->graphSize(); ++i) {
        for (size_t j = 0; j < this->graphSize(); ++j) {
            (*this).matrix[i][j] ++;
        }
    }

    return *this;
}

Graph Graph::operator++(int) {
    Graph temp = *this;
    ++(*this);
    return temp;
}

Graph Graph::operator+=(const Graph &secGraph)  {
    checkValid(secGraph);

        vector<vector<int>> result = initializeResultMatrix(this->matrix.size());

    for (size_t i = 0; i < this->matrix.size(); ++i) {
        for (size_t j = 0; j < this->matrix.size(); ++j) {
            result[i][j] = this->matrix[i][j] + secGraph.matrix[i][j];
        }
    }

    this->loadGraph(result);
    return *this;
}

Graph Graph::operator-() const {
    return *this;
}


Graph Graph::operator-(const Graph &secGraph) const {
    checkValid(secGraph);

        vector<vector<int>> result = initializeResultMatrix(this->matrix.size());

    for (size_t i = 0; i < this->matrix.size(); ++i) {
        for (size_t j = 0; j < this->matrix.size(); ++j) {
            result[i][j] = this->matrix[i][j] - secGraph.matrix[i][j];
        }
    }
    
    Graph newGraph;
    newGraph.loadGraph(result);
    return newGraph;
}

Graph &Graph::operator--() {
    for (size_t i = 0; i < this->graphSize(); ++i) {
        for (size_t j = 0; j < this->graphSize(); ++j) {
            (*this).matrix[i][j] --;
        }
    }
    return *this;
}

Graph Graph::operator--(int) {
    Graph temp = *this;
    --(*this);
    return temp;
}

Graph Graph::operator-=(const Graph &secGraph)  {
    checkValid(secGraph);

        vector<vector<int>> result = initializeResultMatrix(this->matrix.size());
    for (size_t i = 0; i < this->matrix.size(); ++i) {
        for (size_t j = 0; j < this->matrix.size(); ++j) {
            result[i][j] = this->matrix[i][j] - secGraph.matrix[i][j];
        }
    }

    this->loadGraph(result);
    return *this;
}

Graph Graph::operator*(const Graph &secGraph) const {
    if (this->graphSize() != secGraph.graphSize()) {
        throw std::invalid_argument("The number of columns in the first matrix must be equal to the number of rows in the second matrix.");
    }

    size_t size = this->graphSize();
    std::vector<std::vector<int>> result(size, std::vector<int>(size, 0));

    for (size_t i = 0; i < size; ++i) {
        for (size_t j = 0; j < size; ++j) {
            for (size_t k = 0; k < size; ++k) {
                result[i][j] += this->matrix[i][k] * secGraph.matrix[k][j];
            }
        }
    }

    Graph newGraph;
    newGraph.loadGraph(result);  
    return newGraph;
}

Graph Graph::operator*(int scalar) const {
    vector<vector<int>> result = initializeResultMatrix(this->matrix.size());

    for (size_t i = 0; i < this->graphSize(); ++i) {
        for (size_t j = 0; j < this->graphSize(); ++j) {
           result[i][j] = this->matrix[i][j] * scalar;
        }
    }
    
    Graph newGraph;
    newGraph.loadGraph(result);
    return newGraph;
}

Graph &Graph::operator*=(int scalar) {
    for (size_t i = 0; i < this->graphSize(); ++i) {
        for (size_t j = 0; j < this->graphSize(); ++j) {
           (*this).matrix[i][j] *= scalar;
        }
    }

    return *this;
}

Graph &Graph::operator/=(int scalar) {
    if (scalar == 0) {
        throw invalid_argument("You can't divide by 0.");
    }
    for (size_t i = 0; i < this->graphSize(); ++i) {
        for (size_t j = 0; j < this->graphSize(); ++j) {
           (*this).matrix[i][j] /= scalar;
        }
    }

    return *this;
}


bool Graph::operator==(const Graph &secGraph) const {
    return this->matrix == secGraph.matrix;
}

bool Graph::operator!=(const Graph &secGraph) const {
    return !(*this == secGraph);
}

bool Graph::operator<(const Graph &secGraph) const {
    if (this->graphSize() < secGraph.graphSize()) {
        return true;
    }

    if (this->graphSize() > secGraph.graphSize()) {
        return false;
    }

    size_t edges = countEdges();
    size_t secGraphEdges = secGraph.countEdges();

    if (edges < secGraphEdges) {
        return true;
    }

    if (edges > secGraphEdges) {
        return false;
    }

    return this->matrix < secGraph.matrix;
}

bool Graph::operator>(const Graph &secGraph) const {
    return secGraph < *this;
}

bool Graph::operator<=(const Graph &secGraph) const {
    return *this < secGraph || *this == secGraph;
}


bool Graph::operator>=(const Graph &secGraph) const {
    return secGraph <= *this;
}

std::ostream &ariel::operator<<(std::ostream &out, const Graph &g) {
    const auto &matrix = g.getMatrix();

    for (size_t i = 0; i < matrix.size(); ++i) {
        out << "[";

        for (size_t j = 0; j < matrix.size(); ++j) {
            if (j == matrix.size() - 1 ) {
                out << matrix[i][j];
            } else {
                out << matrix[i][j] << ", ";
            }
        }

        out << "]";

        if (i == matrix.size() - 1 ) {
                out << std::endl;
            } else {
                out << ", ";
            }
        
    }

    return out;
}