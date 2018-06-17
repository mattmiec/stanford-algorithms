// source file heap.cpp
#include "heap.h"
#include <iostream>

// add node, conditionally replacing node if already in heap
void heap::add_node(unsigned int nodeid, int score) {

  // if node exists, either delete it or return
  auto mapiter = heapmap.find(nodeid);
  if (mapiter != heapmap.end()) {
    if (score < heapvec[mapiter->second]->score) {
      delete_node(nodeid);
    } else {
      return;
    }
  }

  // construct new heapnode
  heapnode* newheapnode = new heapnode;
  newheapnode->nodeid = nodeid;
  newheapnode->score = score;

  // add to heap
  heapvec.push_back(newheapnode);
  unsigned int index = heapvec.size() - 1;
  heapmap[nodeid] = index;

  // restore heap property
  bubble_up(index);
}

// delete heapnode from heap given nodeid
void heap::delete_node(unsigned int nodeid) {

  // error if nodeid is not in heap
  auto mapiter = heapmap.find(nodeid);
  if (mapiter == heapmap.end()) {
    throw "Attempt to delete nodeid which is not in heapmap!";
  }

  // get node index and swap with last
  unsigned int index = mapiter->second;
  swap(index, heapvec.size() - 1);

  // delete heapnode
  heapmap.erase(nodeid);
  delete heapvec.back();
  heapvec.pop_back();

  // restore heap property (if deleted node was not last in heapvec)
  if (index != heapvec.size()) {
    bubble_up(index);
    bubble_down(index);
  }
}

// return heapnode with minscore
heapnode heap::extract_min() {

  // error if heap is empty
  if (heapvec.size() == 0) {
    throw "Attempt to extract min of empty heap!";
  }

  // heapnode to return
  heapnode rtn = *heapvec[0];

  // swap with last
  swap(0, heapvec.size() - 1);

  // delete heapnode
  heapmap.erase(heapvec.back()->nodeid);
  delete heapvec.back();
  heapvec.pop_back();

  // restore heap property
  bubble_down(0);

  // return heapnode
  return rtn;
}

// check whether heap is empty
bool heap::is_empty() {
  if (heapvec.size() == 0 and heapmap.size() == 0) {
    return true;
  }
  // additional check whether vec and map sizes are different
  if (heapvec.size() != heapmap.size()) {
    throw "Heap vector and map have different sizes!";
  }
  return false;
}

// print heap vector
void heap::print() {
  std::cout << "printing heap:" << std::endl;
  for (unsigned int i = 0; i != heapvec.size(); ++i) {
    std::cout << "heapvec index " << i << std::endl;
    std::cout << "nodeid = " << heapvec[i]->nodeid << std::endl;
    std::cout << "score = " << heapvec[i]->score << std::endl;
  }
}

// check heap property and map
void heap::check() {
  // loop over heap vector
  for (int i = 0; i < heapvec.size(); ++i) {
    // check children if they exist
    if  (((2 * i + 1 < heapvec.size()) && (heapvec[i]->score > heapvec[2 * i + 1]->score))
      || ((2 * i + 2 < heapvec.size()) && (heapvec[i]->score > heapvec[2 * i + 2]->score))) {
      print();
      std::cout << "heap violation at i = " << i << std::endl;
      throw "found heap violation!";
    }
  }
  // check heap map
  if (heapvec.size() != heapmap.size()) {
    print();
    throw "heapvec.size() != heapmap.size()";
  }
  for (auto it = heapmap.begin(); it != heapmap.end(); ++it) {
    if (it->first != heapvec[it->second]->nodeid) {
      print();
      throw "error in heapmap (type 1)!";
    }
  }
  for (int i = 0; i < heapvec.size(); ++i) {
    if (heapmap.find(heapvec[i]->nodeid) == heapmap.end()) {
      print();
      throw "error in heapmap (type 2)!";
    }
    if (heapmap[heapvec[i]->nodeid] != i) {
      print();
      throw "error in heapmap (type 3)!";
    }
  }
}

// bubble-up given heapvec index i
void heap::bubble_up(unsigned int i) {

  // return if root
  if (i == 0) {
    return;
  }
  if (i >= heapvec.size()) {
    throw "Attempt to bubble-up from out-of-range index!";
  }

  // index of parent
  unsigned int p;

  // swap with parent until heap property is satisfied
  while (((i != 0) && (heapvec[p = (i - 1) / 2]->score) > heapvec[i]->score)) {
    swap(i, p);
    i = p;
  }
}

// bubble-down given heapvec index i
void heap::bubble_down(unsigned int i) {

  // indices of children
  unsigned int c1, c2;

  // swap with min of children until heap property is satisfied or reached leaf
  while (true) {
    // return if leaf
    if (2 * i + 1 >= heapvec.size()) {
      return;
    }
    // set children
    c1 = 2 * i + 1;
    // check whether right child exists
    if (2 * i + 2 < heapvec.size()) {
      c2 = 2 * i + 2;
    } else {
      // use c1 as placeholder if no right child
      c2 = c1;
    }

    // c1 becomes min of c1 and c2
    if (heapvec[c2]->score < heapvec[c1]->score) {
      c1 = c2;
    }

    // return if heap property is satisfied
    if (heapvec[c1]->score >= heapvec[i]->score) {
      return;
    }

    // otherwise swap
    swap(i, c1);

    // set i to c1
    i = c1;
  }

  return;
}

// swap nodes with indices i1 and i2
void heap::swap(unsigned int i1, unsigned int i2) {
  heapnode* ptr;
  ptr = heapvec[i1];
  heapvec[i1] = heapvec[i2];
  heapvec[i2] = ptr;
  heapmap[heapvec[i1]->nodeid] = i1;
  heapmap[heapvec[i2]->nodeid] = i2;
}
