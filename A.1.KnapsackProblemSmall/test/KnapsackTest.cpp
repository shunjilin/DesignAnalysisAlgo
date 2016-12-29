//Copyright 2016 <Shunji Lin>

#include "KnapsackIterative.hpp"
#include <gmock/gmock.h>
#include <vector>

using namespace testing;
using namespace knapsack;

const int MAX_WEIGHT = 165;

class TableInitialize : public Test {
public:
    std::vector<Item> items;
    KnapsackIterative knapsack;
    TableInitialize() : items{{92,23}, {57,31}, {49,29}, {68, 44}, {60,53}
	,{43,38}, {67,63}, {84,85}, {87,89}, {72,82}},
			knapsack(items, MAX_WEIGHT) {}
};

TEST_F(TableInitialize, ReturnsCorrectOptimalSolution) {
    ASSERT_EQ(knapsack.optimalSolution(), 92 + 57 + 49 + 68 + 43);
}



int main(int argc, char *argv[]) {
    testing::InitGoogleMock(&argc, argv);
    return RUN_ALL_TESTS();
}
