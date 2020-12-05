
#ifndef UTIL_HPP
#define UTIL_HPP

#include <iostream>
#include <fstream>
#include <vector>
// vecotr reserve num.lines in  file


std::vector<int> readIntPerLine(std::string filename) {
    std::string line;
    std::vector<int> output;
    std::ifstream f(filename);
    if (f.is_open()) {
        while (getline(f, line)) output.push_back(std::stoi(line));
        f.close();
    }
    return output;
}

std::vector<std::string> readLines(std::string filename) {
    std::string line;
    std::vector<std::string> output;
    std::ifstream f(filename);
    if (f.is_open()) {
        while (getline(f, line)) output.push_back(line);
        f.close();
    }
    return output;
}

std::vector<std::string> getLineSeperatedSequences(std::string filename) {
    std::string line;
    std::vector<std::string> output;
    std::ifstream f(filename);
    if (f.is_open()) {
        std::string sequence = "";
        while (getline(f, line)) {

            if (line.size() == 0 && sequence.size() > 0) {
                output.push_back(sequence);
                sequence = "";
            } else {
                sequence.append(" "+line);
            }

        }
        if (sequence.size() != 0) {
            output.push_back(sequence);
        }

        f.close();
    }
    return output;
}

std::vector<std::string> split(std::string line, char delim) { // probably not safe for double space (or more)
        std::vector<std::string> output;
        int last_cut = 0, size = line.size();
        for (int i = 0; i < size; i++) {
            if (line[i] == delim && last_cut <= i) {
                output.push_back(line.substr(last_cut, i-last_cut));
                last_cut = i+1;
            }
        }

        if (last_cut != size) {
            output.push_back(line.substr(last_cut, size-last_cut));
        }
        return output;
}


int isHexValid(std::string input) {
    char hex[16] = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'a', 'b', 'c', 'd', 'e', 'f'};
    for (int i = 0; i < input.size(); i++) {
        int found = 0;
        for (int j = 0; j < 16; j++) if (input[i] == hex[j]) found++;
        if (!found) return 0;
    }
    return 1;
}


int isDigit(char c) {
    char digits[10]= {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9'};
    for (int i = 0; i < 10; i++) if (c == digits[i]) return 1;
    return 0;
}

int numDigits(std::string input) {
    int num = 0;
    for (int i = 0; i < input.size(); i++) {
        if (isDigit(input[i])) num++;
        else return 0;
    }
    return num;
}

int isWithin(int i, int min, int max) {
    if (i >= min && i <= max) {
        std::cout << i << " is greater than " << min << " and smaller than " << max << std::endl;
        return 1;
     }
    return 0;
}

/// debug 

void print_vector(std::vector<std::string> vec) {
        for (int i = 0; i < vec.size(); i++) {
            std::cout << " '" << vec[i] << "' ";
        }
        std::cout << std::endl;
}

void print_boolarr(bool *arr, int size) {
    for (int i = 0; i < size; i++) std::cout << " " << arr[i];
}


#endif
