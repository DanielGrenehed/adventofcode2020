// Autor Daniel Grenehed 05 12 2020

#include "util.hpp"


class Seat {
public:
    int row, col;
    Seat() {
        row = 0;
        col = 0;
    }

    void calculateSeat(std::string line) {
        int low_row = 0, high_row = 127, low_col = 0, high_col = 7;
        for (int i = 0; i < line.size(); i++) {
            char c = line[i];
            if (c == 'F') {
                high_row -= ((high_row-low_row) /2);
            } else if (c == 'B') {
                low_row += (high_row-low_row)/2;
            } else if (c == 'R') {
                low_col += (high_col-low_col)/2;
            } else if (c == 'L') {
                high_col -= ((high_col-low_col)/2);
            } else {
                // panic! (invalid string)
            }
        }
        std::cout << "lr " << low_row << " hr " << high_row << "  lc " << low_col << " hc " << high_col << std::endl;
        row = high_row;
        col = high_col;
    }

    int getId() {
        return row * 8 + col;
    }
};


int getHighestId(std::vector<std::string> input) {
    int highest = 0;
    print_vector(input);
    for (int i=0; i < input.size(); i++) {
        Seat s;
        s.calculateSeat(input[i]);
        int id = s.getId();
        if (id > highest) highest = id;
    }
    return highest;
}

int main() {
    int id = getHighestId(readLines("../input_d5"));
    std::cout << "Calculated " << id << " to be the highest possible id in input"<< std::endl;
}
