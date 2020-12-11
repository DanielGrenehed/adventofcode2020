// Author Daniel Grenehed 11 12 2020
#include "util.hpp"

bool isOccupied(int step_x, int step_y, int x, int y, std::vector<std::string> map) {
    int max_x = map[0].size(), max_y = map.size();
    x += step_x;
    y += step_y;
    while (x >= 0 && x < max_x && y >= 0 && y < max_y) {
        char tile = map[x][y];
        if (tile == '#') return 1;
        if (tile == 'L') return 0;
        x += step_x;
        y += step_y;
    }
    return 0;
}

int adjecentOccupied(int x, int y, std::vector<std::string> map) {
    int count = 0;
    for (int i = -1; i < 2; i++) {
        if (isOccupied(i, -1, x, y, map)) count++;
        if (isOccupied(i, 1, x, y, map)) count++;
        if (i != 0 && isOccupied(i, 0, x, y, map)) count++;
    }
    return count;
}

bool getNextRoundMap(std::vector<std::string> &map) {
    std::vector<std::string> updated_map = map; // get floor
    bool same = 1; // if change appeared, set to 0
    int max_x = map[0].size();
    for (int x = 0; x < max_x; x++) {
        for (int y = 0; y < map.size(); y++) {
            char tile = map[x][y];
            if (tile == '.') continue;

            int occupied = adjecentOccupied(x, y, map);
            if (tile == 'L' && occupied == 0) {
                updated_map[x][y] = '#';
                same = 0;
            } else if (tile == '#' && occupied >= 5) {
                updated_map[x][y] = 'L';
                same = 0;
            }
        }

    }
    map = updated_map;
    return same;
}

int countOccupied(std::vector<std::string> map) {
    int count = 0, max_x = map[0].size();
    for (int x = 0; x < max_x; x++) {
        for (int y = 0; y < map.size(); y++) {
            if (map[x][y] == '#') count++;
        }
    }
    return count;
}

int main() {
    std::vector<std::string> map = readLines("../input_d11");
    while (!getNextRoundMap(map)); // print_vector(map);//for visualisation 
    int count = countOccupied(map);
    std::cout << "Number of occupied seats is " << count << std::endl;
}
