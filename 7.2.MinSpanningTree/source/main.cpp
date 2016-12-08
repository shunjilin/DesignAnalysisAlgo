//Copyright 2016 <Shunji Lin>

#include "MinSpanningTree.hpp"
#include <fstream>
#include <sstream>
#include <iostream>
#include "steadyClockTimer.hpp"

using namespace minSpanningTree;

int main(int argc, char *argv[])
{
    std::ifstream infile;
    infile.open("../edges.txt");
    if (!infile) {
	std::cout << "Opening file failed." << std::endl;
	return -1;
    }

    std::string line;
    int n_vertices;
    int n_edges;

    std::getline(infile, line);
    std::istringstream iss(line);
    iss >> n_vertices >> n_edges;
    if (iss.fail()) {
	std::cout << "Reading error or incorrect type." << std::endl;
	return -1;
    }
    Graph graph(n_vertices);

    for (int i = 0; i < n_edges; ++i) {
	std::getline(infile, line);
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
	graph.insertEdge(node1 - 1, node2 - 1, cost);
    }
    
    SteadyClockTimer timer;
    timer.start();
    std::cout << "Minimum spanning tree sum of costs is : "
	      << returnMinSpanningTreeSum(graph) << std::endl;
    std::cout << "time taken is: " << timer.getMs() << " ms" << std::endl;
    return 0;
}

