#include <gmock/gmock.h>
#include "Map.hpp"

using namespace testing;
using namespace map;

class MapInitialize : public Test {
public:
    std::vector<Coordinate> coordinates = {{1, 2},{3, 4},{5, 6}};
    Map map = Map(coordinates);
};

TEST_F(MapInitialize, DistancesSymmetric) {
    EXPECT_TRUE(map.distanceSquared(0,1) == map.distanceSquared(1,0));
    EXPECT_TRUE(map.distanceSquared(1,2) == map.distanceSquared(2,1));
}

TEST_F(MapInitialize, ReturnsCorrectEuclideanDistance) {
    EXPECT_TRUE(map.distanceSquared(0,1) == 8);
    EXPECT_TRUE(map.distanceSquared(0,2) == 32);
    EXPECT_TRUE(map.distanceSquared(1,2) == 8);
}


int main(int argc, char *argv[]) {
    testing::InitGoogleMock(&argc, argv);
    return RUN_ALL_TESTS();
}
