//Copyright 2016 <Shunji Lin>

#include "BellManFord.hpp"
#include <gmock/gmock.h>

using namespace testing;
using namespace bellmanford;

class BellManFordInitialize : public Test {
public:
    Graph early_termination_graph = Graph(5);
    BellManFord bellmanford1 = BellManFord(early_termination_graph);

    Graph negative_cycle_graph = Graph(3);
    BellManFord bellmanford2 = BellManFord(negative_cycle_graph);

    Graph non_early_termination_graph = Graph(3);
    BellManFord bellmanford3 = BellManFord(non_early_termination_graph);
    
    void SetUp() {
	early_termination_graph.insertEdge(0, 1, -10);
	early_termination_graph.insertEdge(2, 1, 5);
	early_termination_graph.insertEdge(0, 3, 7);
	early_termination_graph.insertEdge(3, 4, 1);
	early_termination_graph.insertEdge(3, 2, -2);
	early_termination_graph.insertEdge(4, 1, -6);
	early_termination_graph.insertEdge(2, 4, 3);
	bellmanford1 = BellManFord(early_termination_graph);

	negative_cycle_graph.insertEdge(0, 1, -1);
	negative_cycle_graph.insertEdge(1, 2, -1);
	negative_cycle_graph.insertEdge(2, 1, -1);
	bellmanford2 = BellManFord(negative_cycle_graph);

	non_early_termination_graph.insertEdge(0, 1, 1);
	non_early_termination_graph.insertEdge(1, 2, 1);
	non_early_termination_graph.insertEdge(2, 0, 1);
	bellmanford3 = BellManFord(non_early_termination_graph);
    }	
};

TEST_F(BellManFordInitialize, correctSingleSourceShortestPath) {
    bellmanford1.fillShortestPathsFrom(0);
    ASSERT_THAT(bellmanford1.getShortestPathTo(3), 7);
    
};

TEST_F(BellManFordInitialize, correctlyIdentifyNegativeCycles) {
    bellmanford2.fillShortestPathsFrom(0);
    ASSERT_TRUE(bellmanford2.hasNegativeCycle());
}

TEST_F(BellManFordInitialize, correctlySolveNonEarlyTermination) {
    bellmanford3.fillShortestPathsFrom(0);
    ASSERT_TRUE(bellmanford3.getShortestPathTo(1));
}

int main(int argc, char *argv[]) {
    testing::InitGoogleMock(&argc, argv);
    return RUN_ALL_TESTS();
}
