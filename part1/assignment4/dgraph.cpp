// source file dgraph.cpp
#include "dgraph.h"
#include <iostream>
#include <algorithm>

dgraph::dgraph(std::ifstream& infile): t(0), s(0) {
  unsigned int n0, n1;
  while (infile >> n0) {
    infile >> n1;
    addedge(n0 - 1, n1 - 1);
  }
}

void dgraph::printgraph() const {
  std::cout << "nodes = " << nodes.size() << std::endl;
  for (unsigned int n = 0; n < nodes.size(); ++n) {
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
  for (unsigned int n = 0; n < nodes.size(); ++n) {
    rgraph.nodes[n].adjlist.clear();
  }
  for (unsigned int n = 0; n < nodes.size(); ++n) {
    for (auto iter = nodes[n].adjlist.begin(); iter != nodes[n].adjlist.end(); ++iter) {
      rgraph.addedge(*iter, n);
    }
  }
  *this = rgraph;
}

void dgraph::dfs(unsigned int i) {
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

void dgraph::scc(unsigned int k) {
  // calculate scc size by source vertex
  std::vector<unsigned int> scc_sizes(nodes.size());
  for (int i = 0; i < nodes.size(); ++i) {
    ++scc_sizes[nodes[i].sn];
  }
  // calcuate top k scc's
  unsigned int top[k];
  for (int j = 0; j < k; ++j) {
    top[j] = 0;
  }
  for (int i = 0; i < nodes.size(); ++i) {
    int l = -1;
    for (int j = 0; j < k; ++j) {
      if (scc_sizes[i] > top[j]) {
        if (l == -1) {
          l = j;
        } else {
          if (top[j] < top[l]) {
            l = j;
          }
        }
      }
    }
    if (l != -1) {
      top[l] = scc_sizes[i];
    }
  }
  std::sort(top, top + k);
  std::cout << "k largest SCCs:" << std::endl;
  for (int j = 0; j < k; ++j) {
    std::cout << top[j] << std::endl;
  }
}

void dgraph::addedge(unsigned int n0, unsigned int n1) {
  if (n0 >= nodes.size()) {
    nodes.resize(n0 + 1);
  }
  nodes[n0].adjlist.push_front(n1);
}
