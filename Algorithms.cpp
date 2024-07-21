// noavrd@gmail.com

#include "Algorithms.hpp"
#include <queue>
#include <stack>
#include <unordered_set>
#include <limits>
#include <iostream>
#include <algorithm>

namespace ariel {
    vector<vector<int>> Algorithms::adjMatrix;
    // vector <int> Algorithms::dist;

    bool Algorithms::bfs(const Graph& g, int start, std::vector<int>& distance,  std::vector<int>& prev) {
        // get adjacency matrix
        const std::vector<std::vector<int>>& adjMatrix = g.getAdjMatrix();
        // size of the graph (number of vertices)
        int adjSize = adjMatrix.size();  
        
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
            for (int secVertex = 0; secVertex < adjSize; ++secVertex) {  
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
        const std::vector<std::vector<int>>& adjMatrix = graph.getAdjMatrix();
        // number of vertices
        int adjSize = adjMatrix.size();

        // check if the graph is empty - if so then it's connected
        if (adjSize == 0) return true;

        int inf  = std::numeric_limits<int>::max();
        // initialize distance var vector with adjSize will be the num of the elements distance will have and each of them will be initalized to inf
        std::vector<int> distance(adjSize, inf);

        // perform bfs starting from the first vertex
        bfs(graph, 0, distance);

        // check if all vertices are reachable
        for (int i = 0; i < adjSize; ++i) {
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
    int adjSize = adjMatrix.size();  

    // check if the start and end vertices are valid
    if (start < 0 || start >= adjSize || end < 0 || end >= adjSize) {
        // return "-1" if the vertices are not valid
        return "-1";  
    }

    // define the infinite distance
    int inf = std::numeric_limits<int>::max();  
    // initialize distance vector with infinite distances
    std::vector<int> distance(adjSize, inf);  
    // initialize prev vector with -1 (no prev)
    std::vector<int> prev(adjSize, -1);  

    // perform bfs to find the shortest paths from the start vertex
    bfs(g, start, distance, prev);  

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
        // move to the prev of the current vertex
        crawl = prev[crawl];  
    }

    // convert the stringstream to a string
    std::string result = path.str();  
    // reverse the string to get the correct path order
    std::reverse(result.begin(), result.end());  
    // return the path string
    return result;  
    }

    bool Algorithms::isContainsCycle(const Graph& g) {
    const std::vector<std::vector<int>>& adjMatrix = g.getAdjMatrix();
    int adjSize = adjMatrix.size();  

    // vector to track visited vertices, initialized with false
    std::vector<bool> visited(adjSize, false);  
    // vector to track the parent of each vertex, initialized with -1
    std::vector<int> parent(adjSize, -1);  

    // iterate over all vertices in the graph
    for (int u = 0; u < adjSize; ++u) {  
        // if the vertex has not been visited
        if (!visited[u]) {  
            // queue for bfs algorithm
            std::queue<int> queue;  
            // mark the vertex as visited
            visited[u] = true;  
            // add the vertex to the queue
            queue.push(u);  

            // while the queue is not empty
            while (!queue.empty()) {  
                // get the first vertex in the queue
                int v = queue.front();  
                // remove the vertex from the queue
                queue.pop();  

                // iterate over all vertices in the graph
                for (int w = 0; w < adjSize; ++w) {  
                    // if there is an edge from v to w
                    if (adjMatrix[v][w] != 0) {  
                        // if w has not been visited
                        if (!visited[w]) {  
                            // mark w as visited
                            visited[w] = true;  
                            // set v as the parent of w
                            parent[w] = v;  
                            // add w to the queue
                            queue.push(w);  
                        } 
                        // if w has been visited and w is not the parent of v
                        else if (w != parent[v]) {  
                            // print message about cycle detection
                            std::cout << "cycle found: ";  
                            // save the starting vertex of the cycle
                            int cycle_vertex = v;  
                            // vector to store the vertices in the cycle
                            std::vector<int> cycle;  
                            // build the cycle path
                            while (cycle_vertex != w) {  
                                // add the current vertex to the cycle
                                cycle.push_back(cycle_vertex);  
                                // move to the parent vertex
                                cycle_vertex = parent[cycle_vertex];  
                            }
                            // add the end vertex to the cycle
                            cycle.push_back(w);  
                            // add the starting vertex to the cycle
                            cycle.push_back(v);  
                            // iterate over all vertices in the cycle
                            for (size_t i = 0; i < cycle.size(); ++i) {  
                                // print the current vertex
                                std::cout << cycle[i];  
                                // if this is not the last vertex in the cycle
                                if (i < cycle.size() - 1) {  
                                    // print the arrow to the next vertex
                                    std::cout << "->";  
                                }
                            }
                            // end the line after the cycle
                            std::cout << std::endl;  
                            // return true when a cycle is found
                            return true;  
                        }
                    }
                }
            }
        }
    }
    // return false if no cycle is found
    return false;  
    }

    std::string Algorithms::isBipartite(const Graph& g) {
    const std::vector<std::vector<int>>& adjMatrix = g.getAdjMatrix();  
    int adjSize = adjMatrix.size();  

    // color vector, initialized with -1 to indicate no color
    std::vector<int> color(adjSize, -1);  
    // queue for bfs algorithm
    std::queue<int> queue;  

    // iterate over all vertices in the graph
    for (int u = 0; u < adjSize; ++u) {  
        // if the vertex is not colored
        if (color[u] == -1) {  
            // color the vertex with color 0
            color[u] = 0;  
            // add the vertex to the queue
            queue.push(u);  

            // while the queue is not empty
            while (!queue.empty()) {  
                // get the first vertex in the queue
                int v = queue.front();  
                // remove the vertex from the queue
                queue.pop();  

                // iterate over all vertices in the graph
                for (int w = 0; w < adjSize; ++w) {  
                    // if there is an edge from v to w
                    if (adjMatrix[v][w] != 0) {  
                        // if w is not colored
                        if (color[w] == -1) {  
                            // color w with the opposite color of v
                            color[w] = 1 - color[v];  
                            // add w to the queue
                            queue.push(w);  
                        } 
                        // if w is already colored and has the same color as v
                        else if (color[w] == color[v]) {  
                            // the graph is not bipartite
                            return "0";  
                        }
                    }
                }
            }
        }
    }

    // variable to build the result string
    std::stringstream bipartiteSets;  
    // start building the string
    bipartiteSets << "the graph is bipartite: a={";  
    // helper variable to check position
    bool first = true;  
    // iterate over all vertices in the graph
    for (int i = 0; i < adjSize; ++i) {  
        // if the vertex is colored 0
        if (color[i] == 0) {  
            // if it is not the first vertex
            if (!first) {  
                // add comma and space
                bipartiteSets << ", ";  
            }
            // add the vertex to the string
            bipartiteSets << i;  
            // update the first variable
            first = false;  
        }
    }
    // continue building the string
    bipartiteSets << "}, b={";  
    // initialize the first variable
    first = true;  
    // iterate over all vertices in the graph
    for (int i = 0; i < adjSize; ++i) {  
        // if the vertex is colored 1
        if (color[i] == 1) {  
            // if it is not the first vertex
            if (!first) {  
                // add comma and space
                bipartiteSets << ", ";  
            }
            // add the vertex to the string
            bipartiteSets << i;  
            // update the first variable
            first = false;  
        }
    }
    // finish building the string
    bipartiteSets << "}";  
    // return the string
    return bipartiteSets.str();  
}

void Algorithms::negativeCycle(const Graph& g) {
    const std::vector<std::vector<int>>& adjMatrix = g.getAdjMatrix();  
    int adjSize = adjMatrix.size();  

    // vector for distances, initialized with max value
    std::vector<int> distance(adjSize, std::numeric_limits<int>::max());  
    // vector of prevs, initialized with -1
    std::vector<int> prev(adjSize, -1);  

    // distance from the starting vertex to itself is 0
    distance[0] = 0;  

    // relaxation of all edges n-1 times
    for (int i = 1; i < adjSize; ++i) {
        for (int u = 0; u < adjSize; ++u) {
            for (int v = 0; v < adjSize; ++v) {
                if (adjMatrix[u][v] != 0 && distance[u] != std::numeric_limits<int>::max() && distance[u] + adjMatrix[u][v] < distance[v]) {
                    distance[v] = distance[u] + adjMatrix[u][v];
                    prev[v] = u;
                }
            }
        }
    }

    // check if there is a negative cycle
    for (int u = 0; u < adjSize; ++u) {
        for (int v = 0; v < adjSize; ++v) {
            if (adjMatrix[u][v] != 0 && distance[u] != std::numeric_limits<int>::max() && distance[u] + adjMatrix[u][v] < distance[v]) {
                // found a negative cycle
                std::cout << "negative cycle found: ";
                int cycle_vertex = v;
                std::vector<int> cycle;
                std::unordered_set<int> visited;
                while (visited.find(cycle_vertex) == visited.end()) {
                    cycle.push_back(cycle_vertex);
                    visited.insert(cycle_vertex);
                    cycle_vertex = prev[cycle_vertex];
                }
                cycle.push_back(cycle_vertex);
                for (size_t i = 0; i < cycle.size(); ++i) {
                    std::cout << cycle[i];
                    if (i < cycle.size() - 1) {
                        std::cout << "->";
                    }
                }
                std::cout << std::endl;
                return;
            }
        }
    }

    // if no negative cycle is found
    std::cout << "no negative cycle found" << std::endl;
    }

}
