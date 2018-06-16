// header file dijkstra.h
#ifndef GUARD_dijkstra_h
#define GUARD_dijkstra_h

#include <fstream>
#include <vector>
#include <forward_list>

struct edge {
  unsigned int n1, d;
};

struct node {
  unsigned int l;
  bool explored;
  std::forward_list<edge> adjlist;
};

class graph {
  friend void shortest_path(graph, unsigned int);
 public:
  graph(std::ifstream&);
  void printgraph() const;
 private:
  std::vector<node> nodes;
  void addedge(unsigned int, unsigned int, unsigned int);
};

void shortest_path(graph, unsigned int);

class heap {

#endif
