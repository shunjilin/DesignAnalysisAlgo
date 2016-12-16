//Copyright 2016 <Shunji Lin>

#include <gmock/gmock.h>
#include <cstddef>
#include "UnionFind.hpp"

using namespace testing;
using namespace unionfind;

class UnionFindInitialize : public Test {
public:
    UnionFind union_find;
    std::vector<int> node_ids;
    
    virtual void SetUp() {	
	node_ids.emplace_back(1);
	node_ids.emplace_back(5);
	node_ids.emplace_back(7);
	node_ids.emplace_back(10);
	union_find = UnionFind(node_ids);
    }
    
};

TEST_F(UnionFindInitialize, ReturnsCorrectSize) {
    ASSERT_EQ(node_ids.size(), union_find.size());
}

TEST_F(UnionFindInitialize, ReturnsCorrectNClusters) {
    ASSERT_EQ(node_ids.size(), union_find.nGroups());
}

TEST_F(UnionFindInitialize, ReturnsCorrectInitialGroupings) {
    bool correct = true;
    for (auto node_id : node_ids) {
	if (union_find.find(node_id) != node_id) {
	    correct = false;
	    break;
	}
    }
    ASSERT_TRUE(correct);
}


TEST_F(UnionFindInitialize, MergesCorrectly) {
    union_find.merge(1, 5);
    union_find.merge(7, 10);
    union_find.merge(5, 7);
    ASSERT_EQ(union_find.find(1), union_find.find(10));
}



int main(int argc, char *argv[]) {
    testing::InitGoogleMock(&argc, argv);
    return RUN_ALL_TESTS();
}
