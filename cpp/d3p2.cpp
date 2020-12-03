// Author Daniel Grenehed 03 12 2020

#include "util.hpp"

class Toboggan {
public:
    int x, y, step_x, step_y;
    Toboggan(int sx, int sy) {
        x = 0;
        y = 0;
        step_x = sx;
        step_y = sy;
    }
    void move() {
        x += step_x;
        y += step_y;
    }
};

int didHitTree(Toboggan sled, std::string line) {
    return line[sled.x%line.size()] == '#';
}

int getTreesHit(Toboggan sled, std::vector<std::string> map) {
    int hit_count = 0;
    for (int i = 0; i < map.size(); i+= sled.step_y) {
        std::string line = map[i];
        hit_count += didHitTree(sled, line);
        sled.move();
    }
    return hit_count;
}


int multiplyTreesForSlopes(std::vector<Toboggan> sleds, std::vector<std::string> map) {
    int res = 1;
    for (int i = 0; i < sleds.size(); i++) {
        res *= getTreesHit(sleds[i], map);
    }
    return res;
}
int main() {
    std::vector<Toboggan> sleds;
    sleds.push_back(Toboggan(1, 1));
    sleds.push_back(Toboggan(3, 1));
    sleds.push_back(Toboggan(5, 1));
    sleds.push_back(Toboggan(7, 1));
    sleds.push_back(Toboggan(1, 2));
    int count = multiplyTreesForSlopes(sleds, readLines("../input_d3"));
    std::cout << "You get " << count << " if you multiply the number of trees encountered" << std::endl;
}
