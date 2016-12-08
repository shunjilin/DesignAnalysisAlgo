//Copyright 2016 <Shunji Lin>

#include <gmock/gmock.h>
#include "MinHeap.hpp"
#include <vector>

using namespace testing;

class MinHeapInitialize : public Test {
public:
    MinHeap<int> min_heap{{5, 4, 7, 9, 8}};
};

TEST_F(MinHeapInitialize, ReturnsCorrectSize) {
    ASSERT_EQ(5, min_heap.size());
}

TEST_F(MinHeapInitialize, ExtractMinReturnsCorrectly) {
    auto first = min_heap.extractMin();
    auto second = min_heap.extractMin();
    auto third = min_heap.extractMin();
    auto fourth = min_heap.extractMin();
    auto fifth = min_heap.extractMin();
    ASSERT_TRUE(first == 4 && second == 5 && third == 7
		&& fourth == 8 && fifth == 9);
}

TEST_F(MinHeapInitialize, InsertsCorrectly) {
    min_heap.insert(1);
    ASSERT_EQ(1, min_heap.extractMin());
}

int main(int argc, char *argv[]) {
    testing::InitGoogleMock(&argc, argv);
    return RUN_ALL_TESTS();
}
