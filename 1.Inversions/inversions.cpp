//
// Created by Lin Gengxian Shunji on 19/6/16.
//

#include "inversions.h"

static long unsigned int n_inversions = 0;

// copyback copies entries from output to input in the specified range [begin, end)
void copyback(std::vector<int> &input, const std::vector<int> &output, size_t begin, size_t end) {
    for (size_t i = begin; i < end; ++i) {
        input[i] = output[i];
    }
}

// merge_halves merges [begin, middle) and [middle, end) in sorted order
void merge_halves(const std::vector<int> &input, std::vector<int> &output, size_t begin, size_t middle, size_t end) {
    size_t output_idx = begin, left_idx = begin, right_idx = middle;
    while (output_idx < end) {
        if (left_idx < middle && (right_idx >= end || input[left_idx] < input[right_idx])) {
            output[output_idx] = input[left_idx];
            ++left_idx;
        } else {
            output[output_idx] = input[right_idx];
            ++right_idx;
            n_inversions += (middle - left_idx);
        }
        ++output_idx;
    }
}

// split_merge recursively splits and merges
void split_merge(std::vector<int> &input, std::vector<int> &output, size_t begin, size_t end) {
    if (end - begin == 1) return;
    size_t middle = begin + (end - begin) / 2;
    split_merge(input, output, begin, middle);
    split_merge(input, output, middle, end);
    merge_halves(input, output, begin, middle, end);
    copyback(input, output, begin, end);
}

// outer merge_sort calls
void merge_sort(std::vector<int> &input, std::vector<int> &output) {
    split_merge(input, output, 0, input.size());
}

void print_inversions() {
    printf("Number of inversions is %lu\n", n_inversions);
}