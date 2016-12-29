//Copyright 2016 <Shunji Lin>

#ifndef KNAPSACK_RECURSIVE_HPP
#define KNAPSACK_RECURSIVE_HPP

#include <vector>
#include <unordered_map>

namespace knapsack {
    struct Subproblem {
	Subproblem(int n_items, int weight) : n_items(n_items), weight(weight) {}
	int n_items;
	int weight;
    };

    struct SubproblemHash {
	// adapted from boost hash_combine
	std::size_t operator()(const Subproblem& subproblem) const {
	    return subproblem.n_items + 0x9e3779b9 + (subproblem.weight << 6) + (subproblem.weight >> 2);
	}

    };

    bool operator==(const Subproblem& sub1, const Subproblem& sub2) {
	return sub1.n_items == sub2.n_items && sub1.weight == sub2.weight;
    }
    
    struct Item {
	Item(int value, int weight) : value(value), weight(weight) {}
	int value;
	int weight;
    };
    
    class KnapsackRecursive {
	std::vector<Item> items;
	int max_weight;
	std::unordered_map<Subproblem, int, SubproblemHash> subproblem_cache;

	int solve_subproblem(int n_items, int weight) {
	    if (n_items == 0 || weight == 0) return 0;
	    auto cached_solution = subproblem_cache.find(Subproblem(n_items, weight));
	    if (cached_solution != subproblem_cache.end()) return cached_solution->second;
	    
	    int nth_item_value = items[n_items-1].value;
	    int nth_item_weight = items[n_items-1].weight;

	    int solution;

	    if (nth_item_weight > weight) {
		solution = solve_subproblem(n_items - 1, weight);
	    } else {
		solution = std::max(solve_subproblem(n_items - 1, weight),
				    solve_subproblem(n_items - 1, weight - nth_item_weight)
				    + nth_item_value);
	    }
	    subproblem_cache.emplace(std::make_pair(Subproblem(n_items, weight), solution));
	    return solution;
	}
	
    public:
	KnapsackRecursive(std::vector<Item> items, int max_weight) :
	    items(items),
	    max_weight(max_weight) {}

	int optimalSolution() {
	    return solve_subproblem(items.size(), max_weight);

	}
	
    };
};

#endif
