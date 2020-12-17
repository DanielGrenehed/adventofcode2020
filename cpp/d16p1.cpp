// Author Daniel Grenehed 16 12 2020
#include "util.hpp"

class Range {
public:
    int min, max;
    Range(int n, int x) {
        min = n;
        max = x;
    }

    bool inRange(int i) {
        return (i <= max && i >= min);
    }

    // returns 0 if ranges did not merge
    bool extendRange(Range r) {
        if (r.min > max | r.max < min) return 0;
        if (r.min < min) min = r.min;
        if (r.max > max) max = r.max;
        return 1;
    }
};

Range getRangeFromString(std::string line) {
    std::vector<std::string> s_line = split(line, '-');
    Range r(std::stoi(s_line[0]), std::stoi(s_line[1]));
    return r;
}

std::vector<Range> getRanges(std::vector<std::string> input) {
    std::vector<Range> ranges;
    for (int i = 0; i < input.size(); i++) {
        std::string line = input[i];
        if (line == "") break; // starts with ranges, stop at first empty line
        std::vector<std::string> s_line = splitOnce(splitOnce(line, ": ")[1], " or "); // get numbers
        ranges.push_back(getRangeFromString(s_line[0]));
        ranges.push_back(getRangeFromString(s_line[1]));

    }
    return ranges;
}

std::vector<Range> mergeRanges(std::vector<Range> ranges) {
    bool merge = 1;
    while (merge && ranges.size() > 1) {
        merge = 0;
        for (int i = 0; i < ranges.size()-1; i++) {
            bool extended = ranges[i].extendRange(ranges[i+1]);
            if (extended) {
                merge = 1;
                ranges.erase(ranges.begin() + (i+1));
            }
        }
    }
    return ranges;
}

bool inRanges(std::vector<Range> ranges, int data) {
    for (int i = 0; i < ranges.size(); i++) if (ranges[i].inRange(data)) return 1;
    return 0;
}

int sumInvalidTicketData(std::vector<Range> ranges, std::vector<std::string> input) {
    int ticket_start = getLineIndex(input, "nearby tickets:");
    if (ticket_start == -1) return -1;
    ticket_start++;

    int sum = 0;
    for (int i = ticket_start; i < input.size(); i++) {
        std::vector<std::string> sequence = split(input[i], ',');
        for (int j = 0; j < sequence.size(); j++) {
            int number = std::stoi(sequence[j]);
            if (!inRanges(ranges, number)) sum += number;
        }
    }
    return sum;
}

int main() {

    std::vector<std::string> input = readLines("../input_d16");
    std::vector<Range> ranges = mergeRanges(getRanges(input));
    std::cout << "Ranges size is " << ranges.size() << std::endl;
    int sum = sumInvalidTicketData(ranges, input);
    std::cout << "got sum of " << sum << std::endl;
}
