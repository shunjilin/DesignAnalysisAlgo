//Copyright 2016 <Shunji Lin>

#ifndef HUFFMANCODING_HPP
#define HUFFMANCODING_HPP

#include <vector>
#include "HuffmanTree.hpp"

using namespace huffmantree;

namespace huffmancoding {

    template <class T>
    class HuffmanCoding {
	HuffmanTree<T> tree;
    public:
	HuffmanCoding() {}
	HuffmanCoding(std::vector<Entry<T> > &entries) :
	    tree(entries) {
	    tree.mergeAll();
	}

	int minLength() const {
	    return tree.minDepth();
	}

	int maxLength() const {
	    return tree.maxDepth();
	}   
    };

    
};

#endif
