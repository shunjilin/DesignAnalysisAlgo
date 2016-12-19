//Copyright 2016 <Shunji Lin>

#include "MWIS_DP.hpp"
#include <gmock/gmock.h>
#include <vector>

using namespace testing;
using namespace mwisdp;

class PathInitialize : public Test {
public:
    std::vector<int> path;
    MWISDP mwisdp;
    PathInitialize() : path{{5, 99, 2, 48, 29, 88, 9}},
		       mwisdp(path) {}
};

TEST_F(PathInitialize, CorrectMaxWeightSubProblemSize3) {
    ASSERT_EQ(99, mwisdp.maxWeightSubProblem(2)); 
}

TEST_F(PathInitialize, CorrectMaxWeightFullProblem) {
    ASSERT_THAT(99 + 48 + 88, mwisdp.maxWeightFullProblem());
}

TEST_F(PathInitialize, CorrectMaxWeightIndependentSet) {
    mwisdp.constructMaxWeightIndependentSet();
    ASSERT_TRUE(!mwisdp.verticeInSet(0) && mwisdp.verticeInSet(1) &&
		!mwisdp.verticeInSet(2) && mwisdp.verticeInSet(3) &&
		!mwisdp.verticeInSet(4) && mwisdp.verticeInSet(5) &&
		!mwisdp.verticeInSet(6));
}

int main(int argc, char *argv[]) {
    testing::InitGoogleMock(&argc, argv);
    return RUN_ALL_TESTS();
}
