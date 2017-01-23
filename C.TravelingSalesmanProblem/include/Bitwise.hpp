#ifndef BITWISE_HPP
#define BITWISE_HPP

#include <vector>

namespace bitwise {

    int countSetBits(int bits) {
	int count = 0;
	while (bits !=0 ) {
	    bits &= (bits - 1);
	    ++count;
	}
	return count ;
    }

    bool isBitSetAtIndex(int bits, int index) { // index from right
	return (bits & (1 << index)) != 0;
    }

    int setBitAtIndex(int bits, int index) { // index from right
	int mask = 1 << index;
	return bits ^ mask;
    }


    int offsetByOneAndSetOne(int bits) {
	bits <<= 1;
	bits += 1;
	return bits;
    }

    int bitVecToBits(std::vector<bool> bitVec) {
	int bits = 0;
	if (bitVec[0]) bits = 1;
	for (int i = 1, size = bitVec.size(); i < size; ++i) {
	    if (bitVec[i]) {
		bits <<= 1;
		bits += 1;
	    } else {
		bits <<= 1;
	    }
	}
	return bits;
    }

    void kSubsetAux(std::vector<std::vector<bool> > &subsets,
		    std::vector<bool>& bits, std::size_t index, std::size_t k) {
	if ((bits.size() - index) < k) return;
	if (k == 0) {
	    subsets.emplace_back(bits);
	    return;
	}
	kSubsetAux(subsets, bits, index+1, k); // omit index
	bits[index] = true;
	kSubsetAux(subsets, bits, index+1, k-1); // include index
	bits[index] = false;
    }

    void kSubset(std::vector<std::vector<bool> > &subsets, int n, int k) {
	std::vector<bool> bits(n);
	kSubsetAux(subsets, bits, 0, k);
    }

	
    
    

};

#endif
