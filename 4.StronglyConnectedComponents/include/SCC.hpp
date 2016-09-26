//Copyright 2016 <Shunji Lin>

#ifndef SCC_HPP
#define SCC_HPP

#include <vector>
#include <functional>
#include <iostream>
#include <algorithm>
#include <set>


namespace scc {
    template<typename F>
    void DFS(std::vector< std::vector<int> > & adjlist,
	     std::vector<bool> & visited,
	     int node,
	     F postDFSWork) {
	visited[node] = true;
	for (auto v : adjlist[node]) {
	    if (!visited[v]) {
		DFS(adjlist, visited, v, postDFSWork);
	    }
	}
	postDFSWork(node);
    }

    struct Graph {
	Graph(int size) : adjlist(size) {};
	~Graph() = default;
	Graph(const Graph& rhs) = default;
	Graph& operator=(const Graph& rhs) = default;
	// Move constructor
	Graph(Graph&& rhs) {
	    adjlist.swap(rhs.adjlist);
	}
	// Move assignment
	Graph& operator=(Graph&& rhs) {
	    adjlist.swap(rhs.adjlist);
	    return *this;
	}
    
	void insertEdge(int u, int v) {
	    adjlist[u].emplace_back(v);
	}
	int size() const {
	    return adjlist.size();
	}
	std::vector< std::vector<int> > adjlist;
    };

    class SCC {
    public:
	SCC(Graph g) : size(g.size()),
		       graph(g),
		       reversed_graph(graph.size()),
		       ordering(graph.size(), -1),
		       grouping(graph.size(), -1) {
	    for (int u = 0, size = graph.size(); u < size; ++u) {
		for (auto v : graph.adjlist[u]) {
		    reversed_graph.adjlist[v].emplace_back(u);
		}
	    }
	};

	int size;
	Graph graph;
	Graph reversed_graph;
	std::vector<int> ordering; // index is order, entry is node
	std::vector<int> grouping; // index is node, entry is leader

	void DFS_firstPass() {
	    int N = size - 1;
	    std::vector<bool> visited(size);
	    for (int i = 0; i < size; ++i) {
		if (!visited[i]) {
		    DFS(reversed_graph.adjlist, visited, i,
			     [&](int node) {
				 if (ordering[N] == -1) ordering[N--] = node;
			     });
		}
	    }
	}

	void DFS_secondPass() {
	    std::vector<bool> visited(size);
	    for (int i = 0; i < size; ++i) {
		auto leader = ordering[i];
		if (!visited[leader]) {
		    DFS(graph.adjlist, visited, leader,
			     [&](int node) {
				 grouping[node] = leader;
			     });
		}
	    }
	}

	std::vector<int> getGroupSizes() {
	    std::multiset<int> leaders(grouping.begin(), grouping.end());
	    std::vector<int> group_sizes;
	    for (int i = 0; i < size; ++i) {
		int group_size = leaders.count(i);
		if (group_size != 0) group_sizes.emplace_back(group_size);
	    }
	    std::sort(group_sizes.begin(), group_sizes.end());
	    return group_sizes;
	}	

    
    };
}


#endif
