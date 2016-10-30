//Copyright 2016 Shunji Lin

#include <fstream>
#include <sstream>
#include <iostream>
#include <string>
#include "TwoSum.hpp"
#include "steadyClockTimer.hpp"

const long UPPER_BOUND = 10000;
const long LOWER_BOUND = -10000;

using namespace twoSum;

int main(int argc, char *argv[])
{
    std::ifstream infile;
    infile.open("../2sum.txt");
    if (!infile) {
	std::cout << "Opening file failed." << std::endl;
	return -1;
    }

    std::vector<long> integers;

    std::string line;
    while (std::getline(infile, line)) {
	std::istringstream iss(line);
	long integer;
	iss >> integer;
	if (iss.fail()) {
	    std::cout << "Reading error or incorrect type." << std::endl;
	    return -1;
	}
	integers.emplace_back(integer);
    }

    SteadyClockTimer timer;
    timer.start();
    
    TwoSum twoSum(integers, UPPER_BOUND, LOWER_BOUND);
    auto count = twoSum.countTargetValues();
    std::cout << "Number of 2-sums is : " << count << std::endl;
    std::cout << "time taken is: " << timer.getMs() << " ms" << std::endl;
    
    return 0;
}
