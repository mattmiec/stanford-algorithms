// source file graph.cpp
#include "graph.h"
#include "heap.h"
#include "timing.h"
#include <iostream>
#include <string>
#include <sstream>
#include <cstdio>
#include <unordered_map>

// create graph from file
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
void graph::addedge(unsigned int n0, unsigned int n1, unsigned int d) {
  if (n0 >= adjlist.size()) {
    adjlist.resize(n0 + 1);
  }
  edge newedge;
  newedge.n1 = n1;
  newedge.d = d;
  adjlist[n0].push_front(newedge);
}

// Dijkstra shortest path
void graph::shortest_path(unsigned int s) {

  // map to hold shortest paths
  std::unordered_map<unsigned int, unsigned int> completed;
  completed[s] = 0;

  // initialize heap
  heap h;
  for (auto it = adjlist[s].begin(); it != adjlist[s].end(); ++it) {
    h.add_node(it->n1, it->d);
  }

  // main do loop, iterate until heap is empty
  while (!h.is_empty()) {

    // get next node from heap and add to completed
    heapnode nextnode = h.extract_min();
    completed[nextnode.nodeid] = nextnode.score;

    // iterate over node's edges, adding to heap if not completed
    for (auto it = adjlist[nextnode.nodeid].begin(); it != adjlist[nextnode.nodeid].end(); ++it) {
      if (completed.find(it->n1) == completed.end()) {
        h.add_node(it->n1, nextnode.score + it->d);
      }
    }
  }

  std::cout << "Elapsed time from start of shortest_path to after main do loop (ms):" << std::endl;
  timing();

  // output shortest-paths for vertices requested in problem set
  unsigned int vertices[] = {7, 37, 59, 82, 99, 115, 133, 165, 188, 197};
  for (auto v : vertices) {
    std::cout << "Shortest path to vertex " << v << ":  " << completed[v - 1] << std::endl;
  }

  std::cout << "Elapsed time from after main do loop to after output (ms):" << std::endl;
  timing();
}
