//Copyright 2016 <Shunji Lin>

#ifndef MINSPANNINGTREE_HPP
#define MINSPANNINGTREE_HPP

#include "MinHeap.hpp"
#include "Graph.hpp"
#include <set>
#include <iostream>

namespace minSpanningTree {

    struct Node {
	Node(int id, int edge_cost) : id(id), edge_cost(edge_cost) {};
	int id;
	int edge_cost; // edge cost to min spanning tree
	bool operator<(const Node &rhs) const {
	    return edge_cost < rhs.edge_cost;
	}
    };

    void insertNeighborsIntoFrontier(int vertex_id,
				     const Graph &graph,
				     MinHeap<Node> &frontier) {
	for (auto &edge : graph.adjlist[vertex_id]) {
	    frontier.insert(Node(edge.target_id, edge.cost));
	}
    }
    
    int returnMinSpanningTreeSum(const Graph &graph) {
	int minSpanningTreeSum = 0;
	std::set<int> minSpanningTree;	
	MinHeap<Node> frontier;
	minSpanningTree.insert(0);
	insertNeighborsIntoFrontier(0, graph, frontier);
	while (minSpanningTree.size() != graph.size()) {
	    if (frontier.isEmpty()) {
	    	std::cout << "Graph is not connected" << std::endl;
	    	break;
	    }
	    Node node = frontier.extractMin();
	    if (minSpanningTree.find(node.id) == minSpanningTree.end()) {
		minSpanningTree.insert(node.id);
		minSpanningTreeSum += node.edge_cost;
		insertNeighborsIntoFrontier(node.id, graph, frontier);
	    }
	}
	return minSpanningTreeSum;
    }
    

};

#endif
