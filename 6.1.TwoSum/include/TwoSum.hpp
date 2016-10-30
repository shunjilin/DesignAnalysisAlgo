// Copyright 2016 <Shunji Lin>

#ifndef TWOSUM_HPP
#define TWOSUM_HPP

#include <vector>
#include <set>
#include <unordered_set>
#include <algorithm>
#include <iostream>

namespace twoSum {
    
    bool unique(long first, long second) {
	return  first != second;
    }

    class TwoSum {
    public:
	TwoSum(std::vector<long> input,
	       long upper_bound,
	       long lower_bound) :
	    integers(input.begin(), input.end()),
	    upper_bound(upper_bound),
	    lower_bound(lower_bound)
	{
	};

	size_t countTargetValues() {
	    fillTargetValues();
	    return sum_values.size();
	}

	const std::set<long> integers;
	const long upper_bound;
	const long lower_bound;

    private:
	std::unordered_set<int> sum_values;

	void fillTargetValues() {
	    for (auto first : integers) {
		auto max_second_iter = integers.upper_bound(upper_bound - first);
		auto min_second_iter = integers.lower_bound(lower_bound - first);
	    
		for (auto iter = min_second_iter; iter != max_second_iter;++iter) {
		    if (unique(first, *iter)) {
			sum_values.insert(*iter);
		    }
		}

	    }
	}

	bool sumNotYetFound(long sum) const {
	    return sum_values.find(sum) == sum_values.end();
	}

    };
}

#endif
