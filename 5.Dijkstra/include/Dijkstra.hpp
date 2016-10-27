//Copyright 2016 <Shunji Lin>

#ifndef DIJKSTRA_HPP
#define DIJSTRA_HPP

#include <vector>
#include "MinHeap.hpp"
#include <limits>

namespace dijkstra {
    struct Node {
	int id;
	int total_dist;
	bool operator<(const Node & rhs) {
	    return total_dist < rhs.total_dist;
	}
    };
	
    struct Edge {
	int target_id;
	int dist;
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

	void insertEdge(int u, int v, int dist) {
	    Edge edge1 = {v, dist}; 
	    adjlist[u].emplace_back(edge1);
	}

	int size() const {
	    return adjlist.size();
	}
	std::vector< std::vector<Edge> > adjlist;
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
	        Node node = {edge.target_id, edge.dist};
		frontier.insert(node);
	    }
      
	    while (!frontier.isEmpty() && shortest_path_count < graph.size()) {
		Node target_node = frontier.extractMin();
		if (target_node.total_dist < min_costs[target_node.id]) {
		    min_costs[target_node.id] = target_node.total_dist;
		    ++shortest_path_count;
		    for (auto& edge : graph.adjlist[target_node.id]) {
			Node node = {edge.target_id, target_node.total_dist + edge.dist};
			frontier.insert(node);
		    }
		}
	    }
	}
	
	std::vector<int> min_costs;
	
    };
}
	

#endif
