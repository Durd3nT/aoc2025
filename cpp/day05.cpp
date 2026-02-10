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


void read_input(
    const std::string filepath,
    std::vector<std::vector<int64_t>> & ranges,
    std::vector<int64_t> & ids
) {
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
                ranges.push_back(std::vector<int64_t>{std::stoll(range[0]), std::stoll(range[1])});
            } else {
                ids.push_back(std::stoll(val));
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
    const std::vector<int64_t> & A,
    std::vector<size_t> & idx,
    size_t low,
    size_t high
) {
    int64_t pivot = A[idx[random_int(low, high)]];
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
    const std::vector<int64_t> & A,
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

std::vector<int64_t> sort_vector(const std::vector<int64_t> & A) {
    std::vector<size_t> idx(A.size());
    std::iota(idx.begin(), idx.end(), 0);
    quicksort(A, idx, 0, A.size() - 1);

    std::vector<int64_t> sorted;
    for (const auto i: idx) {
        sorted.push_back(A[i]);
    }

    return sorted;
}

/**
 * Sort and combine ranges from a list of unsorted, overlapping ranges. Sorting is done with the
 * above quicksort. Alternatively, a built-in function can be used. Sorting and combining the
 * ranges speeds up the solution for part 1 and enables solution for part 2 with only a handful of lines.
 * 
 * @param ranges: list of all, potentially overlapping, ranges
 * @param combined_ranges: vector to store the resulting ranges
 */
void sort_combine_ranges(
    const std::vector<std::vector<int64_t>> & ranges,
    std::vector<std::vector<int64_t>> & combined_ranges
) {
    std::vector<int64_t> range_starts;
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
 * Counts how many of the IDs in `sorted_ids` fall within one of the (inclusive) ranges.
 * 
 * @param sorted_ranges: inclusive ranges of valid IDs in ascending order
 * @param sorted_ids: all IDs
 */
int64_t filter_valid_ids(
    const std::vector<std::vector<int64_t>> & sorted_ranges,
    const std::vector<int64_t> & sorted_ids
) {
    int64_t num_valid_ids = 0;

    size_t id_cnt = 0;
    size_t range_cnt = 0;

    while (id_cnt < sorted_ids.size() and range_cnt < sorted_ranges.size()) {
        if (sorted_ids[id_cnt] < sorted_ranges[range_cnt][0]) {
            ++id_cnt;
        } else if (sorted_ids[id_cnt] > sorted_ranges[range_cnt][1]) {
            ++range_cnt;
        } else if (
            (sorted_ids[id_cnt] >= sorted_ranges[range_cnt][0]) 
            and (sorted_ids[id_cnt] <= sorted_ranges[range_cnt][1])
        ) {
            ++num_valid_ids;
            ++id_cnt;
        }
    }

    return num_valid_ids;
}

/**
 * Counts the maximum possible number of valid IDs within the given ranges.
 * 
 * @param sorted_ranges: inclusive ranges of valid IDs in ascending order
 */
int64_t all_valid_ids(const std::vector<std::vector<int64_t>> & sorted_ranges) {
    int64_t num_valid_ids = 0;
    
    for (const auto & sr: sorted_ranges) {
        num_valid_ids += sr[1] - sr[0] + 1;
    }
    
    return num_valid_ids;
}

int main() {
    std::string filepath = "../input/input05.txt";
    std::vector<std::vector<int64_t>> ranges;
    std::vector<int64_t> ids;

    read_input(filepath, ranges, ids);

    std::vector<std::vector<int64_t>> combined_ranges;
    sort_combine_ranges(ranges, combined_ranges);
    std::vector<int64_t> sorted_ids = sort_vector(ids);

    int64_t num_valid_ids = filter_valid_ids(combined_ranges, sorted_ids);
    int64_t num_all_valid_ids = all_valid_ids(combined_ranges);

    std::println("number of valid IDs (part 1): {}", num_valid_ids);
    std::println("number of ALL valid IDs (part 2): {}", num_all_valid_ids);
}