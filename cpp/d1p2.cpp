
// advent of code 2020 day one puzzle two
// author Daniel Grenehed 01 12 2020
#include <iostream>
#include "util.hpp"


// iterate through vector
// get next number that would sum to less than 2020
// if pos == -1; continue;
// go through the rest of the vector and find the number that would sum to 2020
// if pos == -1; continue
// multiply them together and return the result


int getPosOfNumber(std::vector<int> input, int start_pos, int max_value) {
    for (int i = start_pos; i < input.size(); i++) {
        int value = input[i];
        if (value <= max_value) return i;
    }
    return -1;
}

int multiplyForSumN(std::vector<int> input, int n) {
    int i = 0, j, k, size = input.size();
    for (; i < size; i++) {
        int first = input[i];

        for ( j= i + 1; j < size; j++) {
            int second_pos = getPosOfNumber(input, j, n-first);
            if (second_pos == -1) continue;
            int second = input[second_pos];

            for (k = second_pos + 1; k < size; k++) {
                int third_pos = getPosOfNumber(input, k, n-(first+second));
                if (third_pos == -1) continue;
                int third = input[third_pos];
                int sum = first + second + third;

                if (sum != n) continue;
                else {
                    std::cout << first << " + " << second << " + " << third << " = " << n << std::endl;
                    return (first*second*third);
                }
            }

            j= second_pos;
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
