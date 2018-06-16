// implement and execut 2-SUM algorithm using std::set (binary search tree)
#include <iostream>
#include <fstream>
#include <set>
#include <ctime>

int main() {

  std::set<long long> myset;
  std::set<int> target;
  std::ifstream myfile("algo1-programming_prob-2sum.txt");
  std::clock_t cpu_t0, cpu_t1;

  long long i;

  while(myfile >> i) {
    myset.insert(i);
  }

  myfile.close();

  std::cout << "size = " << myset.size() << std::endl;

  cpu_t0 = std::clock();

  for (auto it1 = myset.begin(); it1 != myset.end(); ++it1) {
    for (auto it2 = myset.lower_bound(-10000 - *it1); it2 != myset.upper_bound(10000 - *it1); ++it2) {
      if (*it1 != *it2) {
        target.insert(*it1 + *it2);
      }
    }
  }

  cpu_t1 = std::clock();

  std::cout << "CPU time for main loop: " << 1000.0 * (cpu_t1 - cpu_t0) / CLOCKS_PER_SEC << std::endl;


  std::cout << "count = " << target.size() << std::endl;
}
