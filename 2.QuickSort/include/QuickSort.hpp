//Copyright 2016 <Shunji Lin>

#include <vector>
#include <functional>

namespace QuickSort {
  
  namespace detail {
    // partition and get partition element index
    template<typename T>
    size_t partition(std::vector<T>& elements, size_t start, size_t end) {
      T pivot = elements[start];
      size_t i = start + 1;
      for (size_t j = start + 1; j < end; ++j) {
        if (elements[j] < pivot) {
	  std::swap(elements[j], elements[i]);
	  ++i;
	}
      }
      std::swap(elements[start], elements[i-1]);
      return i-1;
    }

    template<typename T, typename F>
    void quickSortAux(std::vector<T>& elements,
		      F choosePivot,
		      unsigned& comparisons,
		      size_t start, size_t end) {
      size_t size = end - start;
      if (size <= 1) return;
      comparisons += size - 1;
      size_t pivotIndex = choosePivot(elements, start, end);
      std::swap(elements[start], elements[pivotIndex]);
      size_t mid = partition(elements, start, end);
      quickSortAux(elements, choosePivot, comparisons, start, mid);
      quickSortAux(elements, choosePivot, comparisons, mid + 1, end);
    }

    size_t getMiddleIndex(size_t start, size_t end) {
      size_t size = end - start;
      size_t mid_offset = (size % 2 == 0) ? (size / 2) - 1 : (size / 2);
      return start + mid_offset;
    }

    template<typename T>
    const T& medianOfThree(const T& first, const T& middle, const T& last) {
      return std::max(std::min(first, middle), std::min(std::max(first, middle), last));
    }
  }

  /* Public Interface */
    
  template<typename T, typename F>
  void quickSort(std::vector<T>& elements,
		 F choosePivot,
		 unsigned& comparisons) {
    detail::quickSortAux(elements, choosePivot, comparisons, 0, elements.size()); 
  }
  // overload for use without comparison count
  template<typename T, typename F>
  void quickSort(std::vector<T>& elements, F choosePivot) {
    unsigned comparisons = 0;
    detail::quickSortAux(elements, choosePivot, comparisons, 0, elements.size()); 
  }

  struct firstPivotIndex_f {
    template <typename T>
    size_t operator() (std::vector<T> elements, size_t start, size_t end) const {
      return start;
    }
  };
  
  struct lastPivotIndex_f {
    template <typename T>
    size_t operator() (std::vector<T> elements, size_t start, size_t end) const {
      return end - 1;
    }
  };

  struct medianOfThreePivotIndex_f {
    template <typename T>
    size_t operator() (std::vector<T> elements, size_t start, size_t end) const {
      size_t mid = detail::getMiddleIndex(start, end);
      auto first = elements[start];
      auto middle = elements[mid];
      auto last = elements[end - 1];
      auto median = detail::medianOfThree(first, middle, last);
      if (median == first) {
	return start;
      } else if (median == middle) {
	return mid;
      } else {
	return end - 1;
      }
    }
  };
}
