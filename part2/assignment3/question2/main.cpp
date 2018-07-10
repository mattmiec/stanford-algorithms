#include <algorithm>
#include <array>
#include <iostream>
#include <fstream>
#include <string>
#include <cstdio>
#include <boost/unordered_map.hpp>
#include <utility>

#define ulong unsigned long

ulong knapsack(ulong number, ulong size, ulong items[][2]) {

    static boost::unordered_map<std::pair<ulong, ulong>, ulong> solution;

    ulong mysolution;

    //std::cout << "calling knapsack with number = " << number << ", size = " << size << std::endl;

    if (number == 0 || size == 0) {
	return 0;
    } else if (solution.find(std::pair<ulong, ulong>(number, size)) != solution.end()) {
	//std::cout << "found cached solution!" << std::endl;
	return solution[std::pair<ulong, ulong>(number, size)];
    } else if ((long)size - (long)items[number - 1][1] < 0){
	mysolution =  knapsack(number - 1, size, items);
	solution[std::pair<ulong, ulong>(number, size)] = mysolution;
	return mysolution;
    } else {
	mysolution =  std::max(knapsack(number - 1, size, items), knapsack(number - 1, size - items[number - 1][1], items) + items[number - 1][0]);
	solution[std::pair<ulong, ulong>(number, size)] = mysolution;
	return mysolution;
    }

}

int main() {

    // size of knapsack and number of items
    ulong size, number;

    // initialize input
    std::ifstream infile("knapsack_big.txt");
    std::string line;

    // read in header data
    std::getline(infile, line);
    std::sscanf(line.c_str(),"%lu %lu", &size, &number);

    // allocate array for item values, sizes
    auto items = new ulong[number][2];

    // read in item data
    for (ulong i = 0; i < number; ++i) {
	std::getline(infile, line);
	std::sscanf(line.c_str(), "%lu %lu", &items[i][0], &items[i][1]);
    }

    // solve and print result
    std::cout << knapsack(number, size, items) << std::endl;

    return 0;

}

