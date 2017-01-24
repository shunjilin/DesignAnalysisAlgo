#include <gmock/gmock.h>
#include "TSP_Heuristic.hpp"

using namespace testing;
using namespace tspheuristic;

class TSPDPInitialize : public Test {
public:
    std::vector<Coordinate> coordinates = {{1, 1},{2, 1},{3, 1}};
    Map map = Map(coordinates);
    TSPHeuristic tsp = TSPHeuristic(map);
};


TEST_F(TSPDPInitialize, ReturnsCorrectMinTSPValue) {
    tsp.solve();
    ASSERT_EQ(4, tsp.TSPValue());
}

    



int main(int argc, char *argv[]) {
    testing::InitGoogleMock(&argc, argv);
    return RUN_ALL_TESTS();
}
