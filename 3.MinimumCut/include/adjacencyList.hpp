//Copyright 2016 <Shunji Lin>

#include <vector>
#include <set>
#include <algorithm>

// Node can be extended to include a payload,
// currently only has an id
struct Node {
    int id;
    // entries indicate at least one edge to neighbor
    std::set<int> neighbors;
};


// undirected graph
// _graph only shows connectivity of graph
// where as _edges contains the actual edges
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
	return _edges.size();
    }
  
    // exposed for testing purposes
    std::set<int> _nodes;
    std::vector<Node> _graph;
    // stores edge pair as key, and count as value
    std::vector<std::pair<int,int> > _edges;

    bool _findEdgeInEdges(int u, int v) const {
	auto edge = getOrderedEdge(u, v);
	return (std::find(_edges.begin(), _edges.end(), edge) != _edges.end());
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

    template< typename T >
    int countAndRemoveAllFromVec(T elem, std::vector<T> &vec) {
	auto it = std::remove(vec.begin(), vec.end(), elem);
	int count = std::distance(it, vec.end());
	vec.erase(it, vec.end());
	return count;
    }
  
    void removeNode(int node) {
	_nodes.erase(node);
    }
  
    void insertEdgeIntoEdges(int u, int v) {
	auto edge = getOrderedEdge(u,  v);
	_edges.emplace_back(edge);
    }

    void removeEdge(int u, int v) {
	countAndremoveEdgeFromEdges(u, v);
	removeEdgeFromGraph(u, v);
    }

    int countAndremoveEdgeFromEdges(int u, int v) {
	auto edge = getOrderedEdge(u, v);
	return countAndRemoveAllFromVec<std::pair<int, int> >(edge, _edges); 
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
	int randInt = rand() % _edges.size();
	auto it = _edges.begin();
	advance(it, randInt);
	return *it;
    }

};




