
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
        while (getline(f, line)) {
            output.push_back(std::stoi(line));
        }
        f.close();
    }
    return output;
}

std::vector<std::string> readLines(std::string filename) {
    std::string line;
    std::vector<std::string> output;
    std::ifstream f(filename);
    if (f.is_open()) {
        while (getline(f, line)) {
            output.push_back(line);
        }
        f.close();
    }
    return output;
}

std::vector<std::string> split(std::string line, char delim) {
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


void print_vector(std::vector<std::string> vec) {
        for (int i = 0; i < vec.size(); i++) {
            std::cout << " '" << vec[i] << "' ";
        }
        std::cout << std::endl;
}

#endif
