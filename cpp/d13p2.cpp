// Author Daniel Grenehed 13 12 2020
#include "util.hpp"

class Bus {
public:
    int id, offset;
    Bus(int i, int o) {
        id = i;
        offset = o;
    }

    bool inSequence(long long target) {
        return (target >= id && (target+offset)%id == 0);
    }
};

long long getSequenceStart(std::vector<Bus> busses) {
    long long step = busses[0].id, timestamp = step;
    busses.erase(busses.begin());
    std::cout << "Step size is " << step << std::endl;
    while (timestamp > 0) {
        for (int i = 0; i < busses.size(); i++) {
            Bus bus = busses[i];
            if (bus.inSequence(timestamp)) {
                busses.erase(busses.begin() + i);
                i--;
                step *= bus.id;
                std::cout << "Step size is " << step << ", added " << bus.id << ", num_busses " << busses.size() << std::endl;
                break;
            }
        }
        if (busses.size() == 0) return timestamp;
        timestamp += step;
    }
    return 0;
}


std::vector<Bus> getBusses(std::string line) {
    std::vector<std::string> s_line = split(line, ',');
    std::vector<Bus> busses;
    for (int i = 0; i < s_line.size(); i++) {
        if (s_line[i][0] == 'x') continue;
        Bus bus(std::stoi(s_line[i]), i);
        busses.push_back(bus);
    }
    return busses;
}

int main() {
    std::vector<Bus> busses = getBusses(readLines("../input_d13")[1]);
    long long res = getSequenceStart(busses);
    std::cout << "Timestamp of sequence is " << res << std::endl;

}
