// header file heap.h
#ifndef GUARD_heap_h
#define GUARD_heap_h

#include <vector>
#include <unordered_map>

// struct used by heap
struct heapnode {
  unsigned int nodeid;
  int score;
};

// class heap for graph node and scores
class heap {
 public:
  void add_node(unsigned int, int);
  void delete_node(unsigned int);
  heapnode extract_min();
  bool is_empty();
  void print();
  void check();
 private:
  // vector to store nodeid, score pair as heap array
  std::vector<heapnode*> heapvec;
  // mapping from nodeid to index in heap array
  std::unordered_map<unsigned int, unsigned int> heapmap;
  void bubble_up(unsigned int);
  void bubble_down(unsigned int);
  void swap(unsigned int, unsigned int);
};

#endif
