//Copyright 2016 <Shunji Lin>

#include <gmock/gmock.h>
#include <utility>
#include "Clustering.hpp"

using namespace testing;
using namespace clusteringimplicit;

const int NBITS = 4;

class ClusteringInitialize : public Test {
public:
    Clustering clustering;
    std::vector<int> node_ids;
    virtual void SetUp() {
	node_ids.emplace_back(10);
	node_ids.emplace_back(7);
	node_ids.emplace_back(5);
	node_ids.emplace_back(1);
	clustering = Clustering(node_ids, NBITS);
    }
};

TEST_F(ClusteringInitialize, CorrectInitialNumberOfClusters) {
    ASSERT_EQ(node_ids.size(), clustering.nClusters());
}


TEST_F(ClusteringInitialize,
       MergeAllClustersWithDistOneAndTwoReturnsCorrectGroupSize) {
    clustering.mergeAllClustersWithDistOneAndTwo();
    ASSERT_EQ(2, clustering.nClusters());
}




int main(int argc, char *argv[]) {
    testing::InitGoogleMock(&argc, argv);
    return RUN_ALL_TESTS();
}
