//Copyright 2016 <Shunji Lin>

#include "MWIS_DP.hpp"
#include <fstream>
#include <sstream>
#include <iostream>
#include <vector>
#include "steadyClockTimer.hpp"

using namespace mwisdp;

int main(int argc, char *argv[])
{
    std::ifstream infile;
    infile.open("../mwis.txt");
    if (!infile) {
	std::cout << "Opening file failed." << std::endl;
	return -1;
    }
    std::string line;
    int n_vertices;
    
    std::getline(infile, line);
    std::istringstream iss(line);
    iss >> n_vertices;
    if (iss.fail()) {
	std::cout << "Reading error or incorrect type." << std::endl;
	return -1;
    }

    std::vector<int> vertices;

    for (int i = 0; i < n_vertices; ++i) {
	std::istringstream iss(line);
	int weight;
	iss >> weight;
	vertices.emplace_back(weight);
    }
    
    SteadyClockTimer timer;
    timer.start();
    MWISDP mwisdp(vertices);
    mwisdp.constructMaxWeightIndependentSet();
    std::vector<int> verticesToCheck{{1, 2, 3, 4, 17, 117, 517, 997}};
    for (auto vertice : verticesToCheck) {
	std::cout << mwisdp.verticeInSet(vertice - 1);
    }
    std:: cout << "\n";
    std::cout << "time taken is: " << timer.getMs() << " ms" << std::endl;
    return 0;
}
