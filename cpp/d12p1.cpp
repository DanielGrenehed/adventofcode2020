// Author Daniel Grenehed 12 12 2020
#include "util.hpp"


class Ferry {
public:
    int x, y, rotation;

    Ferry() {
        x = 0;
        y = 0;
        rotation = 0;
    }

    void Rotate(int deg) {
        rotation = (deg + rotation) % 360;
    }

    void MoveForward(int steps) {
        if (rotation == 0) x += steps;
        else if (rotation == 180 || rotation == -180) x -= steps;
        else if (rotation == 90 || rotation == -270) y += steps;
        else if (rotation == 270 || rotation == -90) y -= steps;

    }

    void MoveEast(int steps) { x += steps; }
    void MoveWest(int steps) { x -= steps; }
    void MoveSouth(int steps) { y += steps; }
    void MoveNorth(int steps) { y -= steps; }

    int Manhattan() { return std::abs(x) + std::abs(y); }
};


Ferry parseInstructions(std::vector<std::string> instructions) {
    Ferry ferry;
    for (int i = 0; i < instructions.size(); i++) {
        char action = instructions[i][0];
        int argument = std::stoi(instructions[i].substr(1));
        if (action == 'N') ferry.MoveNorth(argument);
        else if (action == 'S') ferry.MoveSouth(argument);
        else if (action == 'E') ferry.MoveEast(argument);
        else if (action == 'W') ferry.MoveWest(argument);
        else if (action == 'L') ferry.Rotate(-argument);
        else if (action == 'R') ferry.Rotate(argument);
        else if (action == 'F') ferry.MoveForward(argument);
    }
    return ferry;
}

int main() {
    Ferry f = parseInstructions(readLines("../input_d12"));
    std::cout << "Manhattan distance of ferry is " << f.Manhattan() << std::endl;
}
