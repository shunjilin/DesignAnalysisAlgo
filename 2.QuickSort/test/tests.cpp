//Copyright 2016 <Shunji Lin>

#include <gmock/gmock.h>
#include <vector>
#include <initializer_list>
#include "QuickSort.hpp"

using namespace testing;
using namespace QuickSort;
using namespace QuickSort::detail;


TEST(QuickSort, FirstPivotIndexReturnsCorrectIndex) {
  std::vector<int> testVector{5, 6, 7, 8, 9};
  firstPivotIndex_f firstPivotIndex_o;
  ASSERT_THAT(firstPivotIndex_o(testVector, 0, testVector.size()), Eq(0));
}

TEST(QuickSort, LastPivotIndexReturnsCorrectIndex) {
  std::vector<int> testVector{5, 6, 7, 8, 9};
  lastPivotIndex_f lastPivotIndex_o;
  ASSERT_THAT(lastPivotIndex_o(testVector, 0, testVector.size()), Eq(4));
}

TEST(QuickSort, medianOfThreeReturnsCorrectElement) {
  ASSERT_THAT(medianOfThree(1, 3, 2), Eq(2));
  ASSERT_THAT(medianOfThree(1, 2, 3), Eq(2));
  ASSERT_THAT(medianOfThree(2, 1, 3), Eq(2));
  ASSERT_THAT(medianOfThree(2, 3, 1), Eq(2));
  ASSERT_THAT(medianOfThree(3, 1, 2), Eq(2));
  ASSERT_THAT(medianOfThree(3, 2, 1), Eq(2));
}

TEST(QuickSort, getMiddleIndexReturnsCorrectIndex) {
  std::vector<int> testVector1{1, 2, 3, 4};
  std::vector<int> testVector2{1, 2, 3, 4, 5};
  ASSERT_THAT(getMiddleIndex(0, testVector1.size()), Eq(1));
  ASSERT_THAT(getMiddleIndex(0, testVector2.size()), Eq(2));
}

TEST(QuickSort, MedianOfThreePivotIndexReturnsCorrectIndex) {
  std::vector<int> testVector1{5, 6, 7, 8, 9};
  std::vector<int> testVector2{7, 3, 9, 1, 5};
  std::vector<int> testVector3{5, 7, 3, 9};
  std::vector<int> testVector4{9, 5, 100, 7};
  medianOfThreePivotIndex_f medianOfThreePivotIndex_o;
  ASSERT_THAT(medianOfThreePivotIndex_o(testVector1, 0, testVector1.size()), Eq(2));
  ASSERT_THAT(medianOfThreePivotIndex_o(testVector2, 0, testVector2.size()), Eq(0));
  ASSERT_THAT(medianOfThreePivotIndex_o(testVector3, 0, testVector3.size()), Eq(1));
  ASSERT_THAT(medianOfThreePivotIndex_o(testVector4, 0, testVector4.size()), Eq(3));
}


TEST(QuickSort, PartitionReturnsCorrectIndex) {
  std::vector<int> testVector{5, 6, 4, 7, 3};
  ASSERT_THAT(partition(testVector, 0, testVector.size()), Eq(2));
}

TEST(QuickSort, PartitionModifiesVectorCorrectly) {
  std::vector<int> testVector{5, 6, 4, 7, 3};
  partition(testVector, 0, testVector.size());
  ASSERT_THAT(testVector, Eq(std::vector<int>{3, 4, 5, 7, 6}));
}

TEST(QuickSort, QuickSortSortsCorrectly) {
  std::vector<int> testVector1{5, 6, 4, 7, 3};
  std::vector<int> testVector2{5, 6, 4, 7, 3, 1};
  std::vector<int> testVector3{5, 6, 4, 7, 3, 8, 1};
  firstPivotIndex_f firstPivotIndex_o;
  lastPivotIndex_f lastPivotIndex_o;
  medianOfThreePivotIndex_f medianOfThreePivotIndex_o;
  quickSort(testVector1, firstPivotIndex_o);
  ASSERT_THAT(testVector1, Eq(std::vector<int>{3, 4, 5, 6, 7}));
  quickSort(testVector2, lastPivotIndex_o);
  ASSERT_THAT(testVector2, Eq(std::vector<int>{1, 3, 4, 5, 6, 7}));
  quickSort(testVector3, medianOfThreePivotIndex_o);
  ASSERT_THAT(testVector3, Eq(std::vector<int>{1, 3, 4, 5, 6, 7, 8}));
}

TEST(QuickSort, FirstPivotReturnsCorrectComparisonCount) {
  std::vector<int> testVector{3, 9, 8, 4, 6, 10, 2, 5, 7, 1};
  unsigned comparisons = 0;
  firstPivotIndex_f firstPivotIndex_o;
  quickSort(testVector, firstPivotIndex_o, comparisons);
  ASSERT_THAT(comparisons, Eq(25));
}

TEST(QuickSort, LastPivotReturnsCorrectComparisonCount) {
  std::vector<int> testVector{3, 9, 8, 4, 6, 10, 2, 5, 7, 1};
  unsigned comparisons = 0;
  lastPivotIndex_f lastPivotIndex_o;
  quickSort(testVector, lastPivotIndex_o, comparisons);
  ASSERT_THAT(comparisons, Eq(29));
}

TEST(QuickSort, MedianOfThreePivotReturnsCorrectComparisonCount) {
  std::vector<int> testVector{3, 9, 8, 4, 6, 10, 2, 5, 7, 1};
  unsigned comparisons = 0;
  medianOfThreePivotIndex_f medianOfThreePivotIndex_o;
  quickSort(testVector, medianOfThreePivotIndex_o, comparisons);
  ASSERT_THAT(comparisons, Eq(21));
}




int main(int argc, char *argv[]) {
  testing::InitGoogleMock(&argc, argv);
  return RUN_ALL_TESTS();
}
