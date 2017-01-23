#include <gmock/gmock.h>
#include "Bitwise.hpp"
#include <vector>

using namespace testing;
using namespace bitwise;


TEST(Bitwise, countSetBitsReturnsCorrectly) {
    EXPECT_EQ(2, countSetBits(9));
}

TEST(Bitwise, isBitSetAtIndexReturnsCorrectly) {
    EXPECT_TRUE(isBitSetAtIndex(10, 1));
    EXPECT_FALSE(isBitSetAtIndex(10, 2));
}

TEST(Bitwise, setBitsAtIndexCorrectly) {
    ASSERT_EQ(0,setBitAtIndex(8, 3));
}

TEST(Bitwise,offsetByOneAndSetOneReturnsCorrectly) {
    ASSERT_EQ(offsetByOneAndSetOne(8), 17);
}

TEST(Bitwise, ConvertsBitVectorToBitsCorrectly) {
    std::vector<bool> bits = {true, false, false, true};
    ASSERT_EQ(9, bitVecToBits(bits));
}

TEST(Bitwise, kSubsetReturnsCorrectSubsets) {
    std::vector<std::vector<bool> > subsets;
    kSubset(subsets, 3, 2);
    std::vector<std::vector<bool> > answer = {{false, true, true},
			       {true, false, true},
			       {true, true, false}};
    ASSERT_EQ(subsets, answer);
}


int main(int argc, char *argv[]) {
    testing::InitGoogleMock(&argc, argv);
    return RUN_ALL_TESTS();
}
