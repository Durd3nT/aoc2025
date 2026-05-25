#include <print>
#include <fstream>
#include <vector>
#include <unordered_set>
#include <ranges>
#include <string>
#include <numeric>
#include <cmath>

#include "aoc_utils.hpp"


// lookup table for integer powers of 10
static constexpr int64_t pow10[] = {
    1LL,
    10LL,
    100LL,
    1'000LL,
    10'000LL,
    100'000LL,
    1'000'000LL,
    10'000'000LL,
    100'000'000LL,
    1'000'000'000LL,
    10'000'000'000LL,
    100'000'000'000LL,
    1'000'000'000'000LL,
    10'000'000'000'000LL,
    100'000'000'000'000LL,
    1'000'000'000'000'000LL,
    10'000'000'000'000'000LL,
    100'000'000'000'000'000LL,
    1'000'000'000'000'000'000LL
};

void readInput(const std::string filepath, std::vector<std::vector<int64_t>> & data) {
    std::ifstream inFile(filepath);
    std::string val;

    if (inFile.is_open()) {
        while (getline(inFile, val)) {
            std::vector<std::string> range_list = split(val, ",");
            for (auto r: range_list) {
                std::vector<std::string> range = split(r, "-");
                data.push_back(std::vector<int64_t>{std::stoll(range[0]), std::stoll(range[1])});
            }
        }
    } else { std::println("ERROR: could not open file"); }
}

int digitCount(int64_t number) {
    // count digits by dividing integer by 10 until it becomes 0
    // (since ints are always truncated, e.g., 0.1 becomes 0)
    int digits = 0;
    do { number /= 10; digits++; } while (number != 0);
    return digits;
}

bool intPatternRepeats(const int64_t number, const int max_repeats) {
    int len = digitCount(number);
    int num_repeats = max_repeats;
    if (max_repeats > len or max_repeats < 0) {
        num_repeats = len;
    }

    for (const int k: std::views::iota(2, num_repeats + 1)) {
        // k = number of repeating blocks
        if (len % k != 0) {
            continue;
        }

        int block_len = len / k;
        int64_t block = number / pow10[(len - block_len)];
        int64_t block_pow = pow10[block_len];

        int64_t rebuilt_number = 0;
        for (int i = 0; i < k; i++) {
            rebuilt_number = block + rebuilt_number * block_pow;
        }

        if (rebuilt_number == number) {
            return true;
        }
    }

    return false;
}

/** 
 * Filters ranges of integers for integers consisting of repeated blocks of numbers, e.g.,
 * 212121, 13451345, 111, etc. max repeats. The function returns the sum of all found integers.
 * 
 * @param ranges: ranges of integers (inclusive) within which we check for patterned integers
 * @param max_repeats: maximum repetitions of blocks / patterns we look for in all strings.
 *  If negative, it is set to the number of digits in the integer
*/
int64_t findPatterns(
    const std::vector<std::vector<int64_t>> & ranges,
    const int & max_repeats
) {
    std::unordered_set<int64_t> invalid;
    
    for (const auto & range: ranges) {
        for (const int64_t i: std::views::iota(range[0], range[1] + 1)) {
            bool repeats = intPatternRepeats(i, max_repeats);
            if (repeats) {
                invalid.insert(i);
            }
        }
    }

    int64_t sum = std::accumulate(invalid.begin(), invalid.end(), 0LL); // init (0) has to be long long / int64_t too

    return sum;
}

/**
 * Same as `findPatterns`, but working on strings rather than integers.
 */
int64_t findStringPatterns(
    const std::vector<std::vector<int64_t>> & ranges,
    const int & max_repeats
) {
    std::unordered_set<int64_t> invalid;
    
    for (const auto & range: ranges) {
        for (const int64_t i: std::views::iota(range[0], range[1] + 1)) {
            std::string ss = std::to_string(i);
            std::string_view s = std::string_view(ss);
            int len = s.length();
            int repeats = max_repeats;
            if (max_repeats > len or max_repeats < 0) {
                repeats = len;
            }
            
            for (const int k: std::views::iota(2, repeats + 1)) {
                // k = number of repeating blocks
                if (len % k != 0) {
                    continue;
                }

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
                    break; // no need to test more k on the same string
                }
            }
        }
    }
    int64_t sum = std::accumulate(invalid.begin(), invalid.end(), 0LL); // init (0) has to be long long / int64_t too

    return sum;
}

int main() {
    std::string filepath = "../input/input02.txt";
    std::vector<std::vector<int64_t>> ranges;

    readInput(filepath, ranges);

    int64_t sum_double_invalids, sum_all_invalids;

    sum_double_invalids = findPatterns(ranges, 2);
    sum_all_invalids = findPatterns(ranges, -1);

    std::println("sum of IDs with double patterns (part 1): {}", sum_double_invalids);
    std::println("sum of IDs with multi patterns (part 2): {}", sum_all_invalids);
}

