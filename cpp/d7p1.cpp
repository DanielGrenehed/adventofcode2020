// Author Daniel Grenehed 07 12 2020
 #include "util.hpp"


class Bag {
public:
    std::string color;
    std::vector<std::string> rules;

    Bag(std::string c) {
        color = c;
    }

    bool containsColor(std::string c) {
        for (int i = 0; i < rules.size(); i++) if (rules[i] == c) return 1;
        return 0;
    }

    void print() {
        std::cout << "Bag of color " << color << " contains ";
        for (int i = 0; i < rules.size(); i++) {
            std::cout << rules[i] << ", ";
        }
        std::cout << " bags" << std::endl;
    }
};

std::vector<std::string> addRules(std::string line) {
    std::vector<std::string> output;
    std::vector<std::string> s_line = split(line, ' ');
    try {
        if (s_line.size() % 4 != 0) return output;
        //print_vector(s_line);
        for (int i = 0; i < s_line.size(); i+=4) {
            std::string color = s_line[i+1] + " " + s_line[i+2];
            output.push_back(color);
        }
    } catch (...) {
        std::cout << "in addRules catch" << std::endl;
    }
    return output;
}


std::vector<Bag> readRules(std::vector<std::string> text_rules) {
    std::vector<Bag> rules;
    for (int i = 0; i < text_rules.size(); i++) {
        std::string line = text_rules[i];
        std::vector<std::string> bnarules = splitOnce(line, " bags contain");
        Bag bag(bnarules[0]);
        bag.rules = addRules(bnarules[1]);
        bag.print();
        rules.push_back(bag);
    }
    return rules;
}

bool vecContainsColor(std::vector<std::string> vec, std::string color) {
    for (int i = 0; i < vec.size(); i++) if (vec[i] == color) return 1;
    return 0;
}


int countPossibleBags(std::vector<std::string> &colors, std::vector<Bag> rules) {
    int count = 0;
    //std::cout << " in rec for " << colors[colors.size()-1];
    for (int i = 0; i < colors.size(); i++) {

        for (int j = 0; j < rules.size(); j++) {

            if (rules[j].containsColor(colors[i])) {
                if (!vecContainsColor(colors, rules[j].color)) {
                    colors.push_back(rules[j].color);
                }
            }

        }
    }
    return colors.size()-1;
}

int main() {
    std::vector<std::string> input = readLines("../input_d7");
    std::vector<Bag> rules = readRules(input);
    std::vector<std::string> colors;
    colors.push_back("shiny gold");
    int count = countPossibleBags(colors, rules);
    std::cout << count << " bags could contain your bag." << std::endl;
}
