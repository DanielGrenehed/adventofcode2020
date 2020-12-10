// Author Daniel Grenehed 10 12 2020
// inspired by reddit

#include "util.hpp"

long countWays(std::vector<int> adaptors) {
    quicksort(adaptors);
    std::vector<long> ways;
    for (int i = 0; i < adaptors.size(); i++) {
        if (i == 1 || i == 0) ways.push_back(1);
        else {
            int cur = adaptors[i];
            long value = ((cur - adaptors[i-1] <= 3) ? ways[i-1] : 0) + ((cur - adaptors[i-2] <= 3) ? ways[i-2] : 0) + ((i>2 && cur - adaptors[i-3] <= 3) ? ways[i-3] : 0);
            ways.push_back(value);
        }
    }
    return ways[ways.size()-1];
}

int largest(std::vector<int> numbers) {
    int large = 0;
    for (int i = 0; i < numbers.size(); i++) if (numbers[i] > large) large = numbers[i];
    return large;
}

int main() {
    std::vector<int> adaptors = readIntPerLine("../input_d10");
    adaptors.push_back(0);
    adaptors.push_back(largest(adaptors) +3);
    long result = countWays(adaptors);
    std::cout << "There is " << result << " ways to connect the charger" << std::endl;
}
