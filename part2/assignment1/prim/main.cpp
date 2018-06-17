// source file main.cpp
#include <iostream>
#include <fstream>
#include "graph.h"

int main()
{
  try {
    std::ifstream infile("edges.txt");
    graph mygraph(infile);
    //mygraph.print();
    mygraph.prim(0);
  }
  catch (char const* error) {
    std::cerr << error << std::endl;
  }
}
