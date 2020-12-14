// Author Daniel Grenehed 14 12 2020
#include "util.hpp"
#include <math.h>

std::string binaryString(std::uint64_t number) {
    std::string bin = "";
    for (int i = 35; i >= 0; i--) {
        std::uint64_t value = pow(2, i);
        if (number >= value) {
            bin.push_back('1');
            number -= value;
        } else {
            bin.push_back('0');
        }
    }
    return bin;
}

std::uint64_t getMaskedNumber(std::uint64_t number, std::string mask) {
    std::uint64_t new_number = 0;
    std::string s_number = binaryString(number);
    for (int i = 0; i < mask.size(); i++) {
        char bit = mask[i];
        std::uint64_t value = pow(2, 35-i);
        if (bit == '1' || (bit == 'X' && s_number[i] == '1')) {
            new_number += value;
        }
    }
    return new_number;
}

class Memory {
public:
    int location;
    std::uint64_t value;
    Memory(int l, std::uint64_t v) {
        location = l;
        value = v;
    }
};

void setMemory(int pos, std::uint64_t value, std::vector<Memory> &mem) {
    for (int i = 0; i < mem.size(); i++) {
        if (mem[i].location == pos)  {
            mem[i].value = value;
            return;
        }
    }
    Memory m(pos, value);
    mem.push_back(m);
}

std::vector<Memory> loadMemory(std::vector<std::string> operations) {
    std::vector<Memory> mem;
    std::string mask = "XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX";
    for (int i = 0; i < operations.size(); i++) {
        std::string op = operations[i];
        if (op.substr(0, 4) == "mask") {
            mask = splitOnce(op, " = ")[1];
        }
        else if (op.substr(0, 3) == "mem") {
            std::vector<std::string> op_parts = splitOnce(op.substr(4), "] = ");
            int pos = std::stoi(op_parts[0]);
            std::uint64_t value = getMaskedNumber(std::stoull(op_parts[1]), mask);
            setMemory(pos, value, mem);
        }
    }
    return mem;
}

std::uint64_t sumMemory(std::vector<Memory> mem) {
    std::uint64_t sum = 0;
    for (int i = 0; i < mem.size(); i++) {
        sum += mem[i].value;
    }
    return sum;
}

int main() {
    std::vector<std::string> ops = readLines("../input_d14");
    std::vector<Memory> mem = loadMemory(ops);
    std::uint64_t sum = sumMemory(mem);
    std::cout << "Sum of memory after doing all operations is " << sum << std::endl;
}


// not 3497 (too low)   564494924505
//                      321535994884
//                      18446744038763260932
//                      18446743830750624473
//                      13496669152158
