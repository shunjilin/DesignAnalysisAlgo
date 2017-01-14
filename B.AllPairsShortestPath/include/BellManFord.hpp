//Copyright 2017 <Shunji Lin>

#ifndef BELLMANFORD_HPP
#define BELLMANFORD_HPP

#include <vector>
#include <limits>
#include <algorithm>
#include <iostream>
#include "Graph.hpp"

const int INFTY = std::numeric_limits<int>::max();
using namespace graph;

namespace bellmanford {

    class BellManFord {
	Graph rev_graph;
	std::vector<std::vector<int> > paths_dp;
	bool solved;
	bool negative_cycle;
	int final_iteration;
	int source_id;
    public:
	BellManFord(Graph graph) : rev_graph(graph.size()),
				   paths_dp(graph.size(),
					   std::vector<int>
					    (graph.size(),
					     INFTY)),
				   solved(false),
				   negative_cycle(false),
				   final_iteration(graph.size()-1){
	    for (int u = 0, size = graph.size(); u < size; ++u) {
		for (auto & edge : graph.adjlist[u]) {
		    rev_graph.insertEdge(edge.target_id, u, edge.cost);
		}
	    }
	}
	
	void fillShortestPathsFrom(int source) {
	    source_id = source; 
	    paths_dp[0][source] = 0;
	    bool no_change = true;
	    for (int subprobsize = 1, size = rev_graph.size();
		 subprobsize <= size; ++subprobsize) {
		for (int node = 0, size = rev_graph.size(); node < size; ++node) {
		    auto min_neighbor_edge = std::min_element(rev_graph.adjlist[node].begin(),
							      rev_graph.adjlist[node].end());
		    int case1 = paths_dp[subprobsize-1][node];
		    if (min_neighbor_edge != rev_graph.adjlist[node].end()) {
			
			int case2 = optimalSubproblem2(subprobsize, node);
			if (subprobsize == size) { // negative cycle check
			    if (case2 < case1) negative_cycle = true;
			} else {
			    if (case2 < case1) {
				no_change = false;
				paths_dp[subprobsize][node] = case2;
			    } else {
				paths_dp[subprobsize][node] = case1;
			    }
			}
		    }
		}
		if (no_change) {
		    final_iteration = subprobsize;
		    break; // early termination
		}
		no_change = true;
	    }
	    solved = true;
	}

	int optimalSubproblem2(int subproblemsize, int node) {
	    int min_subproblem_cost = INFTY;
	    for (auto & edge : rev_graph.adjlist[node]) {
		int subpath_cost = paths_dp[subproblemsize-1][edge.target_id];
		if (subpath_cost == INFTY) continue;
		int subproblem_cost = subpath_cost + edge.cost;
		if (subproblem_cost < min_subproblem_cost)
		    min_subproblem_cost = subproblem_cost; 
	    }
	    return min_subproblem_cost;
	}

	bool isSolved() const {
	    return solved;
	}

	bool hasNegativeCycle() const {
	    return negative_cycle;
	}
	int getShortestPathTo(int node) const  {
	    return paths_dp[final_iteration-1][node];
	}					  
    };
};

#endif
