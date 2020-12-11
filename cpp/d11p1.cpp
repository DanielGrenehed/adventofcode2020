// Author Daniel Grenehed 11 12 2020
#include "util.hpp"

int adjecentOccupied(int x, int y, std::vector<std::string> map) {
    // count '#' for the 8 adjecent positions
    int count = 0, max_x = map[0].size(), max_y = map.size();
    for (int i = x-1; i < x+2; i++) {
        if (i < 0) continue;
        if (i >= max_x) break;
        if (y-1 >= 0 && map[i][y-1] == '#') count++;
        if (y+1 < max_y &&map[i][y+1] == '#') count++;
        if (i != x && map[i][y] == '#') count++;

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
            } else if (tile == '#' && occupied >= 4) {
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
    while (!getNextRoundMap(map));
    int count = countOccupied(map);
    std::cout << "Number of occupied seats is " << count << std::endl;
}
