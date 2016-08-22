//Copyright 2016 <Shunji Lin>

#include <iostream>
#include <vector>
#include "MergeSort.hpp"

using namespace MergeSort;

int main(int argc, char *argv[]) {
    // Read from file into vector
    std::vector<int> testVector;
    int entry;
    while (std::cin >> entry) {
	testVector.emplace_back(entry);
    }
    unsigned inversions = 0;
    mergeSort(testVector, inversions);
    std::cout << "Number of inversions is : " << inversions << std::endl;
}
