//Copyright 2016 <Shunji Lin>

#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include "MergeSort.hpp"

using namespace MergeSort;

int main(int argc, char *argv[]) {
    // Read from file into vector
    std::vector<int> testVector;

    std::ifstream infile;
    infile.open("../IntegerArray.txt");
    if (!infile) {
	std::cout << "Opening file failed." << std::endl;
	return -1;
    }

    std::string line;
    while (std::getline(infile, line)) {
	std::istringstream iss(line);
	int entry;
	iss >> entry;
	if (iss.fail()) {
	    std::cout << "Reading error or incorrect type." << std::endl;
	    return -1;
	}
	testVector.emplace_back(entry);
    }
    
    unsigned inversions = 0;
    mergeSort(testVector, inversions);
    std::cout << "Number of inversions is : " << inversions << std::endl;
}
