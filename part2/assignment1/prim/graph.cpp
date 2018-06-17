// source file graph.cpp
#include "graph.h"
#include "heap.h"
#include <iostream>
#include <string>
#include <sstream>
#include <cstdio>
#include <unordered_set>

// create graph from file
graph::graph(std::ifstream& infile) {
  unsigned int n0, n1;
  int d;
  std::string line;
  std::getline(infile, line); // read number of nodes, edges (but not needed)
  while (std::getline(infile, line)) {
    if (std::sscanf(line.c_str(), "%u %u %d", &n0, &n1, &d) != 3) {
      throw "Error reading edge!";
    }
    addedge(n0 - 1, n1 - 1, d);
  }
}

// print graph
void graph::print() const {
  std::cout << "nodes = " << adjlist.size() << std::endl;
  for (unsigned int n = 0; n < adjlist.size(); ++n) {
    std::cout << n + 1 << ": ";
    for (auto iter = adjlist[n].begin(); iter != adjlist[n].end(); ++iter) {
      std::cout << " " << iter->n1 + 1 << "," << iter->d;
    }
    std::cout << std::endl;
  }
}

// add edge
void graph::addedge(unsigned int n0, unsigned int n1, int d) {
  if (n0 >= adjlist.size()) {
    adjlist.resize(n0 + 1);
  }
  if (n1 >= adjlist.size()) {
    adjlist.resize(n1 + 1);
  }
  edge newedge;
  newedge.d = d;
  newedge.n1 = n1;
  adjlist[n0].push_front(newedge);
  newedge.n1 = n0;
  adjlist[n1].push_front(newedge);
}

// Prim's MST
void graph::prim(unsigned int s) {

  // set to hold completed vertices
  std::unordered_set<unsigned int> completed;
  completed.insert(s);

  // initialize heap with vertices adjacent to s
  heap h;
  for (auto it = adjlist[s].begin(); it != adjlist[s].end(); ++it) {
    h.add_node(it->n1, it->d);
  }

  // initialize MST cost
  long int total = 0;

  // main do loop, iterate until heap is empty
  while (!h.is_empty()) {

    // get next node from heap and add to completed
    heapnode nextnode = h.extract_min();
    completed.insert(nextnode.nodeid);
    total += nextnode.score;
    std::cout << std::endl;
    std::cout << "adding node " << nextnode.nodeid + 1 << std::endl;
    std::cout << "total is now " << total << std::endl;

    // iterate over node's edges, adding to heap if not completed
    for (auto it = adjlist[nextnode.nodeid].begin(); it != adjlist[nextnode.nodeid].end(); ++it) {
      if (completed.find(it->n1) == completed.end()) {
        h.add_node(it->n1, it->d);
      }
    }
    h.check();
  }

  // output total cost
  std::cout << std::endl;
  std::cout << "MST cost: " << total << std::endl;
}
