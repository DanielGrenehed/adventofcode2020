// Author Daniel Grenehed 15 12 2020
#include "util.hpp"

int getPreviousPositionInSequence(std::vector<int> sequence, int number) {
    for (int i = sequence.size()-2; i >= 0; i--) if (sequence[i] == number) return sequence.size()-1 -i;
    return -1;
}

int rambunctiousRecitation(std::vector<int> start, int end_it) {
    for (int i = start.size(); i < end_it; i++) {
        std::cout << "last value : " << start[i-1] << std::endl;
        int diff = getPreviousPositionInSequence(start, start[start.size()-1]);
        if (diff == -1) start.push_back(0);
        else start.push_back(diff);

    }
    //std::cout << "sequence size is " << start.size() << std::endl;
    return start[start.size()-1];
}

int main() {
    std::vector<int> start_sequence = readCommaSeperatedInts("../input_d15");
    int result = rambunctiousRecitation(start_sequence, 2020);
    std::cout << "The value of iteration 2020 should be " << result << std::endl;
}
