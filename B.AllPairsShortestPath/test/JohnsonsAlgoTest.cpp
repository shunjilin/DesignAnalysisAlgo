//Copyright 2016 <Shunji Lin>

#include "JohnsonsAlgo.hpp"
#include <gmock/gmock.h>

using namespace testing;
using namespace johnsonsalgo;

class JohnsonsAlgoInitialize : public Test {
public:
    Graph graph = Graph(5);
    JohnsonsAlgo johnsonsalgo = JohnsonsAlgo(graph);

    void SetUp() {
	graph.insertEdge(0, 1, -10);
	graph.insertEdge(2, 1, 5);
	graph.insertEdge(0, 3, 7);
	graph.insertEdge(3, 4, 1);
	graph.insertEdge(3, 2, -2);
	graph.insertEdge(4, 1, -6);
	graph.insertEdge(2, 4, 3);
	johnsonsalgo = JohnsonsAlgo(graph);
    }

};

TEST_F(JohnsonsAlgoInitialize, PreprocessReturnsCorrectOffsets) {
    johnsonsalgo.preprocess();
    EXPECT_EQ(0, johnsonsalgo.getOffset(0));
    EXPECT_EQ(-10, johnsonsalgo.getOffset(1));
    EXPECT_EQ(-2, johnsonsalgo.getOffset(2));
    EXPECT_EQ(0, johnsonsalgo.getOffset(3));
    EXPECT_EQ(0, johnsonsalgo.getOffset(4));
}

TEST_F(JohnsonsAlgoInitialize, ReturnsCorrectShortestShortestPath) {
    johnsonsalgo.preprocess();
    ASSERT_EQ(-10, johnsonsalgo.APSPCost());
}

int main(int argc, char *argv[]) {
    testing::InitGoogleMock(&argc, argv);
    return RUN_ALL_TESTS();
}
