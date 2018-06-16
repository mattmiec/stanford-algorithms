// implement and execut 2-SUM algorithm using std::unordered_set (hash table)
#include <iostream>
#include <fstream>
#include <set>
#include <unordered_set>
#include <ctime>

int main() {

  std::unordered_set<long long> myset;
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


  for (auto it = myset.begin(); it != myset.end(); ++it) {
    for (int t = -10000; t <= 10000; ++t) {
      if (myset.count(t - *it) != 0 && *it != t - *it && target.count(t) == 0) {
        target.insert(t);
        std::cout << "found match for t = " <<  t << std::endl;
      }
    }
  }

  cpu_t1 = std::clock();

  std::cout << "CPU time for main loop: " << 1000.0 * (cpu_t1 - cpu_t0) / CLOCKS_PER_SEC << std::endl;


  std::cout << "count = " << target.size() << std::endl;
}
