//Copyright 2016 <Shunji Lin>

#include <vector>
#include <algorithm>

// Node can be extended to include a payload,
// currently only has an id
struct Node {
  int id;
  std::vector<int> neighbors;
};


class AdjacencyList {
public:
  AdjacencyList(int size) : _nodes(size), _edges(0) {};
  int size() { return _nodes.size(); };
  int n_edges() { return _edges.size(); };
  void insertEdge(int u, int v) {
    if (findEdge(u, v)) {
      return;
    }
    _edges.emplace_back(std::pair<int, int>(u, v) );
    _nodes[u].neighbors.emplace_back(v);
    _nodes[v].neighbors.emplace_back(u);
  }

  // exposed for testing purposes
  std::vector<Node> _nodes;
  std::vector< std::pair<int, int> > _edges;
private:
  bool findEdge(int u, int v) {
    std::vector<int>::iterator it;
    it = find(_nodes[u].neighbors.begin(), _nodes[u].neighbors.end(), v);
    if (it != _nodes[u].neighbors.end()) return true;
    return false;
  }
};




