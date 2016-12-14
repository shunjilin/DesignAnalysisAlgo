//Copyright 2016 <Shunji Lin>

#include "Clustering.hpp"
#include <fstream>
#include <sstream>
#include <iostream>
#include "steadyClockTimer.hpp"

using namespace clustering;

const int K = 4;

int main(int argc, char *argv[])
{
    std::ifstream infile;
    infile.open("../clustering1.txt");
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

    std::vector<Edge> edges;
    
    while(std::getline(infile, line)) {
	std::istringstream iss(line);
	int node1, node2, cost;
	iss >> node1 >> node2 >> cost;
	if (iss.fail()) {
	    std::cout << "Reading error or incorrect type." << std::endl;
	    return -1;
	}
	if (node1 < 1 || node2 > n_vertices || node2 < 1 || node2 > n_vertices) {
	    std::cout << "Vertex ID out of range" << std::endl;
	    return -1;
	}
	edges.emplace_back(Edge(node1 - 1, node2 - 1, cost));
    }
    
    Clustering clustering(n_vertices, edges);

    SteadyClockTimer timer;
    timer.start();
    clustering.kCluster(K);
    
    std::cout << "Maximum spacing of " << K << " clustering is : " << clustering.minClusterDistance() << std::endl;
    std::cout << "time taken is: " << timer.getMs() << " ms" << std::endl;
    return 0;
}

