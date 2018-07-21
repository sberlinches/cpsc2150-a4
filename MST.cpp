#include <iostream>
#include <sstream>
#include <fstream>
#include <vector>
#include <algorithm>

using namespace std;

struct Edges {
    unsigned int vertex;
    unsigned int toVertex;
    int weight;
};

struct Graph {
    unsigned int numberOfVertices;
    vector<Edges>* edges = new vector<Edges>;
};

void findMST(Graph*);
Graph* parseFile(const string&);
bool isConnected(Graph*);

/**
 * Assignment 4: Graphs - MST
 * Ayaka Adachi (100225327)
 * Sergio Berlinches (100291288)
 * 07/19/18
 *
 * @return
 */
int main() {

    const string filename1 = "sp7.txt";
    const string filename2 = "graph25.txt";

    auto graph = parseFile(filename1);
    findMST(graph);

    return 0;
}

/**
 * To find the minimum spanning tree of a graph, remove the edges which are not
 * necessary. The edges chosen for removal should be the edges of maximum weight
 * among those that can break any cycle in the tree. This algorithm somewhat
 * resembles the Kruskal method, but it works in the opposite direction.
 *
 * Use the above algorithm, and write a function named findMST to find the MST
 * for an undirected graph of distances between different cities which is
 * provided as an input file. The first line of input file represents the number
 * of nodes in the graph. Followed by the lines in which each represents an edge
 * of the graph and includes 3 values; city1, city2 and distance that are
 * separated by space. Your program should print out all the removed edges while
 * it is running. Finally, when the minimum spanning tree has been found, the
 * program should print the edges in the tree and the total distance.
 */
void findMST(Graph* graph) {

    auto isConnected2 = isConnected(graph);

    cout << "Is graph connected: " << (isConnected2? "true": "false") << endl;


    auto edges = graph->edges;

    std::sort(begin(*edges), end(*edges), [](const Edges& a, const Edges& b) {
        return a.weight < b.weight;
    });

    for (unsigned int i = 0; i < edges->size(); ++i)
        cout << edges->at(i).vertex
             << "->"
             << edges->at(i).toVertex
             << ":" << edges->at(i).weight
             << endl;
}

/**
 * Reads a file, parses it and returns an undirected weighted graph (UWG).
 * File format:
 * #nodes
 * origin destination weight
 * origin destination weight
 * ...
 *
 * @param filename The filename that contains the UWG
 * @return an UWG
 */
Graph* parseFile(const string& filename) {

    ifstream file(filename);

    if(!file)
        throw runtime_error("parseFile: File not found");

    auto graph = new Graph();
    string line;
    unsigned int a, b, c;

    // Reads the file line by line
    while (getline(file, line)) {

        istringstream iss(line);

        if (iss >> a >> b >> c)
            graph->edges->push_back({a,b,c});
        else
            graph->numberOfVertices = (unsigned)stoi(line);
    }

    file.close();
    return graph;
}

/**
 * Checks and returns whether the graph is connected or not using the union find
 * algorithm.
 * @param graph
 * @return Whether the graph is connected or not
 */
bool isConnected(Graph* graph) {

    unsigned int numberOfVertices = graph->numberOfVertices;
    unsigned int numberOfEdges = graph->edges->size();
    auto edges = graph->edges;

    // 1. if there's more vertices than edges, definitely is not connected
    if(numberOfVertices > numberOfEdges)
        return false;

    // 2. check if all the vertices are connected using the union-find algorithm
    unsigned int u[numberOfVertices];

    for (unsigned int i = 0; i < numberOfVertices; i++)
        u[i] = i;

    // 2.1. Iterates over the graph
    for (unsigned int i = 0; i < numberOfEdges; i++) {

        unsigned int prevVal = u[edges->at(i).vertex];

        // DEBUG
        cout << edges->at(i).vertex << "->" << edges->at(i).toVertex << " = ";
        for (unsigned int j = 0; j < numberOfVertices; j++)
            cout << u[j];
        cout << "->";

        // 2.1.1. Changes all the elements with the same value
        for (unsigned int j = 0; j < numberOfVertices; j++)
            if(u[j] == prevVal)
                u[j] = u[edges->at(i).toVertex];


        // DEBUG
        for (unsigned int j = 0; j < numberOfVertices; j++)
            cout << u[j];
        cout << endl;
    }

    // 3. Compares that all the values are the same
    unsigned int firstVal = u[0];
    for (unsigned int i = 1; i < numberOfVertices; i++)
        if(u[i] != firstVal)
            return false;

    return true;
}