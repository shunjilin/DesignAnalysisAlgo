//Copyright 2016 <Shunji Lin>

#ifndef DIJKSTRA_HPP
#define DIJSTRA_HPP

#include <vector>
#include "MinHeap.hpp"
#include "Graph.hpp"
#include <limits>

using namespace minheap;
using namespace graph;

namespace dijkstra {
    struct Node {
	int id;
	int total_dist;
	bool operator<(const Node & rhs) {
	    return total_dist < rhs.total_dist;
	}
    };

    class Dijkstra {
	Graph graph;
	MinHeap<Node> frontier;
	int shortest_path_count;
    public:
	Dijkstra(Graph g) :  graph(g),
			     shortest_path_count(0),
			    min_costs(g.size(), std::numeric_limits<int>::max()){}
	
	void getShortestPathsFrom(int node_id) {
	    min_costs[node_id] = 0;
	    ++shortest_path_count;
	    for (auto& edge : graph.adjlist[node_id]) {
	        Node node = {edge.target_id, edge.cost};
		frontier.insert(node);
	    }
      
	    while (!frontier.isEmpty() && shortest_path_count < graph.size()) {
		Node target_node = frontier.extractMin();
		if (target_node.total_dist < min_costs[target_node.id]) {
		    min_costs[target_node.id] = target_node.total_dist;
		    ++shortest_path_count;
		    for (auto& edge : graph.adjlist[target_node.id]) {
			Node node = {edge.target_id, target_node.total_dist + edge.cost};
			frontier.insert(node);
		    }
		}
	    }
	}
	
	std::vector<int> min_costs;

	void reset() {
	    shortest_path_count = 0;
	    frontier = MinHeap<Node>();
	    min_costs = std::vector<int>(graph.size(), std::numeric_limits<int>::max());
	}
	
    };
}
	

#endif
