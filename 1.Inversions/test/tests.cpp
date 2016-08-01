//Copyright 2016 <Shunji Lin>

#include <gmock/gmock.h>
#include "MergeSort.hpp"
#include <vector>
#include <initializer_list>

using namespace testing;
using namespace MergeSort;
using namespace MergeSort::detail;

class MergeSortInitialize: public testing::Test {
public:
  unsigned inversions = 0;
};

TEST_F(MergeSortInitialize, MergeLengthOneVectorCorrectly) {
  std::vector<int> testVector{1};
  merge(testVector, 0, testVector.size(), inversions);
  ASSERT_THAT(testVector, Eq(std::vector<int>{1}));
}

TEST_F(MergeSortInitialize, MergeLengthTwoVectorCorrectly) {
  std::vector<int> testVector{3,2};
  merge(testVector, 0, testVector.size(), inversions);
  ASSERT_THAT(testVector, Eq(std::vector<int>{2,3}));
}

TEST_F(MergeSortInitialize, MergeEvenLengthVectorCorrectly) {
  std::vector<int> testVector {1, 3, 2, 4};
  merge(testVector, 0, testVector.size(), inversions);
  ASSERT_THAT(testVector, Eq(std::vector<int> {1, 2, 3, 4}));
}

TEST_F(MergeSortInitialize, MergeOddLengthVectorCorrectly) {
  std::vector<int> testVector {1, 3, 5, 2, 4};
  merge(testVector, 0, testVector.size(), inversions);
  ASSERT_THAT(testVector, Eq(std::vector<int> {1, 3, 5, 2, 4}));
}

TEST_F(MergeSortInitialize, MergeSortOneElementCorrectly) {
  std::vector<int> testVector{1};
  mergeSort(testVector, inversions);
  ASSERT_THAT(testVector, Eq(std::vector<int> {1}));
}

TEST_F(MergeSortInitialize, MergeSortEvenLengthVectorCorrectly) {
  std::vector<int> testVector{100, 7, 89, 35};
  mergeSort(testVector, inversions);
  ASSERT_THAT(testVector, Eq(std::vector<int>{7, 35, 89, 100}));
}

TEST_F(MergeSortInitialize, MergeSortOddLengthVectorCorrectly) {
  std::vector<int> testVector{100, 7, 89, 35, 8888};
  mergeSort(testVector);
  ASSERT_THAT(testVector, Eq(std::vector<int>{7, 35, 89, 100, 8888}));
}

TEST_F(MergeSortInitialize, MergeSortInversionsCorrect) {
  
  std::vector<int> testVector1{1, 2, 3, 4, 5};
  std::vector<int> testVector2{2, 4, 1, 3, 5};
  std::vector<int> testVector3{8, 7, 6, 5, 4, 3, 2, 1};
  std::vector<int> testVector4{5, 8, 2, 3, 1, 7, 4, 6};
  mergeSort(testVector1, inversions);
  ASSERT_THAT(inversions, Eq(0));
  inversions = 0;
  mergeSort(testVector2, inversions);
  ASSERT_THAT(inversions, Eq(3));
  inversions = 0;
  mergeSort(testVector3, inversions);
  ASSERT_THAT(inversions, Eq(28));
  inversions = 0;
  mergeSort(testVector4, inversions);
  ASSERT_THAT(inversions, Eq(14));
}
  
int main(int argc, char *argv[]) {
  testing::InitGoogleMock(&argc, argv);
  return RUN_ALL_TESTS();
}
