//Copyright 2016 <Shunji Lin>

#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include "QuickSort.hpp"

using namespace QuickSort;

int main(int argc, char *argv[]) {
    // Read from file into vector
    std::vector<int> testVector1;

    std::ifstream infile;
    infile.open("../QuickSort.txt");
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
	testVector1.emplace_back(entry);
    }

    std::vector<int> testVector2(testVector1);
    std::vector<int> testVector3(testVector2);

    unsigned comparisons1 = 0;
    unsigned comparisons2 = 0;
    unsigned comparisons3 = 0;

    firstPivotIndex_f firstPivotIndex_o;
    lastPivotIndex_f lastPivotIndex_o;
    medianOfThreePivotIndex_f medianOfThreePivotIndex_o;

    quickSort(testVector1, firstPivotIndex_o, comparisons1);
    quickSort(testVector2, lastPivotIndex_o, comparisons2);
    quickSort(testVector3, medianOfThreePivotIndex_o, comparisons3);

  
    std::cout << "Number of comparisons is [first pivot] : " << comparisons1  << std::endl;
    std::cout << "Number of comparisons is [last pivot] : " << comparisons2  << std::endl;
    std::cout << "Number of comparisons is [median of three pivot] : " << comparisons3  << std::endl;
}
