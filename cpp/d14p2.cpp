// Author Daniel Grenehed 14 12 2020 (done 15 12 2020)
#include "util.hpp"
#include <math.h>

// unsigned 8byte int to string of binary sequence
std::string ulltobs(std::uint64_t number) {
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

// string of binary sequence to unsigned 8byte int
std::uint64_t bstoull(std::string bin) {
        std::uint64_t number = 0;
        for (int i = 0; i < bin.size(); i++) if (bin[i] == '1') number += pow(2, 35-i);
        return number;
}

std::string getMaskedAdress(std::uint64_t adress, std::string mask) {
    std::string m_adress = ulltobs(adress);
    for (int i = 0; i < mask.size(); i++) {
        if (mask[i] != '0') m_adress[i] = mask[i];
    }
    return m_adress;
}

std::vector<std::uint64_t> getMemmoryAdresses(std::uint64_t adress, std::string mask) {
    std::vector<std::uint64_t> permutations;
    std::vector<std::string> unprocessed;
    unprocessed.push_back(getMaskedAdress(adress, mask)); // start with masked adress

    while (unprocessed.size() > 0) {
        std::string bin = unprocessed[0];
        bool found = 0;
        for (int i = 0; i < bin.size(); i++) {
            if (bin[i] == 'X') {
                found = 1;
                bin[i] = '1';
                unprocessed.push_back(bin);
                bin[i] = '0';
                unprocessed.push_back(bin);
                break;
            }
        }
        if (!found) permutations.push_back(bstoull(bin)); // no x in string, convert to int
        unprocessed.erase(unprocessed.begin()); // erase processed item, an item should only be processed once
    }
    return permutations;
}

class Memory {
public:
    std::uint64_t value, location;
    Memory(std::uint64_t l, std::uint64_t v) {
        location = l;
        value = v;
    }
};

void setMemory(std::uint64_t pos, std::uint64_t value, std::vector<Memory> &mem) {
    for (std::uint64_t i = 0; i < mem.size(); i++) {
        if (mem[i].location == pos)  {
            mem[i].value = value;
            return;
        }
    }
    Memory m(pos, value);
    mem.push_back(m);
}

void setMemoryForMaskedAdress(std::uint64_t adress, std::string mask, std::uint64_t value, std::vector<Memory> &mem) {
    std::vector<std::uint64_t> m_adresses = getMemmoryAdresses(adress, mask);
    for (int i = 0; i < m_adresses.size(); i++) {
        setMemory(m_adresses[i], value, mem);
    }
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
            std::uint64_t value = std::stoull(op_parts[1]);
            setMemoryForMaskedAdress(pos, mask, value, mem);
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
