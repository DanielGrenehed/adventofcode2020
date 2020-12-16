
#ifndef UTIL_HPP
#define UTIL_HPP

#include <iostream>
#include <fstream>
#include <vector>
// vecotr reserve num.lines in  file


// conversion

std::vector<std::string> split(std::string line, char delim) { // probably not safe for double space (or more)
    std::vector<std::string> output;
    int last_cut = 0, size = line.size();
    for (int i = 0; i < size; i++) {
        if (line[i] == delim) {
            if (last_cut < i) output.push_back(line.substr(last_cut, i-last_cut));
            last_cut = i+1;
        }
    }

    if (last_cut != size) {
        output.push_back(line.substr(last_cut, size-last_cut));
    }
    return output;
}

void swap(std::vector<int> &vec, int a, int b) {
    int temp = vec[a];
    vec[a] = vec[b];
    vec[b] = temp;
}

int partition(std::vector<int> &vec, int low, int high) {
    int pivot = vec[high];
    int i = (low-1);
    for (int j = low; j <= high-1; j++) {
        if (vec[j] < pivot) {
            i++;
            swap(vec, i, j);
        }
    }
    swap(vec, i+1, high);
    return (i+1);
}

void quicksort(std::vector<int> &vec, int low, int high) {
    if (low < high) {
        int pi = partition(vec, low, high);
        quicksort(vec, low, pi-1);
        quicksort(vec, pi+1, high);
    }
}

void quicksort(std::vector<int> &vec) {
    quicksort(vec, 0, vec.size()-1);
}

int find(std::string word, std::string line) {
    for (int i = 0; i < line.size(); i++) {
        if (line.substr(i, word.size()) == word) return i;
    }
    return -1;
}

std::vector<std::string> splitOnce(std::string line, std::string word) {
    std::vector<std::string> output;
    int pos = find(word, line);
    if (pos == -1) output.push_back(line);
    else if (pos == 0) output.push_back(line.substr(word.size()));
    else {
        output.push_back(line.substr(0, pos));
        output.push_back(line.substr(pos+word.size()));
    }
    return output;
}


bool contains(std::vector<char> vec, char c) {
    for (int i = 0;  i < vec.size(); i++) if (vec[i] == c) return 1;
    return 0;
}

std::vector<char> getCommonChars(std::vector<char> in1, std::vector<char> in2) {
    std::vector<char> output;
    for (int i = 0; i < in1.size(); i++) if (contains(in2, in1[i])) output.push_back(in1[i]);
    return output;
}

std::vector<char> charVectorFromString(std::string line) {
    std::vector<char> output;
    for (int i = 0; i < line.size(); i++) output.push_back(line[i]);
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


// readfile

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

std::vector<long long> readLLongPerLine(std::string filename) {
    std::string line;
    std::vector<long long> output;
    std::ifstream f(filename);
    if (f.is_open()) {
        while (getline(f, line)) output.push_back(std::stoll(line));
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

std::vector<int> readCommaSeperatedInts(std::string filename) {
    std::vector<int> numbers;
    std::string line;
    std::ifstream f(filename);
    if (f.is_open()) {
        while (getline(f, line)) {
            std::vector<std::string> sep = split(line, ',');
            for (int i = 0; i < sep.size(); i++) numbers.push_back(std::stoi(sep[i]));
        }
        f.close();
    }
    return numbers;
}

std::vector<std::string> getLineSeperatedSequences(std::string filename, bool spaced) {
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
                sequence.append(spaced ? (" "+line) : line);
            }

        }
        if (sequence.size() != 0) {
            output.push_back(sequence);
        }

        f.close();
    }
    return output;
}


#endif
