#include <print>
#include <fstream>
#include <vector>
#include <cstdint>
#include <cstddef>
#include <ranges>

#include "aoc_utils.hpp"

void readInput(
    const std::string filepath,
    std::vector<std::vector<char>> & elements
) {
    std::ifstream inFile(filepath);

    if (inFile.is_open()) {
        std::string val;
        while (getline(inFile, val)) {
            std::vector<char> lineChars;
            for (char c: val) {
                lineChars.push_back(c);
            }
            elements.push_back(lineChars);
        }

    } else { std::println("ERROR: could not open file"); }
}

int64_t processNumbers(const std::vector<std::vector<char>> & elements, const bool columnwise) {
    int64_t res = 0;

    if (columnwise) {
        std::vector<char> ops;
        for (auto c: elements.back()) {
            if (c != ' ') {
                ops.push_back(c);
            }
        }
        std::println("{}", ops);
        
        // for (size_t i = 0; i < elements.size() - 1; i++) {

        // }
       

    } else {
        char op;
        
    }

    return res;
}

int main() {
    std::string filepath = "../input/test06.txt";
    std::vector<std::vector<char>> elements;

    readInput(filepath, elements);

    std::println("{}", elements.back());
    elements.pop_back();
    std::println("{}", elements);

    int64_t sum = processNumbers(elements, false);

    // std::println("number of valid IDs (part 1): {}", num_valid_ids);
    // std::println("number of ALL valid IDs (part 2): {}", num_all_valid_ids);
}