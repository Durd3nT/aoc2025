#include <print>
#include <fstream>
#include <vector>
#include <cstdint>
#include <ranges>


void readInput(const std::string filepath, std::vector<std::string> & data) {
    std::ifstream inFile(filepath);
    std::string val;

    if (inFile.is_open()) {
        while (getline(inFile, val)) {
            data.push_back(val);
        }
    } else { std::println("ERROR: could not open file"); }
}

/**
 * In a string of digits, finds the digits that will yield the largest possible integer when
 * combined. Note that the order of digits cannot be changed. For example, in 818181911112111,
 * the largest combination of three digits is 921 when respecting the order of digits (i.e.,
 * disallowing 988 as the 8s would have to moved to the right of the 9)
 * 
 * @param b_string: string of digits
 * @param num_digits: How many digits to maximize
 */
int64_t maxDigitsString(std::string_view s, const int num_digits) {
    int len_s = s.length();
    std::vector<char> max_digits(num_digits);
    std::vector<int> max_idx(num_digits, 0);

    for (const int k: std::views::iota(0, num_digits)) {
        int start;
        if (k == 0) {
            start = 0;
        } else {
            start = max_idx[k - 1] + 1;
        }
        for (const int i: std::views::iota(start, len_s - num_digits + k + 1)) {
            if (s[i] > max_digits[k]) {
                max_digits[k] = s[i];
                max_idx[k] = i;
            }
        }
    }

    int64_t max_int = 0;
    for (char c: max_digits) {
        max_int = max_int * 10 + (c - '0');
    }

    return max_int;
}

int64_t totalJolts(const std::vector<std::string> & data, const int num_digits) {
    int64_t jolts = 0;
    for (auto s: data) {
        jolts += maxDigitsString(std::string_view(s), num_digits);
    }
    return jolts;
}


int main() {
    std::string filepath = "../input/input03.txt";
    std::vector<std::string> data;

    readInput(filepath, data);
    int64_t jolts = totalJolts(data, 2);
    int64_t big_jolts = totalJolts(data, 12);

    std::println("maximum joltage with 2 batteries (part 1): {}", jolts);
    std::println("maximum joltage with 12 batteries (part 2): {}", big_jolts);
}