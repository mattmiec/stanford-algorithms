// header file timing.h
#ifndef GUARD_timing_h
#define GUARD_timing_h

#include <ctime>
#include <chrono>
#include <iostream>

// timing globals declaration
extern std::clock_t cpu_t0, cpu_t1;
extern std::chrono::high_resolution_clock::time_point wall_t0, wall_t1;

// assume cpu_t0, cpu_t1, wall_t0, wall_t1 are already set
inline void timing() {
  cpu_t1 = std::clock();
  wall_t1 = std::chrono::high_resolution_clock::now();
  std::cout << "CPU: " << 1000.0 * (cpu_t1 - cpu_t0) / CLOCKS_PER_SEC << std::endl;
  std::cout << "Wall: " <<  std::chrono::duration_cast<std::chrono::milliseconds>(wall_t1 - wall_t0).count() << std::endl;
  cpu_t0 = cpu_t1;
  wall_t0 = wall_t1;
}

#endif
