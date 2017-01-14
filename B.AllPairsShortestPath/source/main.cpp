//Copyright 2017 <Shunji Lin>

#include "APSP.hpp"
#include <fstream>
#include <sstream>
#include <iostream>
#include <string>
#include "steadyClockTimer.hpp"

using namespace apsp;

int initializeGraphFromFile(Graph &graph, std::string filename) {
    std::ifstream infile;
    infile.open(filename);
    if (!infile) {
	std::cout << "Opening file failed." << std::endl;
	return -1;
    }
    std::string line;
    int n_vertices, n_edges;

    std::getline(infile, line);
    std::istringstream iss(line);
    iss >> n_vertices >> n_edges;
    if (iss.fail()) {
	std::cout << "Reading error or incorrect type." << std::endl;
	return -1;
    }
    graph = Graph(n_vertices);
    for (int i = 0; i < n_edges; ++i) {
	std::getline(infile, line);
	std::istringstream iss(line);
	int u, v, cost;
	iss >> u >> v >> cost;
	if (iss.fail()) {
	    std::cout << "Reading edge failed." << std::endl;
	    return -1;
	}
	graph.insertEdge(u-1, v-1, cost);
    }
    return 0;
}

int main(int argc, char *argv[])
{
    Graph graph1 = Graph(0);
    Graph graph2 = Graph(0);
    Graph graph3 = Graph(0);

    if (initializeGraphFromFile(graph1, "../g1.txt") == -1) return -1;
    if (initializeGraphFromFile(graph2, "../g2.txt") == -1) return -1;
    if (initializeGraphFromFile(graph3, "../g3.txt") == -1) return -1;

    SteadyClockTimer timer1, timer2, timer3;
    std::cout << "Note: value of 2147483647 indicates negative cycle" << std::endl;
    timer1.start();
    std::cout << "APSP of graph1 is : " << APSPCost(graph1) << std::endl;
    std::cout << "time taken for graph1 is : " << timer1.getMs() << " ms" << std::endl;
    timer2.start();
    std::cout << "APSP of graph2 is : " << APSPCost(graph2) << std::endl;
    std::cout << "time taken for graph2 is : " << timer2.getMs() << " ms" << std::endl;
    timer3.start();
    std::cout << "APSP of graph3 is : " << APSPCost(graph3) << std::endl;
    std::cout << "time taken for graph3 is : " << timer3.getMs() << " ms" << std::endl;
    return 0;
}

