#ifndef GRAPH_UWD_H
#define GRAPH_UWD_H

#include <vector>

using namespace std;

/**
 * Undirected Weighted
 */
struct _UW {
    unsigned int vertex;
    unsigned int weight;
};

/**
 * Undirected Weighted Graph
 */
struct _UWG {
    unsigned int vertex;
    vector<_UW>* edges;
};

/**
 * Graph class
 */
class UWG {
private:
    vector<_UWG>* graph;
public:
    UWG(unsigned int);
    vector<_UWG>* getGraph() const;
    vector<unsigned int>* adjacent(unsigned int);
    void insertEdge(unsigned int, unsigned int, unsigned int);
    void print();
    ~UWG();
};

/**
 * Creates a graph.
 * @param numberOfVertices The number of vertices
 */
UWG::UWG(unsigned int numberOfVertices) {

    // Initializes an empty list of vertices
    graph = new vector<_UWG>(numberOfVertices);

    for (unsigned int i = 0; i < numberOfVertices; i++) {
        // Fills the vertices with its value
        graph->at(i).vertex = i;
        // Initializes a list of weights for each vertex
        graph->at(i).edges = new vector<_UW>;
    }
}

/**
 * Returns the graph.
 * @return The graph
 */
vector<_UWG>* UWG::getGraph() const {
    return graph;
}

/**
 * Returns the list of the adjacent vertices for the given vertex.
 * @param vertex
 * @return The list of the adjacent vertices for the given vertex
 */
vector<unsigned int>* UWG::adjacent(unsigned int vertex) {

    auto adjacent = new vector<unsigned int>;

    // Iterates over the edges of given vertex and extracts them
    for (unsigned int i = 0; i < graph->at(vertex).edges->size(); ++i)
        adjacent->push_back(graph->at(vertex).edges->at(i).vertex);

    return adjacent;
}

 /**
  * Insert an edge to the vertex.
  * @param vertex The vertex to insert
  * @param toVertex The other vertex of the edge
  * @param weight The weight of the edge
  */
void UWG::insertEdge(unsigned int vertex, unsigned int toVertex, unsigned int weight) {
    graph->at(vertex).edges->push_back({toVertex, weight});
}

/**
 * Prints the graph on terminal.
 * vertex: toVertex(weight)
 */
void UWG::print() {

    for (unsigned int i = 0; i < graph->size(); i++) {

        cout <<  graph->at(i).vertex << ":";

        for (unsigned int j = 0; j < graph->at(i).edges->size(); j++)
            cout << " " << graph->at(i).edges->at(j).vertex
                 << "("
                 << graph->at(i).edges->at(j).weight
                 << ")";

        cout << endl;
    }
}

/**
 * Auto-deletes the graph
 */
UWG::~UWG() {
    delete[] graph;
}

#endif
