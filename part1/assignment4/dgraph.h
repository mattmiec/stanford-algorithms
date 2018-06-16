// header file dgraph.h
#ifndef GUARD_dgraph_h
#define GUARD_dgraph_h

#include <fstream>
#include <vector>
#include <forward_list>

struct node {
  unsigned int tn, sn;
  bool explored;
  std::forward_list<unsigned int> adjlist;
};

class dgraph {
 public:
  unsigned int t, s;
  dgraph(std::ifstream&);
  void printgraph() const;
  void reverse();
  void dfs(unsigned int);
  void dfs_loop();
  void scc(unsigned int);
 private:
  std::vector<node> nodes;
  std::vector<unsigned int> order;
  void addedge(unsigned int, unsigned int);
};

#endif
