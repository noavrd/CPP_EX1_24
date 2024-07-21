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

    bool Algorithms::bfs(const Graph& g, int start, std::vector<int>& distance,  std::vector<int>& prev) {
        // get adjacency matrix and its size
        const std::vector<std::vector<int>>& adjMatrix = g.getAdjMatrix();
        int numVertices = adjMatrix.size();  
        
        // create a queue to use in the algorithm and add the starting vertex to the queue
        std::queue<int> queue; 
        queue.push(start);  

        // the distance from the start vertex to itself is 0
        distance[start] = 0; 

        // infinite distance (not reachable)
        int infiniteDistance = std::numeric_limits<int>::max();

        // while the queue isn't empty
        while (!queue.empty()) {  
            // get the first vertex in the queue and remove it
            int vertex = queue.front();  
            queue.pop();  

            // iterate over all nodes in the graph
            for (int secVertex = 0; secVertex < numVertices; ++secVertex) {  
                // check if there is an edge and the second vertex has not been visited
                if (adjMatrix[vertex][secVertex] != 0 && distance[secVertex] == infiniteDistance) {  
                    // update the distance to the next vertex
                    distance[secVertex] = distance[vertex] + 1;
                    // save the prev vertex
                    prev[secVertex] = vertex;  
 
                    // add the second vertex to the queue
                    queue.push(secVertex); 
                }
            }
        }

        // return true, BFS completed
        return true;  
    }

    bool Algorithms::isConnected(const Graph& graph) {
        // get the adjacency matrix
        const std::vector<std::vector<int>>& adjMatrix = graph.getAdjMatrix();
        // number of vertices
        int numVertices = adjMatrix.size();

        // check if the graph is empty - if so then it's connected
        if (numVertices == 0) return true;

        int inf  = std::numeric_limits<int>::max();
        // initialize distance var vector with numVertices will be the num of the elements distance will have and each of them will be initalized to inf
        std::vector<int> distance(numVertices, inf);

        // perform bfs starting from the first vertex
        bfs(graph, 0, distance);

        // check if all vertices are reachable
        for (int i = 0; i < numVertices; ++i) {
            if (distance[i] == inf) {
                return false;
            }
        }

        // if all vertices are reachable, the graph is connected
        return true;
    }
    
   std::string Algorithms::shortestPath(const Graph& g, int start, int end) {
     const std::vector<std::vector<int>>& adjMatrix = g.getAdjMatrix();  
    // get the number of vertices in the graph
    int n = adjMatrix.size();  

    // check if the start and end vertices are valid
    if (start < 0 || start >= n || end < 0 || end >= n) {
        // return "-1" if the vertices are not valid
        return "-1";  
    }

    // define the infinite distance
    int inf = std::numeric_limits<int>::max();  
    // initialize distance vector with infinite distances
    std::vector<int> distance(n, inf);  
    // initialize predecessor vector with -1 (no predecessor)
    std::vector<int> predecessor(n, -1);  

    // perform bfs to find the shortest paths from the start vertex
    bfs(g, start, distance, predecessor);  

    // check if there is no path to the end vertex
    if (distance[end] == inf) {
        // return "-1" if there is no path to the end vertex
        return "-1";  
    }

    // create a stringstream to build the path string
    std::stringstream path;  
    // start from the end vertex
    int crawl = end;  
    // traverse the path from end to start
    while (crawl != -1) {  
        // add the current vertex to the path
        path << crawl << " ";  
        // move to the predecessor of the current vertex
        crawl = predecessor[crawl];  
    }

    // convert the stringstream to a string
    std::string result = path.str();  
    // reverse the string to get the correct path order
    std::reverse(result.begin(), result.end());  
    // return the path string
    return result;  
    }
}
