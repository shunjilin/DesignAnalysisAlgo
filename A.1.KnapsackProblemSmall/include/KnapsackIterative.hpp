//Copyright 2016 <Shunji Lin>

#ifndef KNAPSACK_ITERATIVE_HPP
#define KNAPSACK_ITERATIVE_HPP

#include <vector>

namespace knapsack {
    struct Item {
	Item(int value, int weight) : value(value), weight(weight) {}
	int value;
	int weight;
    };
    
    class KnapsackIterative {
	std::vector<Item> items;
	int max_weight;
	// row is n items included, col is weight limit
	std::vector<std::vector<int> > table;
	bool solved;

	void solve() {
	    if (solved) return;
	    for (int n = 1, size = table.size(); n < size; ++n) {
		int value = items[n-1].value;
		int weight = items[n-1].weight;
		for (int w = 1; w <= max_weight; ++w) {
		    if (weight > w) {
			table[n][w] = table[n-1][w];
		    } else {
			table[n][w] = std::max(table[n-1][w],
					       table[n-1][w-weight] + value);
		    }
		}
	    }
	    solved = true;
	}
	
    public:
	KnapsackIterative(std::vector<Item> items,
		      int max_weight) :
	    items(items),
	    max_weight(max_weight),
	    table(items.size() + 1, std::vector<int>(max_weight + 1)),
	    solved(false) {}

	int optimalSolution() {
	    if (!solved) solve();
	    return table[items.size()][max_weight];
	}

    };
};

#endif
