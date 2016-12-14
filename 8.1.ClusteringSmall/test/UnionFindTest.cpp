//Copyright 2016 <Shunji Lin>

#include <gmock/gmock.h>
#include <cstddef>
#include "UnionFind.hpp"

using namespace testing;
using namespace unionfind;
const std::size_t SIZE = 10;

class UnionFindInitialize : public Test {
public:
    UnionFind union_find{SIZE};
};

TEST_F(UnionFindInitialize, ReturnsCorrectSize) {
    ASSERT_EQ(SIZE, union_find.size());
}

TEST_F(UnionFindInitialize, ReturnsCorrectInitialGroupings) {
    bool correct = true;
    for (std::size_t i = 0; i < SIZE; ++i) {
	if (union_find.find(i) != i) {
	    correct = false;
	    break;
	}
    }
    ASSERT_TRUE(correct);
}

TEST_F(UnionFindInitialize, MergesCorrectly) {
    union_find.merge(0, 1);
    union_find.merge(2, 3);
    union_find.merge(1, 2);
    ASSERT_EQ(union_find.find(0), union_find.find(3));
}



int main(int argc, char *argv[]) {
    testing::InitGoogleMock(&argc, argv);
    return RUN_ALL_TESTS();
}
