// source file dgraph.cpp
#include "dgraph.h"
#include <iostream>
#include <algorithm>

dgraph::dgraph(std::ifstream& infile): t(0), s(0) {
  unsigned long n0, n1;
  while (infile >> n0) {
    infile >> n1;
    addedge(n0 - 1, n1 - 1);
  }
}

void dgraph::printgraph() const {
  std::cout << "nodes = " << nodes.size() << std::endl;
  for (unsigned long n = 0; n < nodes.size(); ++n) {
    std::cout << n + 1 << " : ";
    std::cout << "(t = " << nodes[n].tn + 1 << ", s = " <<  nodes[n].sn + 1 << ", e = " << nodes[n].explored << ") ";
    for (auto iter = nodes[n].adjlist.begin(); iter != nodes[n].adjlist.end(); ++iter) {
      std::cout << " " << *iter + 1;
    }
    std::cout << std::endl;
  }
}

void dgraph::reverse() {
  dgraph rgraph(*this);
  for (unsigned long n = 0; n < nodes.size(); ++n) {
    rgraph.nodes[n].adjlist.clear();
  }
  for (unsigned long n = 0; n < nodes.size(); ++n) {
    for (auto iter = nodes[n].adjlist.begin(); iter != nodes[n].adjlist.end(); ++iter) {
      rgraph.addedge(*iter, n);
    }
  }
  *this = rgraph;
}

void dgraph::dfs(unsigned long i) {
  nodes[i].explored = true;
  nodes[i].sn = s;
  for (auto iter = nodes[i].adjlist.begin(); iter != nodes[i].adjlist.end(); ++iter) {
    if (!nodes[*iter].explored) {
      dfs(*iter);
    }
  }
  nodes[i].tn = t;
  t++;
}

void dgraph::dfs_loop() {
  if (order.size() != nodes.size()) {
    // if first call to dfs_loop, set reverse ordering
    order.clear();
    for (int n = 0; n < nodes.size(); ++n) {
      order.push_back(n);
    }
  } else {
    // otherwise order by finish time from last call
    // and clear explored booleans
    for (int n = 0; n < nodes.size(); ++n) {
      order[nodes[n].tn] = n;
      nodes[n].explored = false;
    }
  }
  for (int n = nodes.size() - 1; n >= 0; --n) {
    s = n;
    if (!(nodes[order[n]].explored)) {
      dfs(order[n]);
    }
  }
}

void dgraph::addedge(unsigned long n0, unsigned long n1) {
  if (n0 >= nodes.size()) {
    nodes.resize(n0 + 1);
  }
  nodes[n0].adjlist.push_front(n1);
}

void dgraph::scc() {
  // execute kosaraju
  reverse();
  dfs_loop();
  reverse();
  dfs_loop();
  // strongly connected components are sets of nodes with identical nodes[i].sn
}

bool dgraph::check_scc(unsigned long n0, unsigned long n1) {
    if (nodes[n0].sn == nodes[n1].sn) {
	std::cout << "sn(" << n0 << ") = " << nodes[n0].sn << std::endl;
	std::cout << "sn(" << n1 << ") = " << nodes[n1].sn << std::endl;
	return true;
    } else {
	return false;
    }
}
