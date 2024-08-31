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

/*
 *  Return a copy of the current graph. 
 */
Graph Graph::operator+() const {
    return *this;
}

/*
 *  Addition for two graphs.
 *
 *  This operator adds one graph element to the matching second graph element.
 *  It returns a new graph where each element is the sum of the corresponding elements from the two graphs.
 *
 */
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

/*
 *  Increment each element of the graph by 1.
 *
 *  This operator increments each element in the graph by 1.
 *  It modifies the current graph in place and returns a reference to it.
 *
 */
Graph &Graph::operator++() {
    for (size_t i = 0; i < this->graphSize(); ++i) {
        for (size_t j = 0; j < this->graphSize(); ++j) {
            (*this).matrix[i][j]++;
        }
    }

    return *this;
}

/*
 *  This operator creates a copy of the current graph, increments the current graph by 1, and then returns the copy.
 */
Graph Graph::operator++(int) {
    Graph temp = *this;
    ++(*this);
    return temp;
}

/*
 *  Addition for two graphs.
 *
 *  This operator adds one graph element to the matching second graph element.
 *  It creates a new matrix with the sum of the elements, loads this matrix into the current graph,
 *  and returns a copy of the updated graph. 
 * 
 */
Graph Graph::operator+=(const Graph &secGraph) {
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

/*
 *  Add a scalar to each element of the graph.
 *
 *  This operator adds a given scalar value to each element in the matrix of the current graph.
 *  It modifies the current graph in place and returns a reference to it.
 *
 */
Graph &Graph::operator+=(int scalar) {
    for (size_t i = 0; i < this->graphSize(); ++i) {
        for (size_t j = 0; j < this->graphSize(); ++j) {
            (*this).matrix[i][j] += scalar;
        }
    }

    return *this;
}

/*
 *  Return a copy of the current graph.
 *
 *  This operator simply returns a new graph that is a copy of the current one.
 *
 */
Graph Graph::operator-() const {
    return *this;
}

/*
 *  Subtract two graphs for each other.
 *
 *  This operator performs for each matching element subtraction.
 *  It returns a new graph where each element is the difference between the corresponding elements from the two graphs.
 *
 */
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

/*
 *  Decrement each element of the graph by 1.
 *
 *  This operator decrements each element in the matrix of the current graph by 1.
 *  It modifies the current graph in place and returns a reference to it.
 *
 */
Graph &Graph::operator--() {
    for (size_t i = 0; i < this->graphSize(); ++i) {
        for (size_t j = 0; j < this->graphSize(); ++j) {
            (*this).matrix[i][j]--;
        }
    }
    return *this;
}

/*
 *  This operator creates a copy of the current graph, decrements the current graph by 1, and then returns the copy.
 */
Graph Graph::operator--(int) {
    Graph temp = *this;
    --(*this);
    return temp;
}

/*
 *  Subtract another graph from the current graph.
 *
 *  This operator operates for each elment subtraction of the matrix of another graph from the matrix of the current graph.
 *  It creates a new matrix with the new elements, loads this matrix into the current graph,
 *  and returns a copy of the updated graph. 
 *
 */
Graph Graph::operator-=(const Graph &secGraph) {
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

/*
 *  Subtract another graph from the current graph.
 *
 *  This operator operates for each elment subtraction of the matrix of another graph from the matrix of the current graph.
 *  It modifies the current graph in place and returns a reference to it.
 *
 */
Graph &Graph::operator-=(int scalar) {
    for (size_t i = 0; i < this->graphSize(); ++i) {
        for (size_t j = 0; j < this->graphSize(); ++j) {
            (*this).matrix[i][j] -= scalar;
        }
    }

    return *this;
}

/*
 *  Multiply two graphs element-wise.
 *
 *  This operator performs element-wise multiplication of the matrices of two graphs.
 *  It returns a new graph where each element is the product of the corresponding elements from the two graphs.
 *
 */
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

/*
 *  Multiply the current graph by a scalar.
 *
 *  This operator multiplies each element in the matrix of the current graph by a given scalar value.
 *  It returns a new graph with the scaled elements.
 *
 */
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

/*
 *  Multiply each element of the current graph by a scalar.
 *
 *  This operator multiplies each element in the matrix of the current graph by a given scalar value.
 *  It modifies the current graph in place and returns a reference to it.
 *
 */
Graph &Graph::operator*=(int scalar) {
    for (size_t i = 0; i < this->graphSize(); ++i) {
        for (size_t j = 0; j < this->graphSize(); ++j) {
           (*this).matrix[i][j] *= scalar;
        }
    }

    return *this;
}

/*
 *  Divide each element of the current graph by a scalar.
 *
 *  This operator divides each element in the matrix of the current graph by a given scalar value.
 *  It changes the current graph in place and returns a reference to it.
 *  Throws an exception if the scalar is zero.
 *
 */
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

/*
 *  Compare if two graphs are equal.
 *
 *  This operator checks if the matrices of two graphs are equal.
 *  It returns true if they are equal, if not it will return false.
 * 
 */
bool Graph::operator==(const Graph &secGraph) const {
    return this->matrix == secGraph.matrix;
}

/*
 *  Compare if two graphs are not equal.
 *
 *  This operator checks if the matrices of two graphs are not equal.
 *  It returns true if they are not equal, if not it will return false.
 *
 */
bool Graph::operator!=(const Graph &secGraph) const {
    return !(*this == secGraph);
}

/*
 *  Compare if the current graph is less than another graph.
 *
 *  This operator first compares the sizes of the graphs, then compares the number of edges,
 *  and finally compares the matrices element-wise if necessary.
 *
 */
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

/*
 *  Compare if the current graph is greater than another graph.
 */
bool Graph::operator>(const Graph &secGraph) const {
    return secGraph < *this;
}

/*
 *  Compare if the current graph is less or equal to another graph.
 */
bool Graph::operator<=(const Graph &secGraph) const {
    return *this < secGraph || *this == secGraph;
}

/*
 *  Compare if the current graph is bigger or equal to another graph.
 */
bool Graph::operator>=(const Graph &secGraph) const {
    return secGraph <= *this;
}

/* 
 *  An operator that prints the graph to the given output stream.
 */
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
