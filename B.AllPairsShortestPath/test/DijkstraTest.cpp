//Copyright 2016 <Shunji Lin>

#include <gmock/gmock.h>
#include "Dijkstra.hpp"

using namespace testing;
using namespace dijkstra;

class DijkstraInitialize : public Test {
public:
    Graph graph = Graph(8);
    std::unique_ptr<Dijkstra> dijkstra;

    void SetUp() {
	graph.insertEdge(0, 1, 1);
	graph.insertEdge(0, 7, 2);
	graph.insertEdge(1, 0, 1);
	graph.insertEdge(1, 2, 1);
	graph.insertEdge(2, 1, 1);
	graph.insertEdge(2, 3, 1);
	graph.insertEdge(3, 2, 1);
	graph.insertEdge(3, 4, 1);
	graph.insertEdge(4, 3, 1);
	graph.insertEdge(4, 5, 1);
	graph.insertEdge(5, 4, 2);
	graph.insertEdge(5, 6, 1);
	graph.insertEdge(6, 5, 1);
	graph.insertEdge(6, 7, 1);
	graph.insertEdge(7, 6, 1);
	graph.insertEdge(7, 0, 2);
	dijkstra.reset(new Dijkstra(graph));
    }
};

// private interface
/*TEST_F(DijkstraInitialize, CorrectNumberOfEdges) {
    ASSERT_EQ(2,dijkstra->graph.adjlist[1].size());
}*/ 

TEST_F(DijkstraInitialize, ReturnsCorrectShortestPaths) {
    dijkstra->getShortestPathsFrom(0);
    ASSERT_EQ(3, dijkstra->min_costs[6]);
}

TEST_F(DijkstraInitialize, ResetReturnsCorrectShortestPaths) {
    dijkstra->getShortestPathsFrom(0);
    dijkstra->reset();
    dijkstra->getShortestPathsFrom(0);
    ASSERT_EQ(3, dijkstra->min_costs[6]);
}

int main(int argc, char *argv[]) {
    testing::InitGoogleMock(&argc, argv);
    return RUN_ALL_TESTS();
}
