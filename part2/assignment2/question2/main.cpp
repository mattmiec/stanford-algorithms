#include <algorithm>
#include <cctype>
#include <fstream>
#include <iostream>
#include <unordered_map>
#include <sstream>
#include <string>
#include <vector>

#include "unionfind.h"

#define SEQTYPE unsigned long

std::unordered_map<SEQTYPE, KEYTYPE> readfile(std::string, unsigned int&);
SEQTYPE flipbit(SEQTYPE, unsigned int);
std::vector<SEQTYPE> get_neighbors(SEQTYPE, unsigned int);

int main() {

    unsigned int bits;
    //std::unordered_map<SEQTYPE, KEYTYPE> map = readfile("clustering_big.txt", bits);
    std::unordered_map<SEQTYPE, KEYTYPE> map = readfile("clustering_big.txt", bits);
    //std::cout << "datamap size is " <<  map.size() << std::endl;

    unsigned int clusters = map.size();
    SEQTYPE seq;

    unionfind uf(map.size());

    std::cout << clusters << " CLUSTERS" << std::endl;

    for (auto it1 = map.begin(); it1 != map.end(); ++it1) {
	seq = it1->first;
	std::vector<SEQTYPE> neighbors = get_neighbors(seq, bits);
	for (auto it2 = neighbors.begin(); it2 != neighbors.end(); ++it2) {
	    auto it3 = map.find(*it2);
	    if (it3 != map.end()) {
		if (uf.find(it1->second) != uf.find(it3->second)) {
		    uf.unite(it1->second, it3->second);
		    --clusters;
		    std::cout << clusters << " CLUSTERS" << std::endl;
		}
	    }
	}
    }
    std::cout << "MAX " << clusters << " CLUSTERS WITH SPACING >= 3" << std::endl;
}

// read data
std::unordered_map<SEQTYPE, KEYTYPE> readfile(std::string filename, unsigned int &bits) {

    // open file
    std::ifstream infile(filename);

    // string to hold each line
    std::string line;

    // read first line to get number of nodes and check number of bits
    std::getline(infile, line);
    std::stringstream linestream(line);
    KEYTYPE nodes;
    linestream >> nodes >> bits;

    // check whether we have enough bits
    if (bits > sizeof(SEQTYPE)*8) {
	throw "NOT ENOUGH BITS!";
    }

    // unordered map to return
    std::unordered_map<SEQTYPE, KEYTYPE> map;

    // id
    KEYTYPE id = 0;

    // read data
    while (std::getline(infile, line)) {
	line.erase(std::remove(line.begin(), line.end(), ' '), line.end());
	//std::cout << line << std::endl;
	if (map.find(std::stoul(line, nullptr, 2)) == map.end()) {
	    map[std::stoul(line, nullptr, 2)] = id;
	    ++id;
	}
    }

    // return map
    return map;
}

// get sequences with max distance 2
std::vector<SEQTYPE> get_neighbors(SEQTYPE seq, unsigned int bits) {
    std::vector<SEQTYPE> neighbors;
    SEQTYPE seqp, seqpp;
    for (int i = 0; i < bits; ++i) {
	seqp = flipbit(seq, i);
	neighbors.push_back(seqp);
	for (int j = 0; j < bits; ++j) {
	    if (i != j) {
		seqpp = flipbit(seqp, j);
		neighbors.push_back(seqpp);
	    }
	}
    }
    return neighbors;
}

// flip bit i of seq
SEQTYPE flipbit(SEQTYPE seq, unsigned int i) {
    seq ^=  1UL << i;
    return seq;
}
