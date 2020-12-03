
// advent of code 2020 day one puzzle one
// author Daniel Grenehed 01 12 2020
#include <iostream>
#include "util.hpp"


int multiplyForSumN(std::vector<int> input, int n) {
    int i = 0, j, k, size = input.size();
    for (; i < size; i++) {
        int first = input[i];
        for (j=i+1; j < size; j++) {
            int second = input[j];
            if (first + second == n) {
                std::cout << first << " and " << second << " sum to " << n << std::endl;
                return (first * second);
            }
        }
    }
    std::cout << "No answer found." << std::endl;
    return 0;
}

int main() {
    int answer = multiplyForSumN(readIntPerLine("../input_d1"), 2020);
    std::cout << "Answer should be: " << answer << std::endl;
    return 0;
}
