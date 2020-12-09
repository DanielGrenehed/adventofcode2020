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


long long sumList(std::list<long long> m_list) {
    long long sum = 0;
    for (std::list<long long>::iterator it = m_list.begin(); it != m_list.end(); it++) sum += *it;
    return sum;
}

long long largest(std::list<long long> m_list) {
    long long larg = 0;
    for (std::list<long long>::iterator it = m_list.begin(); it != m_list.end(); it++) {
        if (*it > larg) larg = *it;
    }
    return larg;
}

long long smallest(std::list<long long> m_list) {
    long long small = getFromList(0, m_list);
    for (std::list<long long>::iterator it = m_list.begin(); it != m_list.end(); it++) {
        if (*it < small) small = *it;
    }
    return small;
}

long long sumLargestSmallest(std::list<long long> m_list) {
    return largest(m_list) + smallest(m_list);
}

void validateSequence(long long target, std::list<long long> &sequence) {
    while (sumList(sequence) > target) sequence.pop_front();
}

std::list<long long> getSequenceSums(long long target, std::vector<long long> numbers) {
    std::list<long long> sequence;
    for (int i = 0; i < numbers.size(); i++) {
        long long value = numbers[i];
        if (value >= target) sequence.empty();
        else {
            sequence.push_back(value);
            validateSequence(target, sequence);
            if (sumList(sequence) == target) return sequence;
        }
    }
    return sequence;
}

int main() {
    std::vector<long long> numbers = readLLongPerLine("../input_d9");
    long long target = getFirstInvalidNumber(25, numbers);
    long long sum = sumLargestSmallest(getSequenceSums(target, numbers));
    std::cout << "Largest and smallest numbers in sequence sum to " << sum << std::endl;
}
