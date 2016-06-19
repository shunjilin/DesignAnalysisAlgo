#include <iostream>
#include <vector>
#include "inversions.h"



int main() {
    std::vector<int> int_vec;

    int input;
    printf("test\n");
    while (std::cin >> input) {
        int_vec.emplace_back(input);
    }
    std::vector<int> output_vec(int_vec.size());

    merge_sort(int_vec, output_vec);

    // print sorted sequence
    for (size_t i = 0, end = int_vec.size() ; i < end ; ++i) {
        printf("%d\n", output_vec[i]);
    }
    print_inversions();
    return 0;
}