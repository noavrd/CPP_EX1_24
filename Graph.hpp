// noavrd@gmail.com
#ifndef GRAPH_HPP
#define GRAPH_HPP

#include <ostream>
#include <iostream>
#include <vector>
#include <string>

using namespace std;

namespace ariel {

    class Graph {
        private:
            vector<vector<int>> matrix;
            bool checkValid(const Graph &secGraph) const;
            vector<vector<int>> result;

        public:
            Graph();  // Default constructor
            Graph(const vector<vector<int>> &matrix); 
            ~Graph() = default;
            void loadGraph(const vector<vector<int>> &matrix);
            void printGraph() const;

            const vector<vector<int>>& getMatrix() const;

            size_t graphSize() const;
            size_t countEdges() const;
            
            // + operators
            Graph operator+() const;
            Graph operator+(const Graph &secGraph) const;

            Graph &operator++();
            Graph operator++(int);

            Graph operator+=(const Graph &secGraph);
            Graph &operator+=(int scalar);

            // - operators
            Graph operator-() const;
            Graph operator-(const Graph &secGraph) const;

            Graph &operator--();
            Graph operator--(int);

            Graph operator-=(const Graph &secGraph);
            Graph &operator-=(int scalar);


            // * operators
            Graph operator*(const Graph &secGraph) const;
            Graph operator*(int scalar) const;

            Graph &operator*=(int scalar); 

            // divide operator
            Graph &operator/=(int scalar);   
        
            // conditions operators
            bool operator==(const Graph &secGraph) const;
            bool operator!=(const Graph &secGraph) const;

            bool operator<(const Graph &secGraph) const;
            bool operator>(const Graph &secGraph) const;
            
            bool operator<=(const Graph &secGraph) const;
            bool operator>=(const Graph &secGraph) const;

            // print operators
            friend ostream& operator<<(ostream &out, const Graph &g);

    };
}

#endif // GRAPH_HPP