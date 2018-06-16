// header file graph.h
#ifndef GUARD_graph_h
#define GUARD_graph_h

#include <fstream>
#include <vector>
#include <forward_list>

// struct used by graph
struct edge {
  unsigned int n1, d;
};

// class to store and manipulate graph
class graph {
 public:
  graph(std::ifstream&);
  void print() const;
  // Dijkstra shortest path
  void shortest_path(unsigned int);
 private:
  std::vector<std::forward_list<edge>> adjlist;
  void addedge(unsigned int, unsigned int, unsigned int);
};

#endif
