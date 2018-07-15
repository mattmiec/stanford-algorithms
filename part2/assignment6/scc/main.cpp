#include <cmath>
#include <fstream>
#include <iostream>
#include "dgraph.h"

unsigned long readvar(long n) {
    // return index to var from input file
    if (n > 0) {
	return 2 * (n - 1);
    } else {
	return 2 * (std::abs(n) - 1) + 1;
    }
}

unsigned long negate(unsigned long n) {
    // return index to negation of variable given by index n
    if (n % 2 == 0) {
	return n + 1;
    } else {
	return n - 1;
    }
}

int main(int argc, char** argv) {

    long number;
    std::ifstream infile(argv[1]);
    std::string line;

    // directed graph to represent clauses
    // variable x1 is represented by node index 2 * x1 (assuming indexing from 0)
    // while !x1 is represented by node index 2 * x1 + 1 (assuming indexing from 0)
    dgraph mygraph;

    // read in number
    std::getline(infile, line);
    if (std::sscanf(line.c_str(), "%ld", &number) != 1) {
	throw "failed to read number!";
    }

    // read in clauses as pair of edges
    for (long i = 0; i < number; ++i) {
	long x1, x2;
	std::getline(infile, line);
	if (std::sscanf(line.c_str(), "%ld %ld", &x1, &x2) != 2) {
	    throw "failed to read clause!";
	}
	unsigned long index1 = readvar(x1);
	unsigned long index2 = readvar(x2);
	mygraph.addedge(negate(index1), index2);
	mygraph.addedge(negate(index2), index1);
    }

    mygraph.scc();
    for (long i = 0; i < number; ++i) {
	if (mygraph.check_scc(2 * i, 2 * i + 1)) {
	    std::cout << "instance is unsatisfiable!" << std::endl;
	    return 1;
	}
    }

    std::cout << "instance is satisfiable!" << std::endl;
    return 0;
}
