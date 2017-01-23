#ifndef TSPDP_HPP
#define TSPDP_HPP

#include "Map.hpp"
#include "Bitwise.hpp"
#include <limits>
#include <math.h>
#include <algorithm>
#include <cassert>
#include <bitset>
using namespace map;
using namespace bitwise;

namespace tspdp {

    void kSubsetWithIndexZeroIncluded(std::vector<std::vector<bool> > &subsets,
				      int n, int k) {
	std::vector<bool> bits(n);
	bits[0] = true;
	kSubsetAux(subsets, bits, 1, k-1);
    }

    // associates index with k values (no. of included elements)
    struct IndexKPair {
	int index;
	int k;
	IndexKPair(int index) : index(index) {
	    k = countSetBits(index);
	}
	// order by increasing k 
	bool operator<(const IndexKPair& rhs) const {
	    return k < rhs.k;
	}
    };

    class TSPDP {
	Map map;
	int n_vertices;
	// size 2^n by 2^n -> bitstring index represents membership
	std::vector<std::vector<double> > dp_table;
	std::vector<IndexKPair> index_k_pairs;
	bool solved;
    public:
	TSPDP(Map map) :
	    map(map),
	    n_vertices(map.size()),
	    dp_table(pow(2, n_vertices),
		     std::vector<double>
		     (n_vertices, std::numeric_limits<double>::max())),
	    solved(false)
	{
	    // offset for fact that first index [0] will always be set
	    for (int i = 0, sz = pow(2, n_vertices-1); i < sz; ++i) {
		index_k_pairs.emplace_back(IndexKPair(i));
		index_k_pairs[i].index = offsetByOneAndSetOne(index_k_pairs[i].index);
		++index_k_pairs[i].k;
		
		//std::cerr << "index " << std::bitset<32> (index_k_pairs[i].index) << std::endl;
		//std::cerr << "k " << index_k_pairs[i].k << std::endl;
	    }
	    std::sort(index_k_pairs.begin(), index_k_pairs.end());
	}
	
	void solve() {
	    
	    if (solved) return;
	    assert(index_k_pairs[0].k == 1);
	    dp_table[index_k_pairs[0].index][0] = 0;
	    int index_k_pairs_index = 1; // skip k = 1
	    for (int k = 2; k <= n_vertices; ++k) {
		while (index_k_pairs[index_k_pairs_index].k == k) {
		    int subset_index = index_k_pairs[index_k_pairs_index].index;
		    for (int j = 1; j < n_vertices; ++j) {
			if (isBitSetAtIndex(subset_index, j)) {
			    double min_value = std::numeric_limits<double>::max();
			    for (int k = 0; k < n_vertices; ++k) {
				if (k == j || !isBitSetAtIndex(subset_index, k)) continue;
				//std::vector<bool> j_omit = subset;
				int omit_j = setBitAtIndex(subset_index, j); // omit j
				double subprob_value =
				    dp_table[omit_j][k] +
				    map.distance(k, j);
				if (subprob_value < min_value)
				    min_value = subprob_value;
			    }
			    dp_table[subset_index][j] = min_value;
			}
		    }
		    index_k_pairs_index++;
		}
	    }
	    solved = true;
	}

	double minTSPValue() {
	    if (!solved) solve();
	    std::vector<bool> full_subset(n_vertices, true);
	    double min_tour_value = std::numeric_limits<double>::max();
	    for(int j = 1; j < n_vertices; ++j) {
		double tour_value =
		    dp_table[bitVecToBits(full_subset)][j] + map.distance(j,0);
		if (tour_value < min_tour_value) min_tour_value = tour_value;
	    }
	    return min_tour_value;
	}

    };
};

#endif
