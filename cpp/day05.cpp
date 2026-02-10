#include <print>
#include <fstream>
#include <vector>
#include <cstdint>
#include <cstddef>
#include <ranges>
#include <numeric>
#include <random>
#include <algorithm>

#include "aoc_utils.hpp"


void read_input(const std::string filepath, std::vector<std::vector<int>> & ranges, std::vector<int> & ids) {
    std::ifstream inFile(filepath);

    if (inFile.is_open()) {
        bool passed = false;
        std::string val;
        while (getline(inFile, val)) {
            if (val == "") {
                passed = true;
                continue;
            }
            if (not passed) {
                std::vector<std::string> range = split(val, "-");
                ranges.push_back(std::vector<int>{std::stoi(range[0]), std::stoi(range[1])});
            } else {
                ids.push_back(std::stoi(val));
            }
        }

    } else { std::println("ERROR: could not open file"); }
}

int random_int(int min, int max) {
    static std::mt19937 gen(std::random_device{}());
    std::uniform_int_distribution<int> dist(min, max);
    return dist(gen);
}

size_t hoare_partition(
    const std::vector<int> & A,
    std::vector<size_t> & idx,
    size_t low,
    size_t high
) {
    int pivot = A[idx[random_int(low, high)]];
    std::ptrdiff_t i = static_cast<std::ptrdiff_t>(low) - 1;
    std::ptrdiff_t j = static_cast<std::ptrdiff_t>(high) + 1;

    while (true) {
        ++i;
        while (A[idx[i]] < pivot) { ++i; }

        --j;
        while (A[idx[j]] > pivot) { --j; }

        if (i >= j) { return j; }
        
        std::iter_swap(idx.begin() + i, idx.begin() + j);
    }
    
    return 0;
}

void quicksort(
    const std::vector<int> & A,
    std::vector<size_t> & idx,
    size_t low,
    size_t high
) {
    if (low < high) {
        size_t p = hoare_partition(A, idx, low, high);
        if (p == high) { --p; }
        quicksort(A, idx, low, p);
        quicksort(A, idx, p + 1, high);
    }
}

std::vector<int> sort_vector(const std::vector<int> & A) {
    std::vector<size_t> idx(A.size());
    std::iota(idx.begin(), idx.end(), 0);
    quicksort(A, idx, 0, A.size() - 1);

    std::vector<int> sorted;
    for (const auto i: idx) {
        sorted.push_back(A[i]);
    }

    return sorted;
}

void sort_combine_ranges(
    const std::vector<std::vector<int>> & ranges,
    std::vector<std::vector<int>> & combined_ranges
) {
    std::vector<int> range_starts;
    std::vector<size_t> idx(ranges.size());
    std::iota(idx.begin(), idx.end(), 0);
    for (const auto & r: ranges) {
        range_starts.push_back(r[0]);
    }

    quicksort(range_starts, idx, 0, ranges.size() - 1);

    combined_ranges.push_back(ranges[idx[0]]);
    for (auto i : idx | std::views::drop(1)) {
        if (!combined_ranges.empty() && ranges[i][0] <= combined_ranges.back()[1]) {
            combined_ranges.back()[1] = std::max(combined_ranges.back()[1], ranges[i][1]);
        } else {
            combined_ranges.push_back(ranges[i]);
        }
    }
}

/**
 * 
 */
void filter_valid_ids(
    const std::vector<std::vector<int>> & sorted_ranges,
    const std::vector<int> & ids
) {
    
}

int main() {
    std::string filepath = "../input/test05.txt";
    std::vector<std::vector<int>> ranges;
    std::vector<int> ids;

    read_input(filepath, ranges, ids);

    std::vector<std::vector<int>> combined_ranges;
    sort_combine_ranges(ranges, combined_ranges);

    std::vector<int> sorted_ids = sort_vector(ids);

    // std::vector<int> range_starts;
    // std::vector<size_t> idx(ranges.size());
    // std::iota(idx.begin(), idx.end(), 0);
    // for (const auto r: ranges)
    // {
    //     range_starts.push_back(r[0]);
    // }

    // std::println("{}, {}, {}", ranges, range_starts, idx);

    // quicksort(range_starts, idx, 0, ranges.size() - 1);
    // std::println("{}, {}, {}", ranges, range_starts, idx);

    

    // std::println("rolls removed in first iteration (part 1): {}", roll_cnts[0]);
    // std::println("rolls removed in total (part 2): {}", tot_roll_cnts);
}