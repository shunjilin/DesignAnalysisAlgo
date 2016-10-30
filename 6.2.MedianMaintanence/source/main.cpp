//Copyright 2016 Shunji Lin

#include <fstream>
#include <sstream>
#include <iostream>
#include <string>
#include "MedianMaintanence.hpp"
#include "steadyClockTimer.hpp"


int main(int argc, char *argv[])
{
    std::ifstream infile;
    infile.open("../Median.txt");
    if (!infile) {
	std::cout << "Opening file failed." << std::endl;
	return -1;
    }

    std::vector<int> integers;

    std::string line;
    while (std::getline(infile, line)) {
	std::istringstream iss(line);
	int integer;
	iss >> integer;
	if (iss.fail()) {
	    std::cout << "Reading error or incorrect type." << std::endl;
	    return -1;
	}
	integers.emplace_back(integer);
    }

    SteadyClockTimer timer;
    timer.start();
    
    MedianMaintanence MM(integers);
    auto sum = MM.getSumOfMedians();
    std::cout << "Sum of Medians is : " << sum << std::endl;
    std::cout << "time taken is: " << timer.getMs() << " ms" << std::endl;
    
    return 0;
}
