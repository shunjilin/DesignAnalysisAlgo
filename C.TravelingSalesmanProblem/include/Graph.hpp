//Copyright 2017 <Shunji Lin>

#ifndef GRAPH_HPP
#define GRAPH_HPP

#include <vector>


namespace graph {
    
    struct Graph {
	Graph(int size) :
	    adjmatrix(size,
		      std::vector<double>(size, 0)) {};
	~Graph() = default;
	Graph(const Graph& rhs) = default;
	// Move constructor
	Graph(Graph&& rhs) {
	    adjmatrix.swap(rhs.adjmatrix);
	}
	// Move assignment
	Graph& operator=(Graph&& rhs) {
	    adjmatrix.swap(rhs.adjmatrix);
	    return *this;
	}

	void insertEdge(int u, int v, double cost) {
	    adjmatrix[u][v] = cost;
	    adjmatrix[v][u] = cost;
	}

	double returnEdge(int u, int v) const {
	    return adjmatrix[u][v];
	}

	std::size_t size() const {
	    return adjmatrix.size();
	}
	std::vector< std::vector<double> > adjmatrix;
    };
};

#endif
