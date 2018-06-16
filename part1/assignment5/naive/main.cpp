// source file main.cpp
#include <iostream>
#include <fstream>
#include "dijkstra.h"

int main()
{
  std::ifstream infile("dijkstraData.txt");
  graph mygraph(infile);
  shortest_path(mygraph, 0);
}
