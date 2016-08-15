//Copyright 2016 <Shunji Lin>

#include <gmock/gmock.h>
#include <memory>
#include <algorithm>
#include "adjacencyList.hpp"

using namespace testing;

const int N_NODES = 200;

class AdjacencyListInitialize : public testing::Test {
public:
  std::unique_ptr<AdjacencyList> adjList;
  AdjacencyListInitialize() {
    adjList.reset(new AdjacencyList(N_NODES));
  }
};

TEST_F(AdjacencyListInitialize, ReturnsCorrectSize) {
  ASSERT_THAT(adjList->size(), Eq(200));
}

TEST_F(AdjacencyListInitialize, ReturnsCorrectNumberOfEdges) {
  ASSERT_THAT(adjList->n_edges(), Eq(0));
}

TEST_F(AdjacencyListInitialize, InsertsAnEdgeIntoEdgesCorrectLy) {
  adjList->insertEdge(1, 2);
  std::vector<std::pair<int, int> >::iterator it;
  it = find(adjList->_edges.begin(), adjList->_edges.end(), std::pair<int, int>(1, 2));
  ASSERT_NE(it, adjList->_edges.end()); 
}

TEST_F(AdjacencyListInitialize, InsertsAnEdgeIntoNodesCorrectly) {
  int node1 = 1, node2 = 2;
  adjList->insertEdge(node1, node2);
  std::vector<int>::iterator it1, it2;
  it1 = find(adjList->_nodes[node1].neighbors.begin(),
	     adjList->_nodes[node1].neighbors.end(), node2);
  it2 = find(adjList->_nodes[node2].neighbors.begin(),
	     adjList->_nodes[node2].neighbors.end(), node1);
  ASSERT_TRUE(*it1 == node2 && *it2 == node1); 
}

TEST_F(AdjacencyListInitialize, DoesNotInsertDuplicateEdge) {
  int node1 = 1, node2 = 2;
  adjList->insertEdge(node1, node2);
  adjList->insertEdge(node1, node2);
  ASSERT_TRUE(adjList->_edges.size() == 1 &&
	      adjList->_nodes[node1].neighbors.size() == 1 &&
	      adjList->_nodes[node2].neighbors.size() == 1);

}

int main(int argc, char *argv[])
{
  testing::InitGoogleMock(&argc, argv);
  return RUN_ALL_TESTS();
  
}

