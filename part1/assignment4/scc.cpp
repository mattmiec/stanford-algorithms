// source file scc.cpp
#include <iostream>
#include <fstream>
#include "dgraph.h"

int main()
{
  std::ifstream infile("SCC.txt");
  dgraph graph(infile);
  graph.reverse();
  graph.dfs_loop();
  graph.reverse();
  graph.dfs_loop();
  graph.scc(5);
}
