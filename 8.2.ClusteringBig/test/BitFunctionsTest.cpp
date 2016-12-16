//Copyright 2016 <Shunji Lin>

#include <gmock/gmock.h>
#include <utility>
#include "BitFunctions.hpp"

using namespace testing;
using namespace bitfunctions;

TEST(BitFunctionsTest, ReturnsCorrectNumberOfOnes) {
    ASSERT_EQ(2, nOnes(9));
}

TEST(BitFunctionsTest, ReturnsCorrectHammingDistance) {
    ASSERT_EQ(2, hammingDist(5, 3));
}

TEST(BitFunctionsTest, ReturnsCorrectDistanceOfOnePermutations) {
    ASSERT_EQ(std::vector<int>({11, 14}), distOneGreaterPermutations(10, 4));
}

TEST(BitFunctionsTest, ReturnsCorrectDistanceOfTwoPermutations) {
    ASSERT_EQ(std::vector<int>({15, 12}), distTwoGreaterPermutations(10, 4));
}

int main(int argc, char *argv[]) {
    testing::InitGoogleMock(&argc, argv);
    return RUN_ALL_TESTS();
}
