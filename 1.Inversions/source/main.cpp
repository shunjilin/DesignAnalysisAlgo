//Copyright 2016 <Shunji Lin>

#include <iostream>
#include <gmock/gmock.h>
#include "MergeSort.hpp"
#include <vector>
#include <initializer_list>

using namespace testing;

class MergeSortInitialize: public testing::Test {
public:
  MergeSort<int> mergesort;
};

TEST_F(MergeSortInitialize, MergeOneLengthVectorCorrectly) {
  std::vector<int> testVector{1};
  mergesort.merge(testVector, 0, testVector.size());
  ASSERT_THAT(testVector, Eq(std::vector<int>{1}));
}

TEST_F(MergeSortInitialize, MergeLengthTwoVectorCorrectly) {
  std::vector<int> testVector{3,2};
  mergesort.merge(testVector, 0, testVector.size());
  ASSERT_THAT(testVector, Eq(std::vector<int>{2,3}));
}

TEST_F(MergeSortInitialize, MergeEvenLengthVectorCorrectly) {
  std::vector<int> testVector {1, 3, 2, 4};
  mergesort.merge(testVector, 0, testVector.size());
  ASSERT_THAT(testVector, Eq(std::vector<int> {1, 2, 3, 4}));
}

TEST_F(MergeSortInitialize, MergeOddLengthVectorCorrectly) {
  std::vector<int> testVector {1, 3, 5, 2, 4};
  mergesort.merge(testVector, 0, testVector.size());
  ASSERT_THAT(testVector, Eq(std::vector<int> {1, 3, 5, 2, 4}));
}

TEST_F(MergeSortInitialize, MergeSortOneElementCorrectly) {
  std::vector<int> testVector{1};
  mergesort.mergeSort(testVector);
  ASSERT_THAT(testVector, Eq(std::vector<int> {1}));
}

TEST_F(MergeSortInitialize, MergeSortEvenLengthVectorCorrectly) {
  std::vector<int> testVector{100, 7, 89, 35};
  mergesort.mergeSort(testVector);
  ASSERT_THAT(testVector, Eq(std::vector<int>{7, 35, 89, 100}));
}

TEST_F(MergeSortInitialize, MergeSortOddLengthVectorCorrectly) {
  std::vector<int> testVector{100, 7, 89, 35, 8888};
  mergesort.mergeSort(testVector);
  ASSERT_THAT(testVector, Eq(std::vector<int>{7, 35, 89, 100, 8888}));
}

TEST_F(MergeSortInitialize, NoInversionsOnInitialization) {
  ASSERT_THAT(mergesort.inversions, Eq(0));
}

TEST_F(MergeSortInitialize, MergeSortInversionsCorrect) {
  MergeSort<int> mergesort;
  
  std::vector<int> testVector1{1, 2, 3, 4, 5};
  std::vector<int> testVector2{2, 4, 1, 3, 5};
  std::vector<int> testVector3{3, 4, 1, 2};

  mergesort.mergeSort(testVector1);
  ASSERT_THAT(mergesort.inversions, Eq(0));
  mergesort.inversions = 0;
  mergesort.mergeSort(testVector2);
  ASSERT_THAT(mergesort.inversions, Eq(3));
  mergesort.inversions=0;
  mergesort.mergeSort(testVector3);
  ASSERT_THAT(mergesort.inversions, Eq(4));
}

TEST_F(MergeSortInitialize, RepeatedMergeSortInversionsCorrect) {
  MergeSort<int> mergesort;
  
  std::vector<int> testVector1{1, 2, 3, 4, 5};
  std::vector<int> testVector2{2, 4, 1, 3, 5};
  std::vector<int> testVector3{8, 7, 6, 5, 4, 3, 2, 1};
  std::vector<int> testVector4{5, 8, 2, 3, 1, 7, 4, 6};
  mergesort.mergeSort(testVector1);
  ASSERT_THAT(mergesort.inversions, Eq(0));
  mergesort.mergeSort(testVector2);
  ASSERT_THAT(mergesort.inversions, Eq(3));
  mergesort.mergeSort(testVector3);
  ASSERT_THAT(mergesort.inversions, Eq(28));
  mergesort.mergeSort(testVector4);
  ASSERT_THAT(mergesort.inversions, Eq(14));
}
  
int main(int argc, char *argv[]) {
  // Read from file into vector
  std::vector<int> testVector;
  int entry;
  while (std::cin >> entry) {
    testVector.emplace_back(entry);
  }
  MergeSort<int> mergesort;
  mergesort.mergeSort(testVector);
  std::cout << "Number of inversions is : " << mergesort.inversions << std::endl;
  
  testing::InitGoogleMock(&argc, argv);
  return RUN_ALL_TESTS();
}
