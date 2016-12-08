#ifndef GRAPH_HPP
#define GRAPH_HPP

#include <vector>

struct Edge {
    Edge(int target_id, int cost) : target_id(target_id), cost(cost) {}
    int target_id;
    int cost;
};

// Undirected Graph
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
	adjlist[u].emplace_back(Edge(v, cost));
	adjlist[v].emplace_back(Edge(u, cost));
    }

    size_t size() const {
	return adjlist.size();
    }
    std::vector< std::vector<Edge> > adjlist;
};

#endif
