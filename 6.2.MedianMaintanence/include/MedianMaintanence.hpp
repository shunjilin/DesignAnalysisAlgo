// Copyright 2016 <Shunji Lin>

#ifndef MEDIANMAINTANENCE_HPP
#define MEDIANMAINTANENCE_HPP

#include <vector>
#include <queue>
#include <iostream>

const int MODVALUE = 10000;

class MedianMaintanence {
public:
    MedianMaintanence(std::vector<int> input) : integers(input),
						index(0) {
	left_heap.push(integers[0]);
    }
    
    int getSumOfMedians() {
	int sum = 0;
	while (!endOfIndex()) {
	    sum += getMedian();
	    _advance_index();
	}
	return sum % integers.size();
    }

    bool endOfIndex() const {
	return index == integers.size();
    }
    
    int getMedian() const {
	return left_heap.empty() ? 0 : left_heap.top();
    }
    

    // exposed for testing purposes
    void _advance_index() {
	++index;
	if (endOfIndex()) return;
	push(integers[index]);
	restore_heap_invariant();
    }
    
private:
    std::vector<int> integers;
    unsigned index;
    std::priority_queue<int> left_heap;
    std::priority_queue<int, std::vector<int>, std::greater<int> > right_heap;

    bool right_heavy() const {
	return right_heap.size() > left_heap.size();
    }

    bool left_heavy() const {
	return left_heap.size() > right_heap.size() + 1;
    }

    void push(int value) {
	if (!right_heap.empty() && value > right_heap.top()) {
	    right_heap.push(value);
	} else {
	    left_heap.push(value);
	}
    }

    void restore_heap_invariant() {
	if (left_heavy()) {
	    right_heap.push(left_heap.top());
	    left_heap.pop();
	}
	if (right_heavy()) {
	    left_heap.push(right_heap.top());
	    right_heap.pop();
	}	
    }
    
};

#endif
