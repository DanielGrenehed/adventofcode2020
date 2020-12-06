// Author Daniel Grenehed 06 12 2020

#include "util.hpp"


int allHasCommon(std::vector<std::string> group) {

    print_vector(group);
    std::vector<char> common = charVectorFromString(group[0]);
    for (int i = 1; i < group.size(); i++) common = getCommonChars(charVectorFromString(group[i]), common);
    return common.size();

}

int sumCounts(std::vector<std::string> groups) {
    int sum = 0;
    for (int i = 0; i < groups.size(); i++) sum += allHasCommon(split(groups[i], ' '));
    return sum;
}

int main() {
    int count = sumCounts(getLineSeperatedSequences("../input_d6", 1));
    std::cout << "counted sum as " << count << std::endl;
}
