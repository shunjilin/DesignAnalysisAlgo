//Copyright 2016 <Shunji Lin>

#ifndef CLUSTERING_HPP
#define CLUSTERING_HPP

#include <cstddef>
#include <set>
#include <cassert>
#include "MinHeap.hpp"
#include "UnionFind.hpp"

using namespace unionfind;
using namespace minheap;

namespace clustering {
    struct Edge {
	Edge(std::size_t u, std::size_t v, int cost) : u(u), v(v), cost(cost) {}
	std::size_t u;
	std::size_t v;
	int cost;
	bool operator<(const Edge& rhs) const {
	    return cost < rhs.cost;
	}
    };

    class Clustering {	
	MinHeap<Edge> edgeList;
	UnionFind union_find;

    public:
	Clustering() {}
	Clustering(std::size_t size, std::vector<Edge>& edges) : edgeList(edges),
								 union_find(size) {}

	std::size_t nClusters() const {
	    return union_find.nGroups();
	}

	Edge minClusterDistanceEdge() {
	    auto edge = edgeList.min();
	    while (union_find.find(edge.u) == union_find.find(edge.v)) {
		edgeList.popMin();
		edge = edgeList.min();
	    }
	    return edge;
	}

	int minClusterDistance() {
	    auto edge = minClusterDistanceEdge();
	    return edge.cost;
	}

	void merge(std::size_t u, std::size_t v) {
	    union_find.merge(u, v);
	}

	void kCluster(std::size_t k) {
	    assert(k <= nClusters());
	    while (nClusters() > k) {
		auto min_dist_edge = minClusterDistanceEdge();
		merge(min_dist_edge.u, min_dist_edge.v);
	    }
	}
    };
};

#endif
