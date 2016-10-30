// Copyright 2016 <Shunji Lin>

#include <gmock/gmock.h>
#include "MedianMaintanence.hpp"

using namespace testing

class MedianMaintanenceInitialize : public Test {
public:
    std::vector<int> integers = {2, 8, 9, 7, 3, 1, 4};
    MedianMaintanence MM = MedianMaintanence(integers);
};

TEST_F(MedianMaintanenceInitialize, GetsFirstMedianCorrectly) {
    ASSERT_EQ(2, MM.getMedian());
}

TEST_F(MedianMaintanenceInitialize, ReturnsCorrectMedianAtIndex1) {
    MM._advance_index();
    ASSERT_EQ(2, MM.getMedian());
}

TEST_F(MedianMaintanenceInitialize, ReturnsCorrectMedianAtIndex2) {
    MM._advance_index();
    MM._advance_index();
    ASSERT_EQ(8, MM.getMedian());
}

TEST_F(MedianMaintanenceInitialize, ReturnsCorrectSumOfMedians) {
    ASSERT_EQ(5, MM.getSumOfMedians());
}

int main(int argc, char *argv[])
{
    testing::InitGoogleMock(&argc, argv);
    return RUN_ALL_TESTS();  
}
