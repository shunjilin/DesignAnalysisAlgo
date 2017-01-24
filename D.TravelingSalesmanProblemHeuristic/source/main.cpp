//Copyright 2017 <Shunji Lin>

#include <fstream>
#include <sstream>
#include <iostream>
#include <iomanip>
#include <string>
#include <cmath>
#include "steadyClockTimer.hpp"
#include "TSP_Heuristic.hpp"

using namespace tspheuristic;

int main(int argc, char *argv[])
{
    std::ifstream infile;
    infile.open("../nn.txt");
    if (!infile) {
	std::cout << "Opening file failed." << std::endl;
	return -1;
    }
    std::string line;
    int n_cities;
    std::getline(infile, line);
    std::istringstream iss(line);
    iss >> n_cities;
    if (iss.fail()) {
	std::cout << "Reading error or incorrect type." << std::endl;
	return -1;
    }
    std::vector<Coordinate> coordinates;
    for (int i = 0; i < n_cities; ++i) {
	std::getline(infile, line);
	std::istringstream iss(line);
	iss.ignore(5, ' '); // ignore index
	double x, y;
	iss >> x >> y;
	if (iss.fail()) {
	    std::cout << "Reading coordinates failed." << std::endl;
	    return -1;
	}
	coordinates.emplace_back(Coordinate(x,y));
    }
    SteadyClockTimer timer;
    timer.start();
    TSPHeuristic tsp = TSPHeuristic(Map(coordinates));
    std::cout << "Tour using nearest neighbor heuristic has cost (rounded down to nearest integer): " << std::setprecision(10) << floor(tsp.TSPValue()) << std::endl;
    std::cout << "time taken is : " << timer.getMs() << " ms" << std::endl;
    return 0;
}
