// implement and execute median maintenance algorithm with C++ standard library's heap functions
#include <iostream>
#include <vector>
#include <algorithm>
#include <fstream>
#include <cstdlib>

void rebalance(std::vector<int>&, std::vector<int>&);
bool greater_than(int, int);

int main(int argc, char **argv) {
  // call with arguments [modulus] [filename]

  if (argc != 3) {
    throw "call with arguments [modulus] [filename]";
  }

  int i, mod = std::atoi(argv[1]), sum = 0;
  std::vector<int> hlow, hhigh;
  std::ifstream myfile(argv[2]);

  while (myfile >> i) {
    // add i to appropriate heap
    if (hlow.size() == 0 || i <= hlow[0]) { // safe to check hlow[0] due to short circuiting
      hlow.push_back(i);
      std::push_heap(hlow.begin(), hlow.end());
    } else {
      hhigh.push_back(i);
      std::push_heap(hhigh.begin(), hhigh.end(), greater_than);
    }

    // rebalance heaps so that hlow as the same number of elements as or one more element than high
    rebalance(hlow, hhigh);

    // median as defined in pset is just hlow[0]
    sum = (sum + hlow[0]) % 10000;
  }

  std::cout << "sum mod " << mod << " = " << sum << std::endl;
}

void rebalance(std::vector<int>& hlow, std::vector<int>& hhigh) {
  // rebalance heaps so that hlow.size() = hhigh.size() or hhigh.size() + 1
  // assume hlow.size() >= hhigh.size() - 1 and hlow.size() <= hhigh.size() + 2
  if (hlow.size() == hhigh.size() - 1) {
    std::pop_heap(hhigh.begin(), hhigh.end(), greater_than);
    hlow.push_back(*(hhigh.end() - 1));
    std::push_heap(hlow.begin(), hlow.end());
    hhigh.pop_back();
  } else if (hlow.size() == hhigh.size() + 2) {
    std::pop_heap(hlow.begin(), hlow.end());
    hhigh.push_back(*(hlow.end() - 1));
    std::push_heap(hhigh.begin(), hhigh.end(), greater_than);
    hlow.pop_back();
  }
}

bool greater_than(int i1, int i2) {
  // wrapper for > operator for passing to push_heap and pop_heap
  if (i1 > i2) {
    return true;
  } else {
    return false;
  }
}
