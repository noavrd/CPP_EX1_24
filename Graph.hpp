// noavrd@gmail.com
#ifndef GRAPH_HPP
#define GRAPH_HPP

#include <vector>
#include <iostream>
#include <stdexcept>

namespace ariel {

    class Graph {
    private:
        std::vector<std::vector<int>> adjMatrix;
      
    public:
        void loadGraph(const std::vector<std::vector<int>>& matrix);
        void printGraph() const;
    
        const std::vector<std::vector<int>>& getAdjMatrix() const { return adjMatrix; }
    };

}

#endif 
