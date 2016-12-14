//Copyright 2016 <Shunji Lin>

#include <gmock/gmock.h>
#include <cstddef>
#include "MinHeap.hpp"
#include "Clustering.hpp"

using namespace testing;
using namespace clustering;

const std::size_t SIZE = 6;

class ClusteringInitialize : public Test {
public:
    Clustering clustering;
    std::vector<Edge> edges;
    virtual void SetUp() {
	edges.emplace_back(Edge(0, 1, 5));
	edges.emplace_back(Edge(0, 2, 6));
	edges.emplace_back(Edge(0, 3, 8));
	edges.emplace_back(Edge(0, 4, 10));
	edges.emplace_back(Edge(0, 5, 8));
	edges.emplace_back(Edge(1, 2, 4));
	edges.emplace_back(Edge(1, 3, 10));
	edges.emplace_back(Edge(1, 4, 10));
	edges.emplace_back(Edge(1, 5, 12));
	edges.emplace_back(Edge(2, 3, 6));
	edges.emplace_back(Edge(2, 4, 6));
	edges.emplace_back(Edge(2, 5, 10));
	edges.emplace_back(Edge(3, 4, 5));
	edges.emplace_back(Edge(3, 5, 5));
	edges.emplace_back(Edge(4, 5, 10));
	clustering = Clustering(SIZE, edges);
    }
};

TEST_F(ClusteringInitialize, CorrectInitialNumberOfClusters) {
    ASSERT_EQ(SIZE, clustering.nClusters());
}

TEST_F(ClusteringInitialize, CorrectInitialMinDistance) {
    ASSERT_EQ(4, clustering.minClusterDistance());
}

TEST_F(ClusteringInitialize, MergeMaintainsCorrectMinDistance) {
    clustering.merge(1, 2);
    ASSERT_EQ(5, clustering.minClusterDistance());  
}

TEST_F(ClusteringInitialize, kClusterReturnsCorrectMinDistance) {
    clustering.kCluster(2);
    ASSERT_EQ(6, clustering.minClusterDistance());
}



int main(int argc, char *argv[]) {
    testing::InitGoogleMock(&argc, argv);
    return RUN_ALL_TESTS();
}
