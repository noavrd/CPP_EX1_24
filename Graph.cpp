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

void Graph::loadGraph(const vector<vector<int>> &adjMatrix) {
    size_t size = adjMatrix.size();
    for (const vector<int> &row : adjMatrix) {
        if (row.size() != size) {
             throw std::invalid_argument("Invalid graph: The graph is not a square matrix.");
        }
    }
    this->matrix = adjMatrix;
}

// fix this!!!!
std::string Graph::printGraph() const {
    size_t size = graphSize();
    std::string matrixprint;  
    for (size_t i = 0; i < size; ++i) {
        matrixprint += "[";  
        for (size_t j = 0; j < size; ++j) {
            matrixprint += std::to_string(matrix[i][j]);  
            if (j < size - 1) {
                matrixprint += ", ";
            }
        }
        matrixprint += "]";
        if (i < size - 1) {
            matrixprint += "\n";  
        }
    }
    return matrixprint;
}

const vector<vector<int>> &Graph::getMatrix() const {
    return this->matrix;
}

size_t Graph::graphSize() const {
    return this->matrix.size();
}

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

Graph Graph::operator+() const {
    return *this;
}

Graph Graph::operator+(const Graph &secGraph) const {
    if (this->graphSize() != secGraph.graphSize()) {
        throw invalid_argument("Graphs must be the same size.");
    }

    vector<vector<int>> result(this->matrix.size(), vector<int>(this->matrix.size()));

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
    if (this->graphSize() != secGraph.graphSize()) {
        throw invalid_argument("Graphs must be the same size.");
    }

    vector<vector<int>> result(this->matrix.size(), vector<int>(this->matrix.size()));

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
    if (this->graphSize() != secGraph.graphSize()) {
        throw invalid_argument("Graphs must be the same size.");
    }

    vector<vector<int>> result(this->matrix.size(), vector<int>(this->matrix.size()));

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
    if (this->graphSize() != secGraph.graphSize()) {
        throw invalid_argument("Graphs must be the same size.");
    }

    vector<vector<int>> result(this->matrix.size(), vector<int>(this->matrix.size()));
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
    vector<vector<int>> result(this->matrix.size(), vector<int>(this->matrix.size()));

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
        throw invalid_argument("YOu can't divide by 0.");
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

    size_t thisEdges = countEdges();
    size_t secGraphEdges = secGraph.countEdges();

    if (thisEdges < secGraphEdges) {
        return true;
    }

    if (thisEdges > secGraphEdges) {
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