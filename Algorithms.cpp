// noavrd@gmail.com
#include "Algorithms.hpp"
#include <list>
#define true 1
#define false 0
#define INT_MAX 999

using namespace std;
using namespace ariel;

/* 
 *  Check if a graph is connected, using BFS algoritem, with a list to check each vertex in a FIFO.
 *
 *  This function checks if all parts of a graph are connected. It starts from the first point and explores all connected points. 
 *  If it can reach all of the points, the graph is connected. 
 *  If not, the graph is disconnected. 
 *
 */
int Algorithms::isConnected(const Graph &g) {
    // get the number of vertices in a graph
    size_t size = g.graphSize();
    vector<int> checkVertex(size, 0);
    vector<vector<int>> adjMatrix = g.getMatrix();

    // starting the bfs from the first node
    list<size_t> verticsToCheck;
    verticsToCheck.push_back(0);  
    
    // check as long as it didn't check all the vertics
    // using BFS so it will start from the first elemnt in the list - fifo
    while (!verticsToCheck.empty()) {
        size_t node = verticsToCheck.front();  
        verticsToCheck.pop_front();  
        
        if (!checkVertex[node]) {
            // mark the current vertex as checked
            checkVertex[node] = 1;  
            
            for (size_t i = 0; i < size; ++i) {
                if (adjMatrix[node][i] != 0 && !checkVertex[i]) {
                    // Add connected unvisited nodes to the back of the list
                    verticsToCheck.push_back(i);  
                }
            }
        }
    }
    
    // check if all the vertics where vistied
    for (int vertex : checkVertex) {
        if (vertex == 0)
            return false;  
    }
    
    return true;  
}
/*
 *  Check what is the shortest path between a start and an end node in a graph using BFS.
 *
 *  It using a list that helps keep track which nodes needs to be visited next.
 *  It checks each node's neighbors one by one. If there is a path it will return the path, if not it will return -1.
 *
 */
string Algorithms::shortestPath(const Graph &g, size_t start, size_t end){
    size_t size = g.graphSize();
    // initialize path array to store previous nodes in the shortest path
    vector<size_t> path(size, (size_t) - 1);
    vector<vector<int>> adjMatrix = g.getMatrix();

    // initialize distance array to store shortest distances from the start node,
    // and give it 0 because the distance between a node to itself is 0
    vector<int> shortestDistance(size, -1);
    shortestDistance[start] = 0;

    // starting the bfs from the first node
    list<size_t> verticsToCheck;
    verticsToCheck.push_front(start);

    while (!verticsToCheck.empty()) {
        // get the next node to process and remove it
        size_t node = verticsToCheck.front();
        verticsToCheck.pop_front();

        // explore all neighbors of the current node
        for (size_t i = 0; i < size; i++) {
            // check if there is an edge from node to i
            if (adjMatrix[node][i] != 0) {
                // check if it wasn't visited, and if so than add it to the disance and updated the path
                if (shortestDistance[i] == -1) {
                    shortestDistance[i] = shortestDistance[node] + 1;
                    path[i] = node;
                    verticsToCheck.push_front(i);
                }
            }
        }
    }

    // change the path so it will start from the end
    string pathString;
    size_t currentNode = end;

    // check first if it can't reach the end node
    if (path[currentNode] == -1) {
        return "-1";
    }

    // if it can reach the end node then print the path
    pathString = to_string(currentNode);
    currentNode = path[currentNode];

    while (currentNode != -1) {
        pathString = to_string(currentNode) + "->" + pathString;
        currentNode = path[currentNode];
    }

    return pathString;
}

int Algorithms::isContainsCycle( const Graph &g ) { 
    size_t size = g.graphSize();
    vector<vector<int>> adjMatrix = g.getMatrix();

    vector<bool> visited(size, 0);
    vector<size_t> parent(size, (size_t)-1);

    for (size_t i = 0; i < size; ++i) {
        if (!visited[i]) {

            list<size_t> verticsToCheck;
            verticsToCheck.push_back(i);
            
            while (!verticsToCheck.empty()) {
                size_t node = verticsToCheck.back();
                verticsToCheck.pop_back();

                if (!visited[node]) {
                    visited[node] = 1;
                    for (size_t j = 0; j < size; ++j) {
                        if (adjMatrix[node][j] != 0) {
                            if (!visited[j]) {
                                verticsToCheck.push_back(j);
                                parent[j] = node;
                            } else if (parent[node] != j) {
                                return true;
                            }
                        }
                    }
                }
            }
        }
    }

    return false;
}


string Algorithms::isBipartite( const Graph &g ) {
    size_t size = g.graphSize();
    vector<vector<int>> adjMatrix = g.getMatrix();
    
    vector<int> twoGroups(size, -1);
    twoGroups[0] = 0;

    list<size_t> verticsToCheck;  
    verticsToCheck.push_back(0);

    while (!verticsToCheck.empty()) {
        size_t node = verticsToCheck.front();
        verticsToCheck.pop_front();

        for (size_t i = 0; i < size; ++i) {
            if (adjMatrix[node][i] != 0) {
                if (twoGroups[i] == -1) {
                    twoGroups[i] = 1 - twoGroups[node];
                    verticsToCheck.push_back(i);
                } else if (twoGroups[i] == twoGroups[node]) {
                        return "0"; 
                }
            }
        }
    }

    vector<int> firstSide, secondSide;

    for (size_t i = 0; i < size; ++i){
        if (twoGroups[i] == 0) {
            firstSide.push_back(i);
        }
        else {
            secondSide.push_back(i);
        }
    }

    string result = "The graph is bipartite: A={";

    for (size_t i = 0; i < firstSide.size(); ++i) {
        result += to_string(firstSide[i]);
        if (i != firstSide.size() - 1) {
            result += ", ";
        }
    }

    result += "}, B={";

    for (size_t i = 0; i < secondSide.size(); ++i) {
        result += to_string(secondSide[i]);
        if (i != secondSide.size() - 1) {
            result += ", ";
        }
    }

    result += "}";
    return result;
}

string Algorithms::negativeCycle( const Graph &g ) {
    if(!isContainsCycle(g)) {
        return "There is no negative cycle";
    }

    size_t size = g.graphSize();
    vector<vector<int>> adjMatrix = g.getMatrix();

    vector<int> distance(size, -1); 
    distance[0] = 0;

    for (size_t i = 0; i < size - 1; ++i) {
        for (size_t w = 0; w < size; ++w) {
            for (size_t v = 0; v < size; ++v) {
                if (adjMatrix[w][v] != 0) {
                    if (distance[w] != -1 && distance[w] + adjMatrix[w][v] < distance[v]) {
                        distance[v] = distance[w] + adjMatrix[w][v];
                    }
                }
            }
        }
    }

    for (size_t w = 0; w < size; ++w) {
        for (size_t v = 0; v < size; ++v) {
            if (adjMatrix[w][v] != 0) {
                if (distance[w] != -1 && distance[w] + adjMatrix[w][v] < distance[v]) {
                    return "found from "+ std::to_string(distance[w]);
                }
            }
        }
    }

    return "There is no negative cycle";
}