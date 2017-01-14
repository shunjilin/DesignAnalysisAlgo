//Copyright 2017 <Shunji Lin>

#ifndef JOHNSON_ALGO_HPP
#define JOHNSON_ALGO_HPP

#include "Dijkstra.hpp"
#include "BellManFord.hpp"
#include "Graph.hpp"
#include <vector>
#include <limits>
#include <cassert>

using namespace bellmanford;
using namespace dijkstra;

namespace johnsonsalgo {
    class JohnsonsAlgo {
	Graph graph;
	std::vector<int> preprocess_offsets;
	bool preprocessed;
	bool negative_cycle;
    public:
	JohnsonsAlgo(Graph g) : graph(g),
				preprocess_offsets(g.size(), INFTY),
				preprocessed(false),
				negative_cycle(false) {
	    // add a dummy source node that has outgoing zero-cost edges to all nodes
	    graph.adjlist.emplace_back(std::vector<Edge>());
	    for (int v = 0, size = graph.size()-1; v < size; ++v) {
		graph.insertEdge(size, v, 0);
	    }
	}

	void preprocess() {
	    BellManFord bellmanford(graph);
	    bellmanford.fillShortestPathsFrom(graph.size()-1);
	    if (!bellmanford.hasNegativeCycle()) {
		for (int i = 0, size = graph.size()-1; i < size; ++i) {
		    preprocess_offsets[i] = bellmanford.getShortestPathTo(i);
		}
		// offset edges
		for (int u = 0, size = graph.size(); u < size; ++u) {
		    for (auto &edge : graph.adjlist[u]) {
			edge.cost += preprocess_offsets[u] - preprocess_offsets[edge.target_id];
		    }
		}
	    } else {
		negative_cycle = true;
	    }
	    graph.adjlist.pop_back(); // remove dummy source node
	    preprocessed = true;
	}

	bool hasNegativeCycle() const {
	    return negative_cycle;
	}

	int getOffset(int node) const {
	    assert(preprocessed);
	    return preprocess_offsets[node];
	}

	int APSPCost() const {
	    assert(!negative_cycle && preprocessed);
	    int shortest_shortest_path = INFTY;
	    Dijkstra dijkstra = Dijkstra(graph);
	    for (int u = 0, size = graph.size(); u < size; ++u) {
		dijkstra.reset();
		dijkstra.getShortestPathsFrom(u);
		for (int v = 0; v < size; ++v) {
		    int shortest_uv_path = (dijkstra.min_costs[v] == INFTY) ?
			INFTY :
			dijkstra.min_costs[v] - preprocess_offsets[u] + preprocess_offsets[v];
		    if (shortest_uv_path < shortest_shortest_path)
			shortest_shortest_path = shortest_uv_path;
		}
	    }
	    return shortest_shortest_path;
	}
	
    };

};



#endif
