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
 *  @return 1 if the graph is conneced, if not it will return 0.
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
 *  It checks each node's neighbors one by one.
 *  
 *  @return If there is a path it will return the path, if not it will return -1.
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

/**
 *  Checks if the graph contains a cycle.
 * 
 *  This function uses DFS to find cycles in a graph.
 *  It uses a visited list and a parent list to keep track of nodes and their parents. 
 *  If we find an edge that connects back to a node that's not its direct parent, it means there's a cycle in the graph.
 * 
 *  @return 1 if a cycle is found, otherwise 0.
 */
int Algorithms::isContainsCycle(const Graph &g) { 
    size_t size = g.graphSize();
    vector<vector<int>> adjMatrix = g.getMatrix();

    // Keeps track of visited nodes
    vector<bool> visited(size, 0); 

    // Stores the parent of each node
    vector<size_t> parent(size, (size_t)-1); 

    for (size_t i = 0; i < size; ++i) {
        if (!visited[i]) {
            // List to use in DFS
            list<size_t> verticsToCheck; 
            verticsToCheck.push_back(i);
            
            while (!verticsToCheck.empty()) {
                size_t node = verticsToCheck.back();
                verticsToCheck.pop_back();

                if (!visited[node]) {
                    visited[node] = 1;
                    for (size_t j = 0; j < size; ++j) {
                        // Check for nodes near the current one
                        if (adjMatrix[node][j] != 0) { 
                            if (!visited[j]) {
                                verticsToCheck.push_back(j);
                                parent[j] = node;

                            // A cycle has been found
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

/**
 *  Checks if the graph is bipartite.
 * 
 *  This function checks if the graph can be colored using two colors such that no two nodes next to each node
 *  have the same color. It uses BFS to try and assign colors to each node. If any two nodes near eachothers have
 *  the same color, the graph is not bipartite.
 * 
 *  @return A string that shows if the graph is bipartite and listing the two sets of nodes.
 *  If it's not bipartite it will return 0.
 */
string Algorithms::isBipartite(const Graph &g) {
    size_t size = g.graphSize();
    vector<vector<int>> adjMatrix = g.getMatrix();
    
    // Color assignment for nodes, and give the first node color 0
    vector<int> twoGroups(size, -1);
    twoGroups[0] = 0; 

    list<size_t> verticsToCheck;  
    verticsToCheck.push_back(0);

    while (!verticsToCheck.empty()) {
        size_t node = verticsToCheck.front();
        verticsToCheck.pop_front();

         for (size_t i = 0; i < size; ++i) {
            // Check nodes near each other
            if (adjMatrix[node][i] != 0) { 
            // If node is not colored yet
                if (twoGroups[i] == -1) { 
                    // give ulternative color
                    twoGroups[i] = 1 - twoGroups[node];
                    verticsToCheck.push_back(i);
                } else if (twoGroups[i] == twoGroups[node]) {
                    // if 2 nodes near each other has the same color, it's not bipartite
                    return "0"; 
                }
            }
        }
    }

    // create the sets of nodes for each color group.
    vector<int> firstSide, secondSide;

    for (size_t i = 0; i < size; ++i){
        if (twoGroups[i] == 0) {
            firstSide.push_back(i);
        } else {
            secondSide.push_back(i);
        }
    }

    // create the string for the two different color if it's bipartite
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

/**
 *  Check if there is a negative weight cycle in the graph.
 * 
 *  This function uses the Bellman-Ford algorithm to detect negative weight cycles. It first checks
 *  if there is any cycle in the graph using isContainsCycle.
 *  Then, it calculates the shortest paths and checks for negative weight cycles by running an extra iteration.
 * 
 *  @return A string of the negative cycle if it's exist 0 if there is no negative cycle.
 */
string Algorithms::negativeCycle(const Graph &g) {
    if (!isContainsCycle(g)) {
        return "0";
    }

    size_t size = g.graphSize();
    vector<vector<int>> adjMatrix = g.getMatrix();

    // initialize distance from the starting node
    vector<int> distance(size, -1); 
    distance[0] = 0; 

    // check distance for each node
    for (size_t i = 0; i < size - 1; ++i) {
        for (size_t j = 0; j < size; ++j) {
            for (size_t k = 0; k < size; ++k) {
                if (adjMatrix[j][k] != 0) {
                    if (distance[j] != -1 && distance[j] + adjMatrix[j][k] < distance[k]) {
                        distance[k] = distance[j] + adjMatrix[j][k];
                    }
                }
            }
        }
    }

    // Check for negative weight cycles.
    for (size_t j = 0; j < size; ++j) {
        for (size_t k = 0; k < size; ++k) {
            if (adjMatrix[j][k] != 0) {
                if (distance[j] != -1 && distance[j] + adjMatrix[j][k] < distance[k]) {
                    return "Negative cycle: " + to_string(distance[j]);
                }
            }
        }
    }

    return "0"; 
}
