// Author Daniel Grenehed 10 12 2020
#include "util.hpp"

int getMultipliedDiff(std::vector<int> numbers) {
    quicksort(numbers);
    int ones = 0, threes = 1, last = 0;
    for (int i = 0; i < numbers.size(); i++) {
        int current = numbers[i];
        if (current - last == 1) ones++;
        else if (current - last == 3) threes++;
        last = current;
    }
    return ones*threes;
}

int main() {
    int result = getMultipliedDiff(readIntPerLine("../input_d10"));
    std::cout << "Multiplying differences of one and three together gets us " << result << std::endl;
}
