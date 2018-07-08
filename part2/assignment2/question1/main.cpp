#define keytype unsigned int
#define dtype unsigned int

#include <algorithm>
#include <cstdio>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

#include "unionfind.h"

struct edge {
    keytype key1, key2;
    dtype d;
    bool operator<(const edge e2) const {
	return d < e2.d;
    }
};

int main() {

    std::vector<edge> edgelist;
    keytype nodes;

    // read in edge list
    std::cout << "reading in edge list" << std::endl;
    std::ifstream infile("clustering1.txt");
    keytype n0, n1;
    dtype d;
    std::string line;
    std::getline(infile, line);
    if (std::sscanf(line.c_str(), "%u", &nodes) != 1) { // read number of nodes
	throw "Error reading number of nodes!";
    }
    while (std::getline(infile, line)) { // then read edges one by one
	if (std::sscanf(line.c_str(), "%u %u %u", &n0, &n1, &d) != 3) {
	   throw "Error reading edge!";
	}
	edge newedge;
	newedge.key1 = n0 - 1;
	newedge.key2 = n1 - 1;
	newedge.d = d;
	edgelist.push_back(newedge);
    }

    // sort edge list using overloaded < operator
    std::sort(edgelist.begin(), edgelist.end());

    // initialize unionfind
    unionfind myuf(nodes);

    // iterate through edge list carrying out Kruskal's algorithm
    // use variable nodes to keep track of # of clusters
    for (auto it = edgelist.begin(); it  != edgelist.end(); ++it) {
	std::cout << "checking edge " << it->key1 << " " << it->key2 << std::endl;
	if (myuf.find(it->key1) != myuf.find(it->key2)) {
	   if (nodes <= 4) {
		std::cout << "spacing: " << it->d << std::endl;
		break;
	   }
	    std::cout << "uniting " << it->key1 << " and " << it->key2 << std::endl;
	    myuf.unite(it->key1, it->key2);
	    --nodes;
	    std::cout << nodes << " clusters" << std::endl;
	}
    }

    return 0;
}
