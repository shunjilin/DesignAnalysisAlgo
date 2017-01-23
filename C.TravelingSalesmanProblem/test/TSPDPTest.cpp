#include <gmock/gmock.h>
#include "TSP_DP.hpp"

using namespace testing;
using namespace tspdp;

class TSPDPInitialize : public Test {
public:
    std::vector<Coordinate> coordinates = {{1, 1},{2, 1},{3, 1}};
    Map map = Map(coordinates);
    TSPDP tspdp = TSPDP(map);
};


TEST(Subset, kSubsetWithIndexZeroIncludedReturnsCorrectly) {
    std::vector<std::vector<bool> > subsets;
    kSubsetWithIndexZeroIncluded(subsets, 3, 2);
    std::vector<std::vector<bool> > answer = {{true, false, true},
					      {true, true, false}};
    ASSERT_EQ(subsets, answer);
}

TEST_F(TSPDPInitialize, ReturnsCorrectMinTSPValue) {
    tspdp.solve();
    ASSERT_EQ(4, tspdp.minTSPValue());
}
    



int main(int argc, char *argv[]) {
    testing::InitGoogleMock(&argc, argv);
    return RUN_ALL_TESTS();
}
