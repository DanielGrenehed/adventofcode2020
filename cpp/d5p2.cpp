// Autor Daniel Grenehed 05 12 2020

#include "util.hpp"
#include <stdlib.h>
// inspired from reddit


std::string replaceToBin(std::string seat) {
    std::string output;
    for (int i =0; i < seat.size(); i++) {
        if (seat[i] == 'F' || seat[i] == 'L') output.append("0");
        else if (seat[i] == 'B' || seat[i] == 'R') output.append("1");
    }
    return output;
}

int binToDec(std::string bin) {
    return strtol(bin.c_str(), NULL, 2);
}

int getId(std::string line) {
    return binToDec(replaceToBin(line));
}


int getIdOfSeat(std::vector<std::string> input) {
    const int num_seats = 127*8;
    bool seats[num_seats] = {0};
    for (int i = 0; i < input.size(); i++) seats[getId(input[i])] = 1;

    //print_boolarr(seats, num_seats);
    bool prev = 0;
    for (int i = 0; i < num_seats; i++) {
        if (seats[i] == 0) {
            if (prev) return i;// ignore leading zeros
        }
        prev = seats[i];
    }
    return 0;
}


int main() {
    int id = getIdOfSeat(readLines("../input_d5"));
    std::cout << "Calculated " << id << " to be the possible id of my seat."<< std::endl;
}
