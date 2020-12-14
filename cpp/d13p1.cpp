// Author Daniel Grenehed 13 12 2020
#include "util.hpp"

std::vector<int> getIDs(std::string line) {
    std::vector<int> ids;
    std::vector<std::string> s_line = split(line, ',');
    for (int i = 0; i < s_line.size(); i++) {
        std::string current = s_line[i];
        if (current[0] == 'x') continue;
        ids.push_back(std::stoi(current));
    }
    return ids;
}

int getSoonest(int mtime, std::vector<int> ids) {
    int sid = 0, soonest = -1;
    for (int i = 0; i < ids.size(); i++) {
        int n_dep = ((mtime)/ids[i])*ids[i] + ids[i];
        if (soonest == -1 || n_dep < soonest) {
            soonest = n_dep;
            sid = ids[i];
        }
    }
    return (soonest - mtime) * sid;
}

int main() {
    std::vector<std::string> input = readLines("../input_d13");
    print_vector(input);
    int target = std::stoi(input[0]);
    std::cout << target << std::endl;
    std::vector<int> ids = getIDs(input[1]);

    int res = getSoonest(target, ids);
    std::cout << "Id of erliest buss times wait time is " << res << std::endl;
}
