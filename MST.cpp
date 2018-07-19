#include <iostream>
#include <sstream>
#include <fstream>
#include "UWG.h"

void findMST(UWG*);
UWG* parseUWGFile(const string&);

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

    auto uwg = parseUWGFile(filename1);
    findMST(uwg);

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
void findMST(UWG* uwg) {
    uwg->print();
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
UWG* parseUWGFile(const string& filename) {

    ifstream file(filename);

    if(!file)
        throw runtime_error("parseFile: File not found");

    UWG* uwg;
    string line;
    unsigned int a, b, c;

    // Reads the file line by line
    while (getline(file, line)) {

        istringstream iss(line);

        // If the stream has the output (int int int)
        if (iss >> a >> b >> c)
            uwg->insertEdge(a, b, c);
        else
            uwg = new UWG((unsigned)stoi(line));
    }

    file.close();
    return uwg;
}