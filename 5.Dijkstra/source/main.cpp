//Copyright 2016 <Shunji Lin>

#include "Dijkstra.hpp"
#include <fstream>
#include <sstream>
#include <iostream>
#include "steadyClockTimer.hpp"

using namespace dijkstra;
const int N_NODES = 200;

int main(int argc, char *argv[])
{
    Graph graph(200);
    std::ifstream infile;
    infile.open("../dijkstraData.txt");
    if (!infile) {
	std::cout << "Opening file failed." << std::endl;
	return -1;
    }

    std::string line;
    while (std::getline(infile, line)) {
	std::istringstream iss(line);
	int u, v, dist; {
	    iss >> u;
	    while (iss >> v) {
		if (iss.fail()) {
		    std::cout << "Reading vertex v failed." << std::endl;
		    return -1;
		}
		iss.ignore(); // ignore comma
		iss >> dist;
		if (iss.fail()) {
		    std::cout << "Reading distance failed." << std::endl;
		return -1;
		}
		if (u < 1 || u > N_NODES || v < 1 || v > N_NODES) {
		    std::cout << "Vertex ID out of range" << std::endl;
		    return -1;
		}
		graph.insertEdge(u - 1, v - 1, dist);
	    }
	}
    }
    SteadyClockTimer timer;
    timer.start();
    Dijkstra dijkstra(std::move(graph));
    dijkstra.getShortestPathsFrom(0);

    std::vector<int>
	vertices_of_interest{7, 37, 59, 82, 99, 115, 133, 165, 188, 197};

    std::cout << "Vertex : Distance" << std::endl;

    for (auto vertex : vertices_of_interest) {
	std::cout << vertex << " : " << dijkstra.min_costs[vertex - 1] << std::endl;
    }

    std::cout << "time taken is: " << timer.getMs() << " ms" << std::endl;
        
    return 0;
}
