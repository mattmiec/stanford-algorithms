#include <algorithm>
#include <bitset>
#include <cstdio>
#include <iostream>
#include <fstream>
#include <cmath>
#include <limits>
#include <string>
#include <vector>

#define settype unsigned long
#define ul unsigned long

settype addnode(settype s, unsigned int i) {
    // set bit i of s to 1
    return s | ((settype) 1 << i);
}

settype delnode(settype s, unsigned int i) {
    // set bit i of s to 0
    return s & ~((settype) 1 << i);
}

bool checknode(settype &s, unsigned int i) {
    // check whether node is in s
    return ((s >> i) & (settype) 1);
}

void get_combinations(settype &s, std::vector<settype> &returnvec, unsigned int offset, unsigned int m, unsigned int nodes) {
    // find combinations of m nodes
    // outer call with s = 1, offset = 1
    // m recursive calls set m other bits to 1
    if (m == 0) {
	returnvec.push_back(s);
    } else {
	for (int i = offset; i < nodes; ++i) {
	    s = addnode(s, i);
	    get_combinations(s, returnvec, i + 1, m - 1, nodes);
	    s = delnode(s, i);
	}
    }

}

void print_array(double** array, unsigned int nodes) {
    for (ul i = 0; i < (settype) std::pow(2, nodes); ++i) {
	for (int j = 0; j < nodes; ++j) {
	    std::cout << "array[" << i << "][" << j << "] = " << array[i][j] << std::endl;
	}
    }
}

int main(int argc, char** argv) {

    unsigned int nodes;
    std::ifstream infile(argv[1]);
    std::string line;

    std::getline(infile, line);
    std::sscanf(line.c_str(), "%u", &nodes);

    if (nodes > sizeof(settype) * 8) {
	std::cout << "not enough bits in setype";
    }

    // read in coordinates
    auto coordinates = new double[nodes][2];

    for (int i = 0; i < nodes; ++i) {
	std::getline(infile, line);
	if (std::sscanf(line.c_str(), "%lf %lf", &coordinates[i][0], &coordinates[i][1]) != 2) {
	    throw "failed to read coordinates!";
	}
    }

    // calculate distances
    double** dist = new double*[nodes];
    for (int i = 0; i < nodes; ++i) {
	dist[i] = new double[nodes];
	for (int j = 0; j < nodes; ++j) {
	    dist[i][j] = std::sqrt(std::pow(coordinates[i][0] - coordinates[j][0], 2) + std::pow(coordinates[i][1] - coordinates[j][1], 2));
	    //std::cout << "dist[" << i << "][" << j << "] = " << dist[i][j] << std::endl;
	}
    }

    // initialize subproblem solution array
    double** array = new double*[(settype) std::pow(2, nodes)];
    //std::cout << "allocated " << (settype) std::pow(2, nodes) << " rows" << std::endl;
    for (ul i = 0; i < (settype) std::pow(2, nodes); ++i) {
	array[i] = new double[nodes];
	//std::cout << "allocated " << nodes << " columms" << std::endl;
	for (int j = 0; j < nodes; ++j) {
	    array[i][j] = std::numeric_limits<double>::max();
	}
    }
    //print_array(array, nodes);

    // initialize A[{1}, 0] to 0
    array[1][0] = 0;

    // outer loop over set size
    for (int m = 1; m < nodes; ++m) {
	std::cout << "m = " << m << std::endl;
	// get combinations
	std::vector<settype> combinations;
	settype s = 1;
	get_combinations(s, combinations, 1, m, nodes);

	// loop over combinations
	std::cout << "looping over " << combinations.size() << " combinations" << std::endl;
	for (ul i = 0; i < combinations.size(); ++i) {
	    //std::cout << std::bitset<sizeof(settype)*8>(combinations[i]) << std::endl;
	    // outer loop over nodes in combination
	    for (int j = 1; j < nodes; ++j) {
		if (checknode(combinations[i], j)) {
		    // inner loop over nodes in combination
		    for (int k = 0; k < nodes; ++k) {
			if (checknode(combinations[i], k) && j != k) {
			    array[combinations[i]][j] = std::min(array[delnode(combinations[i], j)][k] + dist[j][k], array[combinations[i]][j]);
			}
		    }
		}
	    }
	}
	//print_array(array, nodes);
    }

    double tsp = std::numeric_limits<double>::max();
    // construct full set
    settype s = 0;
    for (int i = 0; i < nodes; ++i) {
	s = addnode(s, i);
    }
    // final loop to find min distance back to node 0
    for (int i = 1; i < nodes; ++i) {
	tsp = std::min(tsp, array[s][i] + dist[i][0]);

    }

    // print solution
    std::cout << "solution = " << tsp << std::endl;
}
