//Copyright 2016 <Shunji Lin>

#ifndef BITFUNCTIONS_HPP
#define BITFUNCTIONS_HPP

#include <vector>
#include <cassert>

namespace bitfunctions {
    int nOnes(int binary) {
	int count = 0;
	while (binary != 0) {
	    binary = binary & (binary - 1); // remove least significant 1
	    ++count;
	}
	return count;
    }
    
    
    int hammingDist(int u, int v) {
	return nOnes(u ^ v);
    }

    std::vector<int> distOneGreaterPermutations(int x, int n_bits) {
	//only permutations > x
	std::vector<int> permutations;
	for (int i = 0; i < n_bits; ++i) {
	    int mask = 1 << i;
	    int permutation = x ^ mask;
	    assert(hammingDist(permutation, x) == 1);
	    if (permutation > x) permutations.emplace_back(permutation);
	}
	return permutations;
    }

    std::vector<int> distTwoGreaterPermutations(int x, int n_bits) {
	//only permutations > x
	std::vector<int> permutations;
	for (int i = 0; i < n_bits - 1; ++i) {
	    int mask1 = 1 << i;
	    for (int j = i+1; j < n_bits; ++j) {
		int mask2 = 1 << j;
		int permutation = (x ^ mask1) ^ mask2;
		assert(hammingDist(permutation, x) == 2);
		if (permutation > x) permutations.emplace_back(permutation);
	    }
	}
	return permutations;
	
    }

};

#endif
