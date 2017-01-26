//Copyright 2017 <Shunji Lin>

#include "2SAT.hpp"
#include <fstream>
#include <sstream>
#include <iostream>
#include <string>
#include <vector>
#include "steadyClockTimer.hpp"

using namespace twosat;

int readTwoSatFromFile(TwoSat &twosat, std::string filename) {
    std::ifstream infile;
    infile.open(filename);
    if (!infile) {
	std::cout << "Opening file failed." << std::endl;
	return -1;
    }
    int n_variables;
    std::string line;
    std::getline(infile, line);
    std::istringstream iss(line);
    iss >> n_variables;
    if (iss.fail()) {
	std::cout << "Reading n_variables failed." << std::endl;
	return -1;
    }
    std::vector<Clause> clauses;
    // assumption: n_clauses == n_variables
    for (int i = 0; i < n_variables; ++i) {
	std::getline(infile, line);
	std::istringstream iss(line);
	int u, v;
	iss >> u >> v;
	if (iss.fail()) {
	    std::cout << "Reading clause failed." << std::endl;
	    return -1;
	}
	clauses.emplace_back(Clause(u,v));
    }
    twosat = TwoSat(n_variables, clauses);
    return 0;
}

int main(int argc, char *argv[]) {
    std::vector<std::string> filenames = {"../2sat1.txt", "../2sat2.txt",
				     "../2sat3.txt", "../2sat4.txt",
				     "../2sat5.txt", "../2sat6.txt"};
    for (auto filename : filenames) {
	TwoSat instance;
        readTwoSatFromFile(instance, filename);
	SteadyClockTimer timer;
	timer.start();
	std::cout << filename << " is ";
	if (instance.isSatisfiable()) {
	    std::cout << "satisfiable." << std::endl;
	} else {
	    std::cout << "unsatisfiable." << std::endl;
	}
	std::cout << "time taken for " << filename <<
	    " is: " << timer.getMs() << " ms\n" << std::endl;
    }
}
