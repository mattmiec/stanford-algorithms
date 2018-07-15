// header file dgraph.h
#ifndef GUARD_dgraph_h
#define GUARD_dgraph_h

#include <fstream>
#include <vector>
#include <forward_list>

struct node {
  unsigned long tn, sn;
  bool explored;
  std::forward_list<unsigned long> adjlist;
};

class dgraph {
 public:
  unsigned long t, s;
  dgraph() {};
  dgraph(std::ifstream&);
  void printgraph() const;
  void reverse();
  void dfs(unsigned long);
  void dfs_loop();
  void scc();
  bool check_scc(unsigned long, unsigned long);
  void addedge(unsigned long, unsigned long);
 private:
  std::vector<node> nodes;
  std::vector<unsigned long> order;
};

#endif
