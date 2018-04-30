//Copyright 2016 <Shunji Lin>
/********************************************************************//**
 *                                                                  
 * WARNING: This implementation is incorrect! See updated version at
 * https://github.com/shunjilin/AlgorithmsSpecialization
 ************************************************************************/

#ifndef MWIS_DP_HPP
#define MWIS_DP_HPP

#include <vector>
#include <unordered_set>
#include <cassert>
#include <string>
#include <cstddef>

namespace mwisdp {
    struct subproblemEntry {
	subproblemEntry() : initialized(false), maxWeight(0) {}
	bool initialized;
	int maxWeight;
    };
    
    class MWISDP {
	const std::vector<int> &path;
	std::vector<subproblemEntry> subproblems;
	std::unordered_set<int> set;
	void initializeAndAssignMaxWeight(std::size_t i, int maxWeight) {
	    subproblems[i].initialized = true;
	    subproblems[i].maxWeight = maxWeight;
	}
    public:
	MWISDP(const std::vector<int> &path) : path(path), subproblems(path.size()) {}
	int maxWeightSubProblem(std::size_t i) {
	    if (i < 0 && i >= subproblems.size()) {
		throw std::string("Out of subproblem size range");
	    }
	    // base cases:
	    if (subproblems[i].initialized) return subproblems[i].maxWeight;
	    if (i == 0) {
		initializeAndAssignMaxWeight(i, path[0]);
		return subproblems[i].maxWeight;
	    }
	    if (i == 1) {
		initializeAndAssignMaxWeight(i, std::max(path[0], path[1]));
		return subproblems[i].maxWeight;
	    }
	    initializeAndAssignMaxWeight(i, std::max(maxWeightSubProblem(i - 1),
							 maxWeightSubProblem(i - 2) + path[i]));
	    return subproblems[i].maxWeight;
	}

	int maxWeightFullProblem() {
	    return maxWeightSubProblem(subproblems.size()-1);
	}

        void constructMaxWeightIndependentSet() {
	    if (!subproblems[subproblems.size()-1].initialized) {
		maxWeightFullProblem();
	    }
	    int i = subproblems.size() - 1;
	    while (i > 1) {
		if (subproblems[i-1].maxWeight >= (subproblems[i-2].maxWeight + path[i])) {
		    --i;
		} else {
		    set.insert(i);
		    i-=2;
		}
	    }
	    if (i == 1) {
		if (subproblems[1].maxWeight == path[1]) {
		    set.insert(1);
		} else {
		    set.insert(0);
		}
	    }
	    if (i == 0) {
		set.insert(0);
	    }
	}
	bool verticeInSet(int vertice) {
	    if (set.size() == 0) constructMaxWeightIndependentSet();
	    return set.find(vertice) != set.end();
	}
	    
	       
    };
};

#endif
