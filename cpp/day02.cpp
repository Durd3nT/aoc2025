#include <print>
#include <fstream>
#include <vector>
#include <unordered_set>
#include <ranges>
#include <string>
#include <numeric>

#include "aoc_utils.hpp"

void read_input(const std::string filepath, std::vector<std::vector<long long>> & data) {
    std::ifstream inFile(filepath);
    std::string val;

    if (inFile.is_open()) {
        while (getline(inFile, val)) {
            std::vector<std::string> range_list = split(val, ",");
            for (auto r: range_list) {
                std::vector<std::string> range = split(r, "-");
                data.push_back(std::vector<long long>{std::stoll(range[0]), std::stoll(range[1])});
            }
        }
    } else { std::println("ERROR: could not open file"); }
}

/** 
 * Filters ranges of integers for integers consisting of repeated blocks of numbers, e.g.,
 * 212121, 13451345, 111, etc. max repeats. The function returns the sum of all found integers.
 * 
 * @param ranges: ranges of integers (inclusive) within which we check for patterned integers
 * @param max_repeats: maximum repetitions of blocks / patterns we look for in all strings.
 *  If negative, it is set to the number of digits in the integer
*/
long long find_string_patterns(
    const std::vector<std::vector<long long>> & ranges,
    const int & max_repeats
) {
    std::unordered_set<long long> invalid;
    
    for (const auto & range: ranges) {
        for (const long long & i: std::views::iota(range[0], range[1] + 1)) {
            std::string ss = std::to_string(i);
            std::string_view s = std::string_view(ss);
            int len = s.length();
            int repeats = max_repeats;

            if (max_repeats > len or max_repeats < 0) {
                repeats = len;
            }
            
            for (const int & k: std::views::iota(2, repeats + 1)) {
                // k = number of repeating blocks
                if (len % k != 0)
                    continue;

                bool blocks_match = true;
                int block_len = len / k;

                // check for each block of string that is of length block_len if it is
                // equivalent to the first block in the string
                for (int j = block_len; j < len; ++j) {
                    if (s[j] != s[j % block_len]) {
                        blocks_match = false;
                        break;
                    }
                }

                if (blocks_match) {
                    // only if all blocks match the first
                    invalid.insert(i);
                }
            }
        }
    }
    long long sum = std::accumulate(invalid.begin(), invalid.end(), 0LL); // init (0) has to be long long too

    return sum;
}

int main() {
    std::string filepath = "../input/input02.txt";
    std::vector<std::vector<long long>> ranges;

    read_input(filepath, ranges);

    long long sum_double_invalids, sum_all_invalids;
    sum_double_invalids = find_string_patterns(ranges, 2);
    sum_all_invalids = find_string_patterns(ranges, -1);

    std::println("sum of IDs with double patterns (part 1): {}", sum_double_invalids);
    std::println("sum of IDs with multi patterns (part 2): {}", sum_all_invalids);
}

