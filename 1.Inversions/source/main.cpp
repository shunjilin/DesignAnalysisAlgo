//Copyright 2016 <Shunji Lin>

#include <iostream>
#include <vector>
#include "MergeSort.hpp"

int main(int argc, char *argv[]) {
  // Read from file into vector
  std::vector<int> testVector;
  int entry;
  while (std::cin >> entry) {
    testVector.emplace_back(entry);
  }
  MergeSort<int> mergesort;
  mergesort.mergeSort(testVector);
  std::cout << "Number of inversions is : " << mergesort.inversions << std::endl;
}
