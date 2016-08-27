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

TEST_F(AdjacencyListInitialize, ReturnsCorrectNodeCount) {
    ASSERT_TRUE(adjList->_graph.size() == N_NODES &&
		adjList->_nodes.size() == N_NODES);
}

TEST_F(AdjacencyListInitialize, InsertsAnEdgeIntoGraphCorrectly) {
    int node1 = 1, node2 = 2;
    adjList->insertEdge(node1, node2);
    std::set<int>::iterator it1, it2;
    ASSERT_TRUE(adjList->_findEdgeInGraph(node1, node2) &&
		adjList->_findEdgeInGraph(node2, node1)); 
}

TEST_F(AdjacencyListInitialize, DoesNotInsertDuplicateEdgeIntoGraph) {
    int node1 = 1, node2 = 2;
    adjList->insertEdge(node1, node2);
    adjList->insertEdge(node1, node2);
    ASSERT_TRUE(adjList->_graph[node1].neighbors.size() == 1 &&
		adjList->_graph[node2].neighbors.size() == 1);
}

TEST_F(AdjacencyListInitialize, InsertsEdgeIntoEdgesCorrectly) {
    int node1 = 1, node2 = 2;
    adjList->insertEdge(node1, node2);
    auto edge = std::make_pair(node1, node2);
    ASSERT_FALSE(adjList->_edgeList.edges.find(edge)
		 == adjList->_edgeList.edges.end());
}

class AdjacencyListWithEdges : public testing::Test {
public:
    std::unique_ptr<AdjacencyList> adjList;
    int node1 = 1, node2 = 2, node3 = 3, node4 = 4;
    AdjacencyListWithEdges() {
	adjList.reset(new AdjacencyList(N_NODES));
	adjList->insertEdge(node1, node2);
	adjList->insertEdge(node2, node4);
	adjList->insertEdge(node1, node3);
	adjList->insertEdge(node3, node4);
    }
};

TEST_F(AdjacencyListWithEdges, EdgeContractRemovesSecondNode) {
    adjList->contractEdge(node2, node4);
    ASSERT_THAT(adjList->_nodes.find(node4), Eq(adjList->_nodes.end()));
}


TEST_F(AdjacencyListWithEdges, EdgeContractMergesNodesInEdges) {
    adjList->contractEdge(node2, node4);
    ASSERT_TRUE(adjList->_findEdgeInEdges(node2, node3) == true &&
		adjList->_findEdgeInEdges(node4, node3) == false);

}

TEST_F(AdjacencyListWithEdges, EdgeContractMergesNodesInGraph) {
    adjList->contractEdge(node2, node4);
  
    ASSERT_TRUE(adjList->_findEdgeInGraph(2, 1) &&
		adjList->_findEdgeInGraph(2, 3) &&
		adjList->_graph[4].neighbors.size() == 0);
  
}


TEST_F(AdjacencyListWithEdges, EdgeContractRemovesSelfLoopsInEdges) {
    adjList->contractEdge(node2, node4);
    ASSERT_FALSE(adjList->_findEdgeInEdges(node2, node4));
}

TEST_F(AdjacencyListWithEdges, EdgeContractRemovesSelfLoopsInGraph) {
    adjList->contractEdge(node2, node4);
    ASSERT_FALSE(adjList->_findEdgeInGraph(node2, node2) || adjList->_findEdgeInGraph(node2, node4));
}

TEST_F(AdjacencyListWithEdges, EdgeContractRemovesEdgesToRemovedNodeInEdges) {
    adjList->contractEdge(node2, node4);
    ASSERT_FALSE(adjList->_findEdgeInEdges(node3, node4));

}

TEST_F(AdjacencyListWithEdges, EdgeContractRemovesEdgesToRemovedNodeInGraph) {
    adjList->contractEdge(node2, node4);
    ASSERT_FALSE(adjList->_findEdgeInGraph(node3, node4));
}

TEST_F(AdjacencyListWithEdges, NodeCountReturnsCorrectCountAfterContractions) {
    adjList->contractEdge(node2, node4);
    adjList->contractEdge(node1, node3);
    ASSERT_THAT(adjList->nodeCount(), Eq(N_NODES - 2));

}

TEST_F(AdjacencyListWithEdges, EdgeCountReturnsCorrectCountAfterContractions) {
    ASSERT_THAT(adjList->edgeCount(), Eq(4));

}

TEST_F(AdjacencyListWithEdges, RandomContractionsReducesEdgesCorrectly) {

    for (int i = 0; i < 3; ++i) {
	adjList->contractRandomEdge();
    }
    ASSERT_THAT(adjList->edgeCount(), Eq(0));
}

int main(int argc, char *argv[])
{
    testing::InitGoogleMock(&argc, argv);
    return RUN_ALL_TESTS();
  
}

