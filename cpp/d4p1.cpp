// Author Daniel Grenehed 04 12 2020
#include "util.hpp"


class Passport {
public:
    std::vector<std::string> fields;
    Passport(std::vector<std::string> f) {
        fields = f;
    }
    int coveredFields(std::string sequence) {
        std::vector<std::string> s_sequence = split(sequence, ' ');
        print_vector(s_sequence);
        for (int i = 0; i < s_sequence.size(); i++) {
            std::string key = s_sequence[i].substr(0, 3);

            for (int j = 0; j < fields.size(); j++) {
                if (key == fields[j]) {
                    fields.erase(fields.begin() + j);
                    j--;
                }
            }
        }
        if (fields.size() == 0) return 1;
        else if (fields.size() == 1 && fields[0] == "cid") return 1;
        return 0;
    }
};

std::vector<std::string> getFields() {
    std::vector<std::string> fields;
    fields.push_back("byr");
    fields.push_back("iyr");
    fields.push_back("eyr");
    fields.push_back("hgt");
    fields.push_back("hcl");
    fields.push_back("ecl");
    fields.push_back("pid");
    fields.push_back("cid");
    return fields;
}

int hasFields(std::string sequence) {
    Passport p(getFields());
    return p.coveredFields(sequence);
}

int countValid(std::vector<std::string> input) {
    //print_vector(input);
    int valid = 0;
    for (int i = 0; i < input.size(); i++) {
        if (hasFields(input[i])) valid++;
    }
    return valid;
}

int main() {
    int count = countValid(getLineSeperatedSequences("../input_d4", 1));
    std::cout << "Counted " << count << " valid inputs";
}
