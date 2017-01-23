#ifndef MAP_HPP
#define MAP_HPP

#include "Graph.hpp"
#include <vector>
#include <math.h>

using namespace graph;

namespace map {
    struct Coordinate {
	double x;
	double y;
	Coordinate(double x, double y) : x(x), y(y) {}
    };

    double euclideanDistance(Coordinate a, Coordinate b) {
	return sqrt(pow((a.x - b.x),2) + pow(a.y - b.y,2));
    }

    class Map {
	Graph graph;
    public:
	Map(const std::vector<Coordinate> & coordinates) : graph(coordinates.size()) {
	    auto size = coordinates.size();
	    for (std::size_t i = 0; i < size; ++i) {
		for (std::size_t j = i+1; j < size; ++j) {
		    graph.insertEdge(i, j,
				     euclideanDistance(coordinates[i],
						       coordinates[j]));
		}
	    }
	}

	
	double distance(int city1, int city2) const {
	    return graph.returnEdge(city1, city2);
	}

	std::size_t size() const {
	    return graph.size();
	}


    };
}


#endif
