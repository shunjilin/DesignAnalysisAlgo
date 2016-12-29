//Copyright 2016 <Shunji Lin>

#include "KnapsackRecursive.hpp"
#include <fstream>
#include <sstream>
#include <iostream>
#include <vector>
#include "steadyClockTimer.hpp"

using namespace knapsack;

int main(int argc, char *argv[])
{
    std::ifstream infile;
    infile.open("../knapsack_big.txt");
    if (!infile) {
	std::cout << "Opening file failed." << std::endl;
	return -1;
    }
    std::string line;
    int n_items;
    int max_weight;

    std::getline(infile, line);
    std::istringstream iss(line);
    iss >> max_weight >> n_items;
        if (iss.fail()) {
	std::cout << "Reading error or incorrect type." << std::endl;
	return -1;
    }
    
    std::vector<Item> items;

    for (int i = 0; i < n_items; ++i) {
	std::string line;
	std::getline(infile, line);
	std::istringstream iss(line);
	int value, weight;
	iss >> value >> weight;
	if (iss.fail()) {
	    std::cout << "Reading error or incorrect type." << std::endl;
	    return -1;
	}
	items.emplace_back(Item(value, weight));
    }
    
    SteadyClockTimer timer;
    timer.start();
    KnapsackRecursive knapsack(items, max_weight);


    std::cout << "optimal solution is " << knapsack.optimalSolution() << std::endl;
    std::cout << "time taken is: " << timer.getMs() << " ms" << std::endl;
    return 0;
}
