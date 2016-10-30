//Copyright 2016 <Shunji Lin>

#include <gmock/gmock.h>
#include "TwoSum.hpp"
#include <memory>
#include <vector>

using namespace testing;
using namespace twoSum;

const long UPPER_BOUND = 10000;
const long LOWER_BOUND = -10000;

class IntegerListInitialize : public Test {
protected:
    
    //static std::unique_ptr<std::vector<int> > integers;
    std::vector<long> integers = {1, 4, 45, 6, 10, 10, 8};
    TwoSum twosum = TwoSum(integers, UPPER_BOUND, LOWER_BOUND);

};

TEST_F(IntegerListInitialize, ReturnsCountOfTargetValuesCorrectly) {
    ASSERT_EQ(14, twosum.countTargetValues());
}

int main(int argc, char *argv[])
{
    testing::InitGoogleMock(&argc, argv);
    return RUN_ALL_TESTS();
  
}
