//Copyright 2017 <Shunji Lin>

#include <fstream>
#include <sstream>
#include <iostream>
#include <string>
#include <cmath>
#include "steadyClockTimer.hpp"
#include "TSP_DP.hpp"

using namespace tspdp;

int main(int argc, char *argv[])
{
    std::ifstream infile;
    infile.open("../tsp.txt");
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
    TSPDP tspdp = TSPDP(Map(coordinates));
    std::cout << "Minimum cost tour has cost (rounded down to nearest integer): " << floor(tspdp.minTSPValue()) << std::endl;
    std::cout << "time taken is : " << timer.getMs() << " ms" << std::endl;
    return 0;
}
