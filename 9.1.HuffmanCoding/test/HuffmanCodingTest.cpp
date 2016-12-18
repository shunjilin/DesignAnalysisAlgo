//Copyright 2016 <Shunji Lin>

#include <gmock/gmock.h>
#include "HuffmanCoding.hpp"
#include<vector>

using namespace testing;
using namespace huffmancoding;

class HuffmanEncodingInitialize : public Test {
public:
    HuffmanCoding<int> encoding;

    virtual void SetUp() {
	std::vector<Entry<int> > entries{
	    {1,20},{2,21},{3,7},{4,4},{5,88},{6,3},{7,9},{8,100}
	};
	encoding = HuffmanCoding<int>(entries);
    }
};

TEST_F(HuffmanEncodingInitialize, correctMinLength) {
    ASSERT_EQ(1, encoding.minLength());
}

TEST_F(HuffmanEncodingInitialize, correctMaxLength) {
    ASSERT_EQ(6, encoding.maxLength());
}


int main(int argc, char *argv[]) {
    testing::InitGoogleMock(&argc, argv);
    return RUN_ALL_TESTS();
}
