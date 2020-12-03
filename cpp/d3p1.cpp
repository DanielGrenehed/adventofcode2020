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

int main() {
    Toboggan toboggan(3, 1);
    int count = getTreesHit(toboggan, readLines("../input_d3"));
    std::cout << "Sled hit " << count << " trees." << std::endl;
}
