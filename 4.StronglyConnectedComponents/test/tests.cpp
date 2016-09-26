//Copyright 2016 <Shunji Lin>

#include <gmock/gmock.h>
#include <algorithm>
#include "SCC.hpp"

using namespace testing;
using namespace scc;

const int N_NODES = 6;

class GraphInitialize : public Test {
public:
    std::unique_ptr<Graph> graph;
    std::unique_ptr<SCC> scc;

    GraphInitialize() {
	graph.reset(new Graph(N_NODES));
	graph->insertEdge(0, 1);
	graph->insertEdge(1, 2);
	graph->insertEdge(2, 0);
	graph->insertEdge(1, 3);
	graph->insertEdge(3, 4);
	graph->insertEdge(4, 5);
	graph->insertEdge(5, 3);
	scc.reset(new SCC(std::move(*graph)));
    }
};

TEST_F(GraphInitialize, InsertEdgeCorrectly) {
    ASSERT_TRUE(std::find(scc->graph.adjlist[0].begin(),
			  scc->graph.adjlist[0].end(),
			  1) != scc->graph.adjlist[1].end() &&
		std::find(scc->graph.adjlist[1].begin(),
			  scc->graph.adjlist[1].end(),
			  2) != scc->graph.adjlist[1].end());
}

TEST_F(GraphInitialize, ReverseEdgeCorrectly) {
    ASSERT_TRUE(std::find(scc->reversed_graph.adjlist[1].begin(),
			  scc->reversed_graph.adjlist[1].end(),
			  0) != scc->reversed_graph.adjlist[1].end() &&
		std::find(scc->reversed_graph.adjlist[2].begin(),
			  scc->reversed_graph.adjlist[2].end(),
			  1) != scc->reversed_graph.adjlist[1].end());
}

TEST_F(GraphInitialize, DFSFirstPassOrdersCorrectly) {
    scc->DFS_firstPass();
    std::vector<int> correct_ordering = { 3, 5, 4, 0, 2, 1};

    ASSERT_TRUE(std::equal(scc->ordering.begin(), scc->ordering.end(),
			   correct_ordering.begin()));
}

TEST_F(GraphInitialize, DFSSecondPassGroupsCorrectly) {
    scc->DFS_firstPass();
    scc->DFS_secondPass();
    std::vector<int> correct_grouping = { 0, 0, 0, 3, 3, 3};

    ASSERT_TRUE(std::equal(scc->grouping.begin(), scc->grouping.end(),
			   correct_grouping.begin()));

}

TEST_F(GraphInitialize, ReturnsCorrectGroupSizes) {
    scc->DFS_firstPass();
    scc->DFS_secondPass();
    std::vector<int> group_sizes = scc->getGroupSizes();
    std::vector<int> correct_group_sizes = { 3, 3 };

    ASSERT_TRUE(std::equal(group_sizes.begin(), group_sizes.end(),
			  correct_group_sizes.begin()));
    
}



int main(int argc, char *argv[])
{
    testing::InitGoogleMock(&argc, argv);
    return RUN_ALL_TESTS();
  
}

