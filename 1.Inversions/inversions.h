//
// Created by Lin Gengxian Shunji on 19/6/16.
//

#ifndef INC_1_INVERSIONS_INVERSIONS_H
#define INC_1_INVERSIONS_INVERSIONS_H
#include <vector>



void copyback(std::vector<int> &input, const std::vector<int> &output, size_t begin, size_t end);

void merge_halves(const std::vector<int> &input, std::vector<int> &output, size_t begin, size_t middle, size_t end);

void split_merge(std::vector<int> &input, std::vector<int> &output, size_t begin, size_t end);

void merge_sort(std::vector<int> &input, std::vector<int> &output);

void print_inversions();

#endif //INC_1_INVERSIONS_INVERSIONS_H
