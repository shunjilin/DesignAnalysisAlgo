//Copyright 2016 <Shunji Lin>

#ifndef HUFFMANTREE_HPP
#define HUFFMANTREE_HPP

#include <memory>
#include <vector>
#include <cassert>
#include <iostream>
#include <queue>

namespace huffmantree {

    template <class T>
    struct Entry {
	T character;
	int weight;
	Entry(T character, int weight) : character(character), weight(weight) {}
    };

    template <class T>
    struct TreeNode {
	T character; // only for leaf nodes;
	int weight;
	// shared pointer due to limitations of priority queue,
	// TODO: implement priority queue that supports move operations?
	std::shared_ptr<TreeNode<T> > left, right;
	TreeNode(const Entry<T> &entry) :
	    character(entry.character),
	    weight(entry.weight) {}
	// merge nodes
	TreeNode(TreeNode<T>&& node1, TreeNode<T>&& node2) :
	    weight(node1.weight + node2.weight),
	    left(std::make_shared<TreeNode<T> >(std::move(node1))),
	    right(std::make_shared<TreeNode<T> >(std::move(node2))) {}
    };

    template<class T>
    struct TreeNodeMinPQComparator {
	bool operator()(const TreeNode<T>& lhs, const TreeNode<T>& rhs) {
	    return lhs.weight > rhs.weight;
	}
    };

    template <class T>
    struct HuffmanTree {
	std::priority_queue<TreeNode<T>,
			    std::vector<TreeNode<T> >,
			    TreeNodeMinPQComparator<T> > minPQ;
	
	HuffmanTree() {}
	HuffmanTree(const std::vector<Entry<T> >&entries) :
	    minPQ(entries.begin(), entries.end()) {}

	void merge() {
	    assert(minPQ.size() > 1);
	    auto min1 = minPQ.top();
	    minPQ.pop();
	    auto min2 = minPQ.top();
	    minPQ.pop();
	    minPQ.emplace(TreeNode<T>(std::move(min1), std::move(min2)));
	}

	void mergeAll() {
	    while (minPQ.size() > 1) {
		merge();
	    }
	}

	int minDepth() const {
	    assert(minPQ.size() == 1);
	    return minDepthAux(std::make_shared<TreeNode<T> > (minPQ.top()));
	}

	int minDepthAux(std::shared_ptr<TreeNode<T> > node_ptr) const {
	    if (node_ptr == nullptr) return -1;
	    return std::min(minDepthAux(node_ptr->left), minDepthAux(node_ptr->right)) + 1;

	}

	int maxDepth() const {
	    assert(minPQ.size() == 1);
	    return maxDepthAux(std::make_shared<TreeNode<T> > (minPQ.top()));

	}

	int maxDepthAux(std::shared_ptr<TreeNode<T> > node_ptr) const {
	    if (node_ptr == nullptr) return -1;
	    return std::max(maxDepthAux(node_ptr->left), maxDepthAux(node_ptr->right)) + 1;
	}
	
    };


    
};

#endif
