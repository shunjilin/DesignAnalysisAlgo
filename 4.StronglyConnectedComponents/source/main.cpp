#include "SCC.hpp"
#include <fstream>
#include <sstream>
#include <iostream>
#include <string>
#include "steadyClockTimer.hpp"

using namespace scc;
const int N_NODES = 875714;
const int TOP = 5;
//const int N_NODES = 12;
//using namespace scc;

int main(int argc, char *argv[]) {
    Graph graph(N_NODES);
    std::ifstream infile;
    infile.open("../SCC.txt");
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
	    graph.insertEdge(u-1, v-1);
	}
    }

    SteadyClockTimer timer;
    timer.start();
    SCC scc(std::move(graph));
    scc.DFS_firstPass();
    scc.DFS_secondPass();
    
    std::vector<int> group_sizes = scc.getGroupSizes();


    std::cout << "Biggest group sizes: " << std::endl;

    for (auto begin = group_sizes.rbegin(),
	     end = group_sizes.rend(),
	     top = begin + TOP,
	     rit = begin;
	 rit != top && rit != end; ++rit) {
	std::cout << *rit << std::endl;
    }
    
    std::cout << "time taken is: " << timer.getMs() << " ms" << std::endl;
    
}
