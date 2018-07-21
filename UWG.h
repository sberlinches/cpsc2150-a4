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
    unsigned int numberOfVertices;
    unsigned int numberOfEdges;
public:
    UWG(unsigned int);
    vector<_UWG>* getGraph() const;
    vector<unsigned int>* adjacent(unsigned int);
    void insertEdge(unsigned int, unsigned int, unsigned int);
    bool isConnected();
    void print();
    ~UWG();
};

/**
 * Creates a graph.
 * @param numberOfVertices The number of vertices
 */
UWG::UWG(unsigned int numberOfVertices) {

    this->numberOfVertices = numberOfVertices;

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
    numberOfEdges++;
}

/**
 * Checks and returns whether the graph is connected or not.
 * @return Whether the graph is connected or not
 */
bool UWG::isConnected() {

    // 1. if there's more vertices than edges, definitely is not connected
    if(numberOfVertices > numberOfEdges)
        return false;

    // 2. check if all the vertices are connected using the union-find algorithm
    // TODO: This implementation doesn't seems efficient
    unsigned int uf[graph->size()];

    for (unsigned int i = 0; i < graph->size(); i++)
        uf[i] = i;

    for (unsigned int i = 0; i < graph->size(); i++) {
        for (unsigned int j = 0; j < graph->at(i).edges->size(); j++) {

            unsigned int prevVal = uf[i];

            for (unsigned int k = 0; k < graph->size(); k++)
                if(uf[k] == prevVal)
                    uf[k] = uf[graph->at(i).edges->at(j).vertex];

            // DEBUG
            /*cout << prevVal << "->" << graph->at(i).edges->at(j).vertex << " = ";
            for (unsigned int l = 1; l < graph->size(); l++)
                cout << uf[l];
            cout << endl;*/
        }
    }

    // 3. Compares that all the values are the same
    unsigned int firstVal = uf[0];
    for (unsigned int i = 1; i < graph->size(); i++)
        if(uf[i] != firstVal)
            return false;

    return true;
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
