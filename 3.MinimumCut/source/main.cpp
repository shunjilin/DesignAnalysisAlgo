//Copyright 2016 <Shunji Lin>

#include "adjacencyList.hpp"
#include <fstream>
#include <string>
#include <sstream>
#include <stdlib.h>
#include <chrono>
#include <iostream>
#include "adjacencyList.hpp"
#include "steadyClockTimer.hpp"

const int N_NODES = 200;
const int ITERATIONS = 1000;

int main(int argc, char *argv[])
{
    int minCutEdges = N_NODES;

    AdjacencyList adjList(N_NODES);

    std::ifstream infile;
    infile.open("../kargerMinCut.txt");
    if (!infile) {
	std::cout << "Opening file failed." << std::endl;
	return -1;
    }
    
    std::string line;
    while (std::getline(infile, line)) {
	std::istringstream iss(line);
        int u, v;
	iss >> u;
	while (iss >> v) {
	    if (iss.fail()) { 
		std::cout << "Reading error or incorrect type." << std::endl;
		return -1;
	    }
	    if (u < 1 || u > N_NODES || v < 1 || v > N_NODES) {
		std::cout << "Vertex ID out of range" << std::endl;
		return -1;
	    }
	    adjList.insertEdge(u-1, v-1);
	}
    }
    
    SteadyClockTimer timer;

    timer.start();
    for (int i = 0; i < ITERATIONS; ++i) {
	srand(i);
	AdjacencyList adjListCopy = adjList;

	while (adjListCopy.nodeCount() > 2) {
	    adjListCopy.contractRandomEdge();
	}

	if (adjListCopy.edgeCount() < minCutEdges) {
	    minCutEdges = adjListCopy.edgeCount();
	}
    }

    std::cout << "After " << ITERATIONS << " iterations," << std::endl;
    
    std::cout << "Possible min cut edge count is: " <<  minCutEdges << std::endl;

    std::cout << "time taken is: " << timer.getMs() << " ms" << std::endl;
    return 0;
}
