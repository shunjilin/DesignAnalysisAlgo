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
    EXPECT_TRUE(map.distance(0,1) == map.distance(1,0));
    EXPECT_TRUE(map.distance(1,2) == map.distance(2,1));
}

TEST_F(MapInitialize, ReturnsCorrectEuclideanDistance) {
    EXPECT_TRUE(map.distance(0,1) < 2.83 &&
		map.distance(0,1) > 2.82);
    EXPECT_TRUE(map.distance(0,2) < 5.66 &&
		 map.distance(0,2) > 5.65);
    EXPECT_TRUE(map.distance(1,2) < 2.83 &&
		map.distance(1,2) > 2.82);
}


int main(int argc, char *argv[]) {
    testing::InitGoogleMock(&argc, argv);
    return RUN_ALL_TESTS();
}
