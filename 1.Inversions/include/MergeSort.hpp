//Copyright 2016 <Shunji Lin>

#include <vector>

template <class T>
class MergeSort {
 public:
  MergeSort() : inversions{0} {
  }

  void mergeSort(std::vector<T>& elements) {
    inversions = 0; // reset inversions
    mergeSortAux(elements, 0, elements.size());
  }

  unsigned inversions;

  /*******************************************//**
   * below:  made public for testing purposes
   ***********************************************/
  void merge(std::vector<T>& elements, size_t start, size_t end) {
    size_t mid = getMid(start, end);
    std::vector<T> output(end - start);
    size_t i = start, j = mid, k = 0;
    while (i < mid && j < end) {
      if (elements[j] < elements[i]) {
	output[k] = elements[j++];
	inversions += (mid - i); // remainder in first subarray
      } else {
	output[k] = elements[i++];
      }
      ++k;
    }
    while (i < mid) {
      output[k++] = elements[i++];
    }
    while (j < end) {
      output[k++] = elements[j++];
    }
    copyBack(output, elements, start, end);
  }

private:
  void copyBack(std::vector<T>& copy, std::vector<T>& original, size_t start, size_t end) const {
    auto it = copy.begin();
    for (size_t i = start; i < end; ++i) {
      original[i] = *it;
      ++it;
    }
  }

  void mergeSortAux(std::vector<T>& elements, size_t start, size_t end) {
    if ((end - start) == 1) {
      return;
    }
    size_t mid = getMid(start, end);
    mergeSortAux(elements, start, mid);
    mergeSortAux(elements, mid, end);
    merge(elements, start, end);
  }

  inline size_t getMid(size_t start, size_t end) {
    return start + (end - start) / 2;
  }
};
