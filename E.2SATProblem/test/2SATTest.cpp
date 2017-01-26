//Copyright 2017 <Shunji Lin>

#include <gmock/gmock.h>
#include <algorithm>
#include "2SAT.hpp"

using namespace testing;
using namespace twosat;

const int N_NODES = 6;

class TwoSATInitialize : public Test {
public:
    std::vector<Clause> satisfiable_instance = {{-1,2}, {-2,3}, {1,-3}, {3,2}};
    TwoSat satisfiable = TwoSat(3, satisfiable_instance);
    std::vector<Clause> unsatisfiable_instance = {{1,2},{1,-2},{-1,2},{-1,-2}};
    TwoSat unsatisfiable = TwoSat(2, unsatisfiable_instance);
};

TEST(LiteralToVertice, MapsLiteralToCorrectVertice) {
    EXPECT_EQ(8, literalToVertice(5));
    EXPECT_EQ(11, literalToVertice(-6));
}

TEST_F(TwoSATInitialize, SatisfiableInstanceReturnsCorrectly) {
    ASSERT_TRUE(satisfiable.isSatisfiable());
}

TEST_F(TwoSATInitialize, UnsatisfiableInstanceReturnsCorrectly) {
    ASSERT_FALSE(unsatisfiable.isSatisfiable());
}

int main(int argc, char *argv[])
{
    testing::InitGoogleMock(&argc, argv);
    return RUN_ALL_TESTS();  
}

