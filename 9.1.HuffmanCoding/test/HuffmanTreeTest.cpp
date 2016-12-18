//Copyright 2016 <Shunji Lin>

#include <gmock/gmock.h>
#include "HuffmanTree.hpp"
#include<vector>

using namespace testing;
using namespace huffmantree;

class HuffmanTreeInitialize : public Test {
public:
    HuffmanTree<int> tree;

    virtual void SetUp() {
	std::vector<Entry<int> > entries{{2,2},{1,1},{5,5},{3,3},{4,4}};
	tree = HuffmanTree<int>(entries);
    }
    
  
};

TEST_F(HuffmanTreeInitialize, initializeCorrectSize) {
    ASSERT_EQ(5, tree.minPQ.size());
}

TEST_F(HuffmanTreeInitialize, initializeCorrectMinPQ) {
    ASSERT_EQ(1, tree.minPQ.top().weight);
}

TEST_F(HuffmanTreeInitialize, mergeMaintainsCorrectSize) {
    tree.merge();
    ASSERT_EQ(4, tree.minPQ.size());

}

TEST_F(HuffmanTreeInitialize, mergeMaintainsCorrectMinPQ) {
    tree.merge();
    tree.merge();
    ASSERT_EQ(4, tree.minPQ.top().weight);
}

TEST_F(HuffmanTreeInitialize, mergeAllCorrectMinPQ) {
    tree.mergeAll();
    ASSERT_EQ(15, tree.minPQ.top().weight);
}


TEST_F(HuffmanTreeInitialize, returnCorrectMinDepth) {
    tree.mergeAll();
    ASSERT_EQ(2, tree.minDepth());
}

TEST_F(HuffmanTreeInitialize, returnCorrectMaxDepth) {
    tree.mergeAll();
    ASSERT_EQ(3, tree.maxDepth());
}

int main(int argc, char *argv[]) {
    testing::InitGoogleMock(&argc, argv);
    return RUN_ALL_TESTS();
}
