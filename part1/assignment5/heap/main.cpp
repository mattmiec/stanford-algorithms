// source file main.cpp
#include <iostream>
#include <fstream>
#include "graph.h"
#include "timing.h"

// timing globals definition
std::clock_t cpu_t0, cpu_t1;
std::chrono::high_resolution_clock::time_point wall_t0, wall_t1;

int main()
{
  cpu_t0 = std::clock();
  wall_t0 = std::chrono::high_resolution_clock::now();
  try {
    std::ifstream infile("dijkstraData.txt");
    graph mygraph(infile);
    //mygraph.print()
    std::cout << "Elapsed time from start to after file read (ms):" << std::endl;
    timing();
    mygraph.shortest_path(0);
  }
  catch (char const* error) {
    std::cerr << error << std::endl;
  }
}
