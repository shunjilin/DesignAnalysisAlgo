//Copyright 2016 <Shunji Lin>

#include <gmock/gmock.h>
#include "MinSpanningTree.hpp"
#include "Graph.hpp" 
#include <vector>
#include <map>

using namespace testing;
using namespace minSpanningTree;

class GraphInitialize : public Test {
public:
    Graph graph = Graph(4);
    virtual void SetUp() {
	graph.insertEdge(0, 1, 1);
	graph.insertEdge(1, 2, 2);
	graph.insertEdge(2, 3, 3);
	graph.insertEdge(3, 0, 4);
    }
    
};



TEST_F(GraphInitialize, ReturnsCorrectSum) {
    ASSERT_EQ(6, returnMinSpanningTreeSum(graph));
}
/*
TEST_F(MinHeapInitialize, ExtractMinReturnsCorrectly) {
    auto first = min_heap.extractMin();
    auto second = min_heap.extractMin();
    auto third = min_heap.extractMin();
    auto fourth = min_heap.extractMin();
    auto fifth = min_heap.extractMin();
    ASSERT_TRUE(first == 4 && second == 5 && third == 7
		&& fourth == 8 && fifth == 9);
}

TEST_F(MinHeapInitialize, InsertsCorrectly) {
    min_heap.insert(1);
    ASSERT_EQ(1, min_heap.extractMin());
}
*/
int main(int argc, char *argv[]) {
    testing::InitGoogleMock(&argc, argv);
    return RUN_ALL_TESTS();
}
