//Copyright 2016 <Shunji Lin>

#ifndef UNIONFIND_HPP
#define UNIONFIND_HPP

#include <vector>
#include <cassert>
#include <cstddef>

namespace unionfind {

struct UFEntry {
    UFEntry() : parent(0), rank(0) {}
    UFEntry(size_t parent) : parent(parent), rank(0) {}
    std::size_t parent;
    std::size_t rank;
};

class UnionFind {
    std::vector<UFEntry> entries;
    std::size_t n_groups;
    
    std::size_t rank(std::size_t i) const {
	assert(i >= 0 && i < size());
	return entries[i].rank;
    }
public:
    UnionFind() {}
    UnionFind(std::size_t size) : entries(size), n_groups(size) {
	for (std::size_t i = 0; i < size; ++i) {
	    entries[i] = UFEntry(i);
	}
    }
    
    std::size_t size() const {
	return entries.size();
    }

    std::size_t nGroups() const {
	return n_groups;
    }
    
    std::size_t find(std::size_t i) {
	assert(i >= 0 && i < size());
	std::vector<size_t> indexes_to_update;
	while (entries[i].parent != i) {
	    indexes_to_update.emplace_back(i);
	    i = entries[i].parent;
	}
	for (auto index : indexes_to_update) {
	    entries[index].parent = i;
	}
	return i;
    }
    
    void merge(std::size_t i, std::size_t j) {
	auto parent_i = find(i);
	auto parent_j = find(j);
	if (rank(parent_i) > rank(parent_j)) {
	    entries[parent_j] = parent_i;
	} else {
	    entries[parent_i] = parent_j;
	    if (rank(parent_i) == rank(parent_j)) entries[parent_j].rank += 1;
	}
	--n_groups;
    }
    
};
    
};

#endif
