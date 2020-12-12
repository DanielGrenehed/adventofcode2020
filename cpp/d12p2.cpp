// Author Daniel Grenehed 12 12 2020
#include "util.hpp"

class Waypoint {
public:
    int x, y;
    Waypoint() {x=0;y=0;}
    Waypoint(int e, int s) {
        x = e;
        y = s;
    }

    void MoveNorth(int steps) { y -= steps; }
    void MoveSouth(int steps) { y += steps; }
    void MoveEast(int steps) { x += steps; }
    void MoveWest(int steps) { x -= steps; }
    void Rotate(int degrees) {
        int rotation = degrees%360;
        if (rotation == 0);
        else if (rotation == 180 || rotation == -180) {
            x = -x;
            y = -y;
        }
        else if (rotation == 90 || rotation == -270) {
            int t = x;
            x = -y;
            y = t;
        }
        else if (rotation == 270 || rotation == -90) {
            int t = x;
            x = y;
            y = -t;
        }
    }
};

class Ship {
public:
    Waypoint target;
    int x, y;

    Ship(Waypoint t) {
        target = t;
        x = 0;
        y = 0;
    }

    void Move(int steps) {
        x += target.x*steps;
        y += target.y*steps;
    }
    int Manhattan() {
        return std::abs(x) + std::abs(y);
    }
};

Ship parseInstructions(std::vector<std::string> instructions) {
    Waypoint target(10, -1);
    Ship ferry(target);
    for (int i = 0; i < instructions.size(); i++) {
        char action = instructions[i][0];
        int argument = std::stoi(instructions[i].substr(1));
        if (action == 'N') ferry.target.MoveNorth(argument);
        else if (action == 'S') ferry.target.MoveSouth(argument);
        else if (action == 'E') ferry.target.MoveEast(argument);
        else if (action == 'W') ferry.target.MoveWest(argument);
        else if (action == 'L') ferry.target.Rotate(-argument);
        else if (action == 'R') ferry.target.Rotate(argument);
        else if (action == 'F') ferry.Move(argument);
    }
    return ferry;
}
int main() {
    Ship f = parseInstructions(readLines("../input_d12"));
    std::cout << "Manhattan distance of ferry is " << f.Manhattan() << std::endl;
}
