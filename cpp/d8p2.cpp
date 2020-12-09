// Author Daniel Grenehed 08 12 2020
#include "util.hpp"

class Result {
public:
    int value;
    bool ok;
    Result() {
        value = 0;
        ok = 0;
    }
    Result(int v) {
        value = v;
        ok = 1;
    }
};

bool isInVec(int v, std::vector<int> vec) {
    for (int i = 0; i < vec.size(); i++) if (vec[i] == v) return 1;
    return 0;
}

Result getAccumulatorValue(std::vector<std::string> program) {
    int iterator = 0, accumulator = 0;
    std::vector<int> lines_operated;
    while (iterator < program.size()) {
        if (isInVec(iterator, lines_operated)) return Result();
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
    return Result(accumulator);
}

Result getValidCodeAccumulation(std::vector<std::string> program) {
    for (int i = 0; i < program.size(); i++) {
        std::string line = program[i], operation = line.substr(0, 3);

        if (operation == "nop") {
            program[i] = "jmp" + line.substr(3);
            Result accumulator = getAccumulatorValue(program);
            if (accumulator.ok) return accumulator;
            program[i] = line;
        } else if (operation == "jmp") {
            program[i] = "nop" + line.substr(3);
            Result accumulator = getAccumulatorValue(program);
            if (accumulator.ok) return accumulator;
            program[i] = line;
        }
    }
    return Result();
}

int main() {
    Result acc = getValidCodeAccumulation(readLines("../input_d8"));
    if (!acc.ok) return -1;
    std::cout << "Accumulator is " << acc.value << " when running through entire program" << std::endl;
}
