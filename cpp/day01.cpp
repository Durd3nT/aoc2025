#include <print>
#include <fstream>
#include <vector>

void readInput(const std::string filepath, std::vector<int> & data) {
    std::ifstream inFile(filepath);
    std::string val;

    if (inFile.is_open()) {
        while (getline(inFile, val)) {
            std::string dir = val.substr(0, 1);
            if (dir == "R") {
                data.push_back(std::stoi(val.substr(1)));
            } else if (dir == "L") {
                data.push_back(- std::stoi(val.substr(1)));
            }
        }
    } else { std::println("ERROR: could not open file"); }
}

/** 
 * On a dial 0-99, counts how often the 0 is passed if the dial is turned by the values in
 * `clicks`, and how often the dial stops at 0, given it is initiated at the value 50.
 * 
 * @param clicks: list of values by which to turn the dial
 * @param pos_init: initial position of dial
 * @param zero_cnt: counts how often dial stops at zero position
 * @param zero_passed_cnt: counts how often dial passes zero position without stopping
*/
void countZeros(
    const std::vector<int> & clicks,
    const int & pos_init,
    int & zero_cnt,
    int & zero_passed_cnt
) {

    int pos = pos_init;

    for (auto i: clicks) {
        int new_pos = ((pos + i) % 100 + 100) % 100; // true modulo instead of remainder
        int full_rotations = std::abs(i) / 100;

        zero_passed_cnt += full_rotations;
        if (((new_pos > pos and i < 0) or (new_pos < pos and i > 0))
            and (new_pos != 0)
            and (pos != 0))
        {
            zero_passed_cnt += 1;
        }

        pos = new_pos;
        if (pos == 0) {
            zero_cnt += 1;
        }
    }
}

int main() {
    std::string filepath = "../input/input01.txt";
    std::vector<int> clicks;

    readInput(filepath, clicks);

    int dial_init = 50;
    int zero_cnt = 0;
    int zero_passed_cnt = 0;
    countZeros(clicks, dial_init, zero_cnt, zero_passed_cnt);

    std::println("Dial landed on / passed zero: {} / {}", zero_cnt, zero_passed_cnt);
    std::println("Total: {}", zero_cnt + zero_passed_cnt);
}