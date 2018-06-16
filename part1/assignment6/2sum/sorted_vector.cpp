// implement and execut 2-SUM algorithm using sorted std::vector
#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <set>
#include <ctime>

int main() {

  std::vector<long long> myvector;
  std::set<int> target;
  std::ifstream myfile("algo1-programming_prob-2sum.txt");
  std::clock_t cpu_t0, cpu_t1;

  long long i;

  while(myfile >> i) {
    myvector.push_back(i);
  }

  myfile.close();

  std::sort(myvector.begin(), myvector.end());

  std::cout << "size = " << myvector.size() << std::endl;

  cpu_t0 = std::clock();

  for (auto it1 = myvector.begin(); it1 != myvector.end(); ++it1) {
    for (auto it2 = std::lower_bound(myvector.begin(), myvector.end(), -10000 - *it1); it2 != std::upper_bound(myvector.begin(), myvector.end(), 10000 - *it1); ++it2) {
      if (*it1 != *it2) {
        target.insert(*it1 + *it2);
      }
    }
  }

  cpu_t1 = std::clock();

  std::cout << "CPU time for main loop: " << 1000.0 * (cpu_t1 - cpu_t0) / CLOCKS_PER_SEC << std::endl;


  std::cout << "count = " << target.size() << std::endl;
}
