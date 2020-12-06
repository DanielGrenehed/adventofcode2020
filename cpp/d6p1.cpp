// Author Daniel Grenehed 06 12 2020

#include "util.hpp"


int countGroup(std::string group) {
    std::vector<char> answers;
    for (int i = 0; i < group.size(); i++) if (!contains(answers, group[i])) answers.push_back(group[i]);

    return answers.size();
}

int sumCounts(std::vector<std::string> groups) {
    int sum = 0;
    for (int i = 0; i < groups.size(); i++) sum += countGroup(groups[i]);
    return sum;
}

int main() {
    int count = sumCounts(getLineSeperatedSequences("../input_d6", 0));
    std::cout << "counted sum as " << count << std::endl;
}
