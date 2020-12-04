// Author Daniel Grenehed 04 12 2020
#include "util.hpp"

int validateField(std::string key, std::string value) {
    //std::cout << "Validating " << key << " with value " << value << std::endl;
    try {
        if (key == "byr") return isWithin(std::stoi(value), 1920, 2002);
        else if (key == "iyr") return isWithin(std::stoi(value), 2010, 2020);
        else if (key == "eyr") return isWithin(std::stoi(value), 2020, 2030);
        else if (key == "hgt") {
            std::string unit = value.substr(value.size() - 2, 2);
            int height = std::stoi(value.substr(0, value.size() - 2));
            if (unit == "cm") return isWithin(height, 150, 193);
            else if (unit == "in") return isWithin(height, 59, 76);
        }
        else if (key == "hcl" && value[0] == '#') return isHexValid(value.substr(1, value.size()-1));
        else if (key == "ecl") { if (value == "amb" || value == "blu" || value == "brn" || value == "gry" || value == "grn" || value == "hzl" || value == "oth") return 1; }
        else if (key == "pid") return (numDigits(value) == 9);
        else if (key == "cid") return 1;
    } catch (...)  { return 0;}
    return 0;
}

class Passport {
public:
    std::vector<std::string> fields;
    Passport(std::vector<std::string> f) { fields = f;}

    int coveredFields(std::string sequence) {
        std::vector<std::string> s_sequence = split(sequence, ' ');
        //print_vector(s_sequence);
        for (int i = 0; i < s_sequence.size(); i++) {
            std::string line = s_sequence[i];
            std::vector<std::string> keyvalue = split(line, ':');
            if (keyvalue.size() < 2) continue;

            for (int j = 0; j < fields.size(); j++) {
                if (keyvalue[0] == fields[j]) {

                    print_vector(keyvalue);
                    if (validateField(keyvalue[0], keyvalue[1])) {
                        fields.erase(fields.begin() + j);
                        j--;
                        std::cout << "valid field" << std::endl;
                    }
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
    int count = countValid(getLineSeperatedSequences("../input_d4"));
    std::cout << "Counted " << count << " valid inputs";
}
