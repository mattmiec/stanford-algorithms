#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>

typedef std::vector<std::pair<long, long> > clausevec;

clausevec get_violations(clausevec clauses, bool* vars) {
    clausevec violations;
    // loop over all clauses
    for (auto it = clauses.begin(); it != clauses.end(); ++it) {
	// booleans to hold x1 or ^x1, x2 or ^x2 that appear in clause
	bool x1, x2;
	// set x1, x2, remembering that clauses index variables from 1, while bool array is indexed from 0
	if (it->first > 0) {
	    x1 = vars[it->first - 1];
	} else {
	    x1 = !vars[-1 * it->first - 1];
	}
	if (it->second > 0) {
	    x2 = vars[it->second - 1];
	} else {
	    x2 = !vars[-1 * it->second - 1];
	}
	// add clause to return vec if violation
	if (!(x1 || x2)) {
	    violations.push_back(*it);
	}
    }
    return violations;
}

void gen_rand(bool* vars, long number) {
    for (long i = 0; i < number; ++i) {
	vars[i] = std::rand() % 2;
    }
}

int main(int argc, char** argv) {

    long number;
    clausevec clauses;
    std::ifstream infile(argv[1]);
    std::string line;

    // read in number
    std::getline(infile, line);
    if (std::sscanf(line.c_str(), "%ld", &number) != 1) {
	throw "failed to read number!";
    }
    //std::cout << number << std::endl;

    // read in clauses
    for (long i = 0; i < number; ++i) {
	long x1, x2;
	std::getline(infile, line);
	if (std::sscanf(line.c_str(), "%ld %ld", &x1, &x2) != 2) {
	    throw "failed to read clause!";
	}
	clauses.push_back(std::pair<long, long>(x1, x2));
	//std::cout << x1 << " " << x2 << std::endl;
    }

    // initialize random number generator
    std::srand(42);
    std::cout << "RAND_MAX = " << RAND_MAX << std::endl;

    // allocate variable array
    bool* vars = new bool[number];

    // main loop
    for (long i = 0; i < (long) std::log2(number); ++i) {
	std::cout << "i = " << i << std::endl;
	// random initialization
	gen_rand(vars, number);
	// inner loop
	for (long j = 0; j < 2 * number * number; ++j) {
	    clausevec violations = get_violations(clauses, vars);
	    if (j % 1000 == 0 ) {
		std::cout << "j = " << j << std::endl;
		std::cout << violations.size() << " violations" << std::endl;
	    }
	    if (violations.size() == 0) {
		std::cout << "instance is satisfiable!" << std::endl;
		return 0;
	    }
	    long n;
	    // flip # violations / 10 variables
	    // if (violations.size() > 10) {
	    //     n = violations.size() / 10;
	    // } else {
	    //     n = 1;
	    // }
	    n = 1;
	    for (long k = 0; k < n; ++k) {
		std::pair<long, long> myclause = violations[std::rand() % violations.size()];
		long myvar;
		if (std::rand() % 2 == 0) {
		    myvar = std::abs(myclause.first) - 1;
		} else {
		    myvar = std::abs(myclause.second) - 1;
		}
		vars[myvar] = !vars[myvar];
	    }
	}
	std::cout << std::endl;
    }

    std::cout << "instance is (probably) unsatisfiable!" << std::endl;
    return 1;

}
