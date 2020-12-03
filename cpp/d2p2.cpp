// advent of code 2020 day one puzzle one
// author Daniel Grenehed 02 12 2020
#include "util.hpp"


int isCharX(std::string line, int pos1, int pos2, char c) {
    int matchcount = 0;
    if (pos1 < line.size() && pos1 >= 0 && line[pos1] == c) matchcount++;
    if (pos2 < line.size() && pos2 >= 0 && line[pos2] == c) matchcount++;
    return matchcount == 1;
}


int passwordIsValid(std::string line) {
    std::vector<std::string> seperated_line = split(line, ' '), range = split(seperated_line[0], '-');
    int pos1 = std::stoi(range[0])-1, pos2 = std::stoi(range[1])-1; // starting index one
    char c = seperated_line[1][0];// ignore ":"
    return isCharX(seperated_line[2], pos1, pos2, c);
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
