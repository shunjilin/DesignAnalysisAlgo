#ifndef TSPDP_HPP
#define TSPDP_HPP

#include "Map.hpp"
#include <math.h>
#include <set>
#include <algorithm>
#include <limits>
#include <cassert>

using namespace map;

namespace tspheuristic {

    class TSPHeuristic {
	Map map;
	std::set<int> unvisited;
	int current_vertice;
	double distance;
	bool solved;
	
    public:
	TSPHeuristic(Map map) : map(map), current_vertice(0), distance(0), solved(false) {
	    for (int i = 1, size = map.size(); i < size; ++i) {
		unvisited.insert(unvisited.end(),i);
	    }
	}

	void visit_step() {
	    double min_squared_dist = std::numeric_limits<double>::max();
	    int min_vertice = -1;
	    for (auto vertice : unvisited) {
		auto squaredDist = map.distanceSquared(current_vertice, vertice);
		if (squaredDist < min_squared_dist) {
		    min_squared_dist = squaredDist;
		    min_vertice = vertice;
		}
	    }
	    distance += sqrt(min_squared_dist);
	    unvisited.erase(min_vertice);
	    current_vertice = min_vertice;
	}


	void solve() {
	    while (unvisited.size() != 0) {
		visit_step();
	    }
	    distance += sqrt(map.distanceSquared(current_vertice, 0)); //last hop
	    solved = true;
	}

	double TSPValue() {
	    if (!solved) solve();
	    return distance;
	}

    };
};

#endif
