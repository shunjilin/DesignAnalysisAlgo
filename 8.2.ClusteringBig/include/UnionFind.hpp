//Copyright 2016 <Shunji Lin>

#ifndef UNIONFIND_HPP
#define UNIONFIND_HPP

#include <vector>
#include <map>
#include <cassert>

namespace unionfind {

    struct UFEntry {
	UFEntry() : parent(0), rank(0) {}
	UFEntry(int id) : parent(id), rank(0) {}
	int parent;
	unsigned rank;
    };

    class UnionFind {
	std::map<int, UFEntry> entries;
	std::size_t n_groups;
    
	std::size_t rank(int i) const {
	    return entries.at(i).rank;
	}
    public:
	UnionFind() {}
	UnionFind(const std::vector<int>& node_ids) {
	    // might have duplicates!
	    for (auto node_id : node_ids) {
		entries[node_id] = UFEntry(node_id);
	    }
	    n_groups = entries.size();
	}
    
	std::size_t size() const {
	    return entries.size();
	}
	
	
	std::size_t nGroups() const {
	    return n_groups;
	}
	
	int find(int i) {
	    assert(entries.find(i) != entries.end());
	    std::vector<int> indexes_to_update;
	    while (entries[i].parent != i) {
		indexes_to_update.emplace_back(i);
		i = entries[i].parent;
	    }
	    for (auto index : indexes_to_update) {
		entries[index].parent = i;
	    }
	    return i;
	}
	
	
	void merge(int i, int j) {
	    auto parent_i = find(i);
	    auto parent_j = find(j);
	    if (parent_i == parent_j) return; //already merged
	    if (rank(parent_i) > rank(parent_j)) {
		entries[parent_j].parent = parent_i;
	    } else {
		entries[parent_i].parent = parent_j;
		if (rank(parent_i) == rank(parent_j)) entries[parent_j].rank += 1;
	    }
	    --n_groups;
	}
	
    
    };
    
};

#endif
