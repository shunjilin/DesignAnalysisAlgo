//Copyright 2016 <Shunji Lin>

#include <vector>

namespace MergeSort {
    namespace detail {

	size_t getMid(size_t start, size_t end) {
	    return start + (end - start) / 2;
	}

	template<typename T>
	void copyBack(std::vector<T>& copy, std::vector<T>& original, size_t start, size_t end) {
	    auto it = copy.begin();
	    for (size_t i = start; i < end; ++i) {
		original[i] = *it;
		++it;
	    }
	}

	template<typename T>
	void merge(std::vector<T>& elements, size_t start, size_t end, unsigned& inversions) {
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
    
	template<typename T>
	void mergeSortAux(std::vector<T>& elements, size_t start, size_t end, unsigned& inversions) {
	    if ((end - start) == 1) {
		return;
	    }
	    size_t mid = getMid(start, end);
	    mergeSortAux(elements, start, mid, inversions);
	    mergeSortAux(elements, mid, end, inversions);
	    merge(elements, start, end, inversions);
	}


    }



    template<typename T>
    void mergeSort(std::vector<T>& elements, unsigned& inversions) {
	detail::mergeSortAux(elements, 0, elements.size(), inversions);
    }
    // overload
    template<typename T>
    void mergeSort(std::vector<T>& elements) {
	unsigned inversions = 0;
	detail::mergeSortAux(elements, 0, elements.size(), inversions);
    }
};
