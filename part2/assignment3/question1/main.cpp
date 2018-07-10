#include <algorithm>
#include <array>
#include <iostream>
#include <fstream>
#include <string>
#include <cstdio>

#define ulong unsigned long

int main() {

    // size of knapsack and number of items
    ulong size, number;

    // initialize input
    std::ifstream infile("knapsack1.txt");
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

    // initialize solution array
    ulong **solution = new ulong*[number + 1];
    for (ulong i = 0; i <= number; ++i) {
	solution[i] = new ulong[size + 1];
    }
    for (ulong j = 0; j <= size; ++j) {
	solution[0][j] = 0;
    }

    // solve
    for (ulong i = 1; i <= number; ++i) {
	for (ulong j = 0; j <= size; ++j) {
	    //std::cout << i << ", " << j << std::endl;
	    if ((long)j - (long)items[i - 1][1] < 0) {
		//std::cout << "case 1" << std::endl;
		solution[i][j] = solution[i - 1][j];
	    } else {
		//std::cout << "case 2" << std::endl;
		solution[i][j] = std::max(solution[i - 1][j], solution[i - 1][j - items[i - 1][1]] + items[i - 1][0]);
	    }
	    //std::cout << "solution = " << solution[i][j] << std::endl;
	}
    }

    std::cout << solution[number][size] << std::endl;


    return 0;

}
