//Copyright 2016 <Shunji Lin>

#ifndef ADJACENCYLIST_HPP
#define ADJACENCYLIST_HPP

#include <vector>
#include <set>
#include <algorithm>
#include <iostream>
#include <unordered_map>
#include <functional>
#include <utility>

// Node can be extended to include a payload
struct Node {
    // entries indicate at least one edge to neighbor
    std::set<int> neighbors;
};

// hash using bit shift and XOR
struct pair_hash {
    template <typename T1, typename T2>
    size_t operator()(const std::pair<T1, T2> &p) const {
	return (p.first >> 1) ^ (p.second << 1);
    }
};

// stores edge pair as key, count as value
// using unordered map as opposed to vector reduces look-up time,
// improves performance of about an order of 10
struct EdgeList {
    std::unordered_map<std::pair<int,int>, int, pair_hash > edges;
    int size = 0;
};

// undirected graph
// _graph only shows connectivity of graph
// where as _edges contains the actual edge counts
class AdjacencyList {
public:
    AdjacencyList(int size) : _graph(size) {
	for (int i = 0; i < size; ++i) {
	    _nodes.insert(i);
	}
    };
  
    void insertEdge(int u, int v) {
	if (_findEdgeInEdges(u, v)) {
	    return;
	}
	insertEdgeIntoEdges(u, v);
	insertEdgeIntoGraph(u, v);
    }

    void contractEdge(int u, int v) {
	removeNode(v);
	removeEdge(u, v);
	mergeNodes(u, v);
	propagateEdgeChanges(u, v);

    };

    void contractRandomEdge() {
	auto edge = getRandomEdge();
	contractEdge(edge.first, edge.second);
    }
  

    int nodeCount() {
	return _nodes.size();
    }

    int edgeCount() {
	return _edgeList.size;
    }
  
    /*******************************//**
     * exposed for testing purposes
     ***********************************/
    
    std::set<int> _nodes;
    std::vector<Node> _graph;
    EdgeList _edgeList;

    bool _findEdgeInEdges(int u, int v) const {
	auto edge = getOrderedEdge(u, v);
	return (_edgeList.edges.find(edge)
		!= _edgeList.edges.end());
    }

    bool _findEdgeInGraph(int u, int v) const {
	return (std::find(_graph[u].neighbors.begin(), _graph[u].neighbors.end(), v)
		!= _graph[u].neighbors.end());
    }

  
private:

    std::pair<int, int> getOrderedEdge(int u, int v) const {
	// edge pair (a, b) has a <= b
	std::pair<int, int> edge;
	if (u < v) {
	    edge = std::make_pair(u, v);
	} else {
	    edge = std::make_pair(v, u);
	}
	return edge;
    }
  
    void removeNode(int node) {
	_nodes.erase(node);
    }
  
    void insertEdgeIntoEdges(int u, int v) {
	auto edge = getOrderedEdge(u,  v);
	_edgeList.edges[edge] += 1;
	_edgeList.size += 1;
    }

    void removeEdge(int u, int v) {
        countAndremoveEdgeFromEdges(u, v);
	removeEdgeFromGraph(u, v);
    }

    int countAndremoveEdgeFromEdges(int u, int v) {
	auto edge = getOrderedEdge(u, v);
	auto count = _edgeList.edges[edge];
        _edgeList.size -= count;
	_edgeList.edges.erase(edge);
	return count;
    }

    void insertEdgeIntoGraph(int u, int v) {
	_graph[u].neighbors.insert(v);
	_graph[v].neighbors.insert(u);
    }

    void removeEdgeFromGraph(int u, int v) {
	_graph[u].neighbors.erase(v);
	_graph[v].neighbors.erase(u);
    }

    void mergeNodes(int u, int v) {
	mergeNodesInEdges(u, v);
	mergeNodesInGraph(u, v);
    }

    void mergeNodesInEdges(int u, int v) {
	for (int neighbor : _graph[v].neighbors) {
	    int count = countAndremoveEdgeFromEdges(v, neighbor);
	    for (int i = 0; i < count; ++i) {
		insertEdgeIntoEdges(u, neighbor);
	    }
	}
    }

    void mergeNodesInGraph(int u, int v) {
	_graph[u].neighbors.insert( _graph[v].neighbors.begin(),
				    _graph[v].neighbors.end());
	_graph[v].neighbors.clear();
    }

    // modifies any edge pointing to v to point to u
    void propagateEdgeChanges(int u, int v) {
	for (int neighbor: _graph[u].neighbors) {
	    _graph[neighbor].neighbors.erase(v);
	    _graph[neighbor].neighbors.insert(u);
	}
    }

    std::pair<int, int> getRandomEdge() {
	int randInt = rand() % _edgeList.size;
	auto it = _edgeList.edges.begin();
	for (; it != _edgeList.edges.end(); ++it) {
	    if (it->second < randInt) {
		randInt -= it->second;
	    } else {
		break;
	    }
	}
	return it->first;
    }
};

#endif


