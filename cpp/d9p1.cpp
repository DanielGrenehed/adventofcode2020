// Author Daniel Grenehed 09 12 2020
#include "util.hpp"
#include <list>

long long getFromList(int index, std::list<long long> m_list){
    std::list<long long>::iterator it = m_list.begin();
    for (int i=0; i < index; i++) it++;
    return *it;
}

bool containsSum(long long target, std::list<long long> numbers) {
    // for each number in number, if it sums up to target with any other number in vector return true
    for (int i = 0; i < numbers.size(); i++) {
        long long value1 = getFromList(i, numbers);
        for (int j = i+1; j < numbers.size(); j++) {
            long long value2 = getFromList(j, numbers);
            if (value1 + value2 == target) return 1;
        }
    }
    return 0;
}

std::list<long long> constructFromFirst(int preamble, std::vector<long long> numbers) {
    std::list<long long> output;
    if (preamble > numbers.size()) return output;
    for (int i=0; i < preamble; i++) output.push_back(numbers[i]);
    return output;
}

long long getFirstInvalidNumber(int preamble, std::vector<long long> numbers) {
    std::list<long long> prev = constructFromFirst(preamble, numbers);
    for (int i = preamble; i < numbers.size(); i++) {
        if (!containsSum(numbers[i], prev)) return numbers[i];
        prev.pop_front();
        prev.push_back(numbers[i]);
    }
    return 0;
}

int main() {
    long long result = getFirstInvalidNumber(25, readLLongPerLine("../input_d9"));
    std::cout << "First number not summed in preamble is " << result << std::endl;
}
