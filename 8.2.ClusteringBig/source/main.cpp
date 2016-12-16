//Copyright 2016 <Shunji Lin>

#include "Clustering.hpp"
#include <fstream>
#include <sstream>
#include <iostream>
#include "steadyClockTimer.hpp"

using namespace clusteringimplicit;

int main(int argc, char *argv[])
{
    std::ifstream infile;
    infile.open("../clustering_big.txt");
    if (!infile) {
	std::cout << "Opening file failed." << std::endl;
	return -1;
    }

    std::string line;
    std::size_t n_vertices;
    int n_bits;

    std::getline(infile, line);
    std::istringstream iss(line);
    iss >> n_vertices >> n_bits;
    if (iss.fail()) {
	std::cout << "Reading error or incorrect type." << std::endl;
	return -1;
    }
	
    std::vector<int> nodes;
    
    while(std::getline(infile, line)) {
	std::istringstream iss(line);
	int node = 0;
	int cur_bit;
	for (int i = 0; i < n_bits; ++i) {
	    node <<= 1;
	    iss >> cur_bit;
	    if (iss.fail()) {
		std::cout << "Reading error or incorrect type." << std::endl;
		return -1;
	    }
	    node += cur_bit;
	    
	}      
	nodes.emplace_back(node);
    }
    assert(nodes.size() == n_vertices);

    Clustering clustering(nodes, n_bits);

    SteadyClockTimer timer;
    timer.start();
    clustering.mergeAllClustersWithDistOneAndTwo();
    
    std::cout << "Number of clusters such that spacing is at least 3 is : " << clustering.nClusters() << std::endl;
    std::cout << "time taken is: " << timer.getMs() << " ms" << std::endl;
    return 0;
}

