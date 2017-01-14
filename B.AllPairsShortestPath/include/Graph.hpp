//Copyright 2017 <Shunji Lin>

#ifndef GRAPH_HPP
#define GRAPH_HPP

#include <vector>

namespace graph {
	
    struct Edge {
	int target_id;
	int cost;
	bool operator<(const Edge & rhs) {
	    return cost < rhs.cost;
	}
    };
	
    struct Graph {
	Graph(int size) : adjlist(size) {};
	~Graph() = default;
	Graph(const Graph& rhs) = default;
	// Move constructor
	Graph(Graph&& rhs) {
	    adjlist.swap(rhs.adjlist);
	}
	// Move assignment
	Graph& operator=(Graph&& rhs) {
	    adjlist.swap(rhs.adjlist);
	    return *this;
	}

	void insertEdge(int u, int v, int cost) {
	    Edge edge1 = {v, cost}; 
	    adjlist[u].emplace_back(edge1);
	}

	int size() const {
	    return adjlist.size();
	}
	std::vector< std::vector<Edge> > adjlist;
    };
};

#endif
