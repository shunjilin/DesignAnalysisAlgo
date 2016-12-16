//Copyright 2016 <Shunji Lin>

#ifndef CLUSTERING_HPP
#define CLUSTERING_HPP

#include <set>
#include "UnionFind.hpp"
#include "BitFunctions.hpp"

using namespace unionfind;
using namespace bitfunctions;

namespace clusteringimplicit {
    
    class Clustering {	
	std::set<int> node_set;
	UnionFind union_find;
	int n_bits;

	bool sameCluster(int u, int v) {
	    return union_find.find(u) == union_find.find(v);
	}
    public:
	Clustering() {}
	Clustering(const std::vector<int>& node_vec, int n_bits) :
	    node_set(node_vec.begin(), node_vec.end()),
	    union_find(node_vec),
	    n_bits(n_bits) {}

	std::size_t nClusters() const {
	    return union_find.nGroups();
	}
	
	void merge(int u, int v) {
	    union_find.merge(u, v);
	}

	void mergeNodeAndNodeVec(int node, const std::vector<int>& nodeVec) {
	    for (auto otherNode : nodeVec) {
		if (node_set.find(otherNode) != node_set.end()) {
		    union_find.merge(node, otherNode);
		}
	    }
	}

	void mergeAllClustersWithDistOneAndTwo() {
	    for (auto node: node_set) {
		mergeNodeAndNodeVec(node, distOneGreaterPermutations(node, n_bits));
	    }
	    for (auto node: node_set) {
		mergeNodeAndNodeVec(node, distTwoGreaterPermutations(node, n_bits));
	    }
	}        
    };

};

#endif
