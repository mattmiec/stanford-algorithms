#include <algorithm>
#include <iostream>
#include <cstdio>
#include <fstream>
#include <cmath>
#include <string>
#include "array3d.h"

#define ul unsigned long

int main(int argc, char** argv) {

    std::ifstream infile(argv[1]);
    std::string line;
    ul vertices, edges;

    std::getline(infile, line);

    std::sscanf(line.c_str(), "%lu %lu", &vertices, &edges);

    std::cout << "vertices = " << vertices << ", edges = " << edges << std::endl;

    array3d<long> myarray(vertices, vertices, vertices + 1);

    // initialize all values to max val of long
    std::cout << "initializing array" << std::endl;
    for (ul l = 0; l < vertices; ++l) {
	for (ul m = 0; m < vertices; ++m) {
	    for (ul n = 0; n < vertices + 1; ++n) {
		myarray(l, m, n) = std::pow(2, 31);
	    }
	}
	std::cout << "l = " << l << std::endl;
    }

    ul v1, v2;
    long d;

    std::cout << "reading in edges to A(i, j, 0)" << std::endl;
    while (std::getline(infile, line)) {
	std::sscanf(line.c_str(), "%lu %lu %ld", &v1, &v2, &d);
	myarray(v1 - 1, v2 - 1 , 0) = d;
	std::cout << "setting myarray(" << v1 - 1 << "," << v2 - 1 << ") = " << d << std::endl;;
    }

    std::cout << "setting A(i, i, 0) = 0" << std::endl;
    for (ul l = 0; l < vertices; ++l) {
	myarray(l, l, 0) = 0;
    }

    std::cout << "solving for shortest paths" << std::endl;
    for (ul k = 1; k < vertices + 1; ++k) {
	for (ul i = 0; i < vertices; ++i) {
	    for (ul j = 0; j < vertices; ++j) {
		myarray(i, j, k) = std::min(myarray(i, j, k - 1), myarray(i, k - 1, k - 1) + myarray(k - 1, j, k - 1));
	    }
	    if (myarray(i, i, k) < 0) {	
		std::cout << "found negative cycle!" << std::endl;
		return 1;
	    }
	}
	std::cout << "k = " << k << std::endl;
    }

    long sp = std::pow(2, 31);
    std::cout << "finding shortest shortest path" << std::endl;
    for (ul i = 0; i < vertices; ++i) {
	for (ul j = 0; j < vertices; ++j) {
	    if (i != j) {
		sp = std::min(sp, myarray(i, j, vertices));
	    }
	}
    }

    std::cout << "shortest path is " << sp << std::endl;

    return 0;
}
