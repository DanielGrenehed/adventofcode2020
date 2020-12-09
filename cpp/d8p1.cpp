// Author Daniel Grenehed 08 12 2020
#include "util.hpp"

bool isInVec(int v, std::vector<int> vec) {
    for (int i = 0; i < vec.size(); i++) if (vec[i] == v) return 1;
    return 0;
}

int getAccumulatorValue(std::vector<std::string> program) {
    int iterator = 0, accumulator = 0;
    std::vector<int> lines_operated;
    while (!isInVec(iterator, lines_operated) && iterator < program.size()) {
        lines_operated.push_back(iterator);

        std::vector<std::string> op_v = split(program[iterator], ' ');
        std::string operation = op_v[0];
        int value = std::stoi(op_v[1]);

        if (operation == "nop") {
            iterator++;
        } else if (operation == "jmp") {
            iterator += value;
        } else if (operation == "acc") {
            accumulator += value;
            iterator++;
        }

    }
    return accumulator;
}

int main() {
    int acc = getAccumulatorValue(readLines("../input_d8"));
    std::cout << "Accumulator is " << acc << " before infinite loop" << std::endl;
}
