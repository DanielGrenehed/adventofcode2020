// Author Daniel Grenehed 15 12 2020
#include "util.hpp"

int rambunctiousRecitation(std::vector<int> start, int end_it) {
    std::vector<int> sequence(end_it, -1);
    for (int i = 0; i < start.size()-1; i++) sequence[start[i]] = i;

    int last_val = start[start.size()-1];
    for (int i = start.size(); i < end_it; i++) {
        int pos = sequence[last_val];
        int value;
        if (pos == -1) value = 0;
        else value = i-1 - pos;
        sequence[last_val] = i-1;
        last_val = value;
    }
    return last_val;
}

int main() {
    std::vector<int> start_sequence = readCommaSeperatedInts("../input_d15");
    int result = rambunctiousRecitation(start_sequence, 30000000);
    std::cout << "The value of iteration 30000000 should be " << result << std::endl;
}
