// advent of code 2020 day one puzzle one
// author Daniel Grenehed 02 12 2020
#include <iostream>
#include "util.hpp"

int countCharOccurance(std::string line, char c) {
    int count = 0;
    for (int i = 0; i < line.size(); i++) if (line[i] == c) count++;
    return count;
}


int passwordIsValid(std::string line) {
    std::vector<std::string> seperated_line = split(line, ' '), range = split(seperated_line[0], '-');
    int min = std::stoi(range[0]), max = std::stoi(range[1]);
    char c = seperated_line[1][0];// ignore ":"

    int charcount = countCharOccurance(seperated_line[2], c);
    return (charcount >= min && charcount <= max);
}

int countValidPasswords(std::vector<std::string> input) {
    int count = 0;
    for (std::string line: input) if (passwordIsValid(line)) count++;
    return count;
}

int main() {
    int num_valid  = countValidPasswords(readLines("../input_d2"));
    std::cout << num_valid << " valid passords " << std::endl;
}
