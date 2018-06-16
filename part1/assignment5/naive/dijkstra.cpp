// source file dijkstra.cpp
#include "dijkstra.h"
#include <iostream>
#include <string>
#include <sstream>
#include <cstdio>
#include <map>

graph::graph(std::ifstream& infile) {
  unsigned int n0, n1, d;
  std::string line;
  std::string edge;
  while (std::getline(infile, line)) {
    std::istringstream linestream(line);
    linestream >> n0;
    while (linestream >> edge) {
      if (std::sscanf(edge.c_str(), "%u,%u", &n1, &d) != 2) {
        throw "Error reading edge values!";
      }
      addedge(n0 - 1, n1 - 1, d);
    }
  }
}

void graph::printgraph() const {
  std::cout << "nodes = " << nodes.size() << std::endl;
  for (unsigned int n = 0; n < nodes.size(); ++n) {
    std::cout << n + 1 << ": ";
    for (auto iter = nodes[n].adjlist.begin(); iter != nodes[n].adjlist.end(); ++iter) {
      std::cout << " " << iter->n1 + 1 << "," << iter->d;
    }
    std::cout << std::endl;
  }
}

void graph::addedge(unsigned int n0, unsigned int n1, unsigned int d) {
  if (n0 >= nodes.size()) {
    nodes.resize(n0 + 1);
  }
  edge newedge;
  newedge.n1 = n1;
  newedge.d = d;
  nodes[n0].adjlist.push_front(newedge);
}

void shortest_path(graph g, unsigned int s) {
  std::map<unsigned int, unsigned int> completed;
  completed[s] = 0;

  // main do loop, iterate until no eligible edges
  bool foundedge;
  do {
    foundedge = false;
    // variables to hold node to be added and lowest dijkstra score
    unsigned int nextnode = s;
    unsigned int minscore = 1000000;
    // iterate over completed nodes
    for (auto it1 = completed.begin(); it1 != completed.end(); ++it1) {
      // iterate over completed node edges
      for (auto it2 = g.nodes[it1->first].adjlist.begin(); it2 != g.nodes[it1->first].adjlist.end(); ++it2) {
        // check whether edge is eligible (does not lead to a completed node)
        if (completed.find(it2->n1) == completed.end()) {
          // set foundedge so outer do loop continues
          foundedge = true;
          // set nextnode and minscore if dijkstra score is lowest so far
          if (it2->d + it1->second < minscore) {
            nextnode = it2->n1;
            minscore = it2->d + it1->second;
          }
        }
      }
    }
    completed[nextnode] = minscore;

  } while (foundedge == true);

  // output shortest-paths for vertices requested in problem set
  unsigned int vertices[] = {7, 37, 59, 82, 99, 115, 133, 165, 188, 197};
  for (auto v : vertices) {
    std::cout << "Shortest path to vertex " << v << ":  " << completed[v - 1] << std::endl;
  }
}
