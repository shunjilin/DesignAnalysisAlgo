//Copyright 2016 <Shunji Lin>

#ifndef MINHEAP_HPP
#define MINHEAP_HPP

#include <vector>
#include <cassert>
#include <string>

template <typename Node> class MinHeap {
    std::vector<Node> heapArray;

    int get_left_index(int index) {
	return index * 2 + 1;
    }

    int get_right_index(int index) {
	return index * 2 + 2;
    }

    int get_parent_index(int index) {
	return (index - 1) /2;
    }

    
    void minHeapify(int index) {
	assert(index < this->size());
	int left_index = get_left_index(index);
	int right_index = get_right_index(index);
	int min_index = index; 
	if (left_index < size() &&
	    heapArray[left_index] < heapArray[min_index]) {
	    min_index = left_index;
	}
	if (right_index < size() &&
	    heapArray[right_index] < heapArray[min_index]) {
	    min_index = right_index;
	}
	if (min_index != index) {
	    std::swap(heapArray[min_index], heapArray[index]);
	    minHeapify(min_index);
	}
    }

    void buildMinHeap() {
	if (size() <= 1) return;
	for (int i = get_parent_index(size()-1); i >= 0 ; --i) {
	    minHeapify(i);
	}
    }

    void bubble_up(int index) {
	if (index == 0) return;
	int parent_index = get_parent_index(index);
	if (heapArray[index] < heapArray[parent_index]) {
	    std::swap(heapArray[index], heapArray[parent_index]);
	    bubble_up(parent_index);
	}
    }
	
public:
    MinHeap() {};
    MinHeap(std::vector<Node> elements) : heapArray(elements) {
	buildMinHeap();
    };
    
    int size() { return heapArray.size(); }

    bool isEmpty() { return size() == 0; }

    Node min() {
	if (size() == 0) throw std::string("minOnEmpty");
	return heapArray[0];
    }
	
    void popMin() {
	if (size() == 0) throw std::string("popMinOnEmpty");
	std::swap(heapArray[0], heapArray[size() - 1]);
	heapArray.pop_back();
	if (size() != 0) minHeapify(0);
    }

    Node extractMin() {
	Node min = this->min();
	popMin();
	return min;
    }    

    void insert(Node node) {
	heapArray.emplace_back(node);
	bubble_up(size() - 1);
    }

    

};

#endif
