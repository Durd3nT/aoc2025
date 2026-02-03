import time
start_time = time.time()
import random
# import numpy as np

def read_inputs(filepath):
    """
    Reads data from input file in the respective format.
    
    :param filepath: path to input file
    """
    ranges = []
    ids = []

    with open(filepath, "r") as f:
        file_sep = f.read().split("\n\n")
        for row in file_sep[0].splitlines():
            ranges.append([int(x) for x in row.split("-")])
        for row in file_sep[1].splitlines():
            ids.append(int(row))
            
    return ranges, ids

def hoare_partition(A, idx_list, low, high):
    """
    Based on the Hoare scheme, partitions index list based on values of list A and returns"
    the partitioning
    """
    pivot = A[idx_list[random.randint(low, high)]]
    i = low - 1
    j = high + 1

    while True:
        i += 1
        while A[idx_list[i]] < pivot:
            i += 1

        j -= 1
        while A[idx_list[j]] > pivot:
            j -= 1

        if i >= j:
            return j
        
        idx_list[i], idx_list[j] = idx_list[j], idx_list[i]

def quicksort(A, idx_list, low, high):
    """
    Implements quicksort using the Hoare partition scheme above. Note that this can run into
    infinite recursion for many duplicate values in A, against which the if statement tries
    to safeguard. 
    
    :param A: List of values
    :param idx_list: index list to be sorted according to A
    :param low: lowest index
    :param high: highest index
    """
    if low < high:
        p = hoare_partition(A, idx_list, low, high)
        if p == high:
            # protection against infinite recursion
            p -= 1
        quicksort(A, idx_list, low, p)
        quicksort(A, idx_list, p + 1, high)

def sort_combine_ranges(ranges):
    """
    Sort and combine ranges from a list of unsorted, overlapping ranges. Sorting is done with the
    above quicksorte. Alternatively, numpy's builtin `argsort` can be used for sorting.
    Sorting and combining the ranges speeds up the solution for part 1 and enables solution for
    part 2 with only a handful of lines.
    
    :param ranges: list of all, potentially overlapping, ranges
    """

    idx_list = list(range(len(ranges)))
    range_starts = [x[0] for x in ranges]
    # idx_list = np.argsort(range_starts)

    quicksort(range_starts, idx_list, 0, len(idx_list) - 1)
    
    combined_ranges = [ranges[idx_list[0]]]

    for i in idx_list[1::]:
        if ranges[i][0] <= combined_ranges[-1][1]:
            combined_ranges[-1][1] = max(combined_ranges[-1][1], ranges[i][1])
        else:
            combined_ranges.append(ranges[i])

    return combined_ranges

def filter_valid_ids(sorted_ranges, sorted_ids):
    """
    Count how many of the IDs in `sorted_ids` fall within one of the (inclusive) ranges.
    
    :param sorted_ranges: inclusive ranges of valid IDs in ascending order
    :param sorted_ids: all IDs
    """
    valid_ids = []
    num_valid_ids = 0

    id_cnt = 0
    range_cnt = 0
    while id_cnt < len(sorted_ids) and range_cnt < len(sorted_ranges):
        if sorted_ids[id_cnt] < sorted_ranges[range_cnt][0]:
            id_cnt += 1
        elif sorted_ids[id_cnt] > sorted_ranges[range_cnt][1]:
            range_cnt += 1
        elif sorted_ids[id_cnt] >= sorted_ranges[range_cnt][0] \
            and sorted_ids[id_cnt] <= sorted_ranges[range_cnt][1]:
            valid_ids.append(sorted_ids[id_cnt])
            num_valid_ids += 1
            id_cnt += 1
        else:
            print(sorted_ids[id_cnt], sorted_ranges[range_cnt])

    return num_valid_ids

def all_valid_ids(sorted_ranges):
    """
    Counts how the maximum possible number of valid IDs within the given ranges.
    
    :param sorted_ranges: inclusive ranges of valid IDs in ascending order
    """
    num_valid_ids = 0
    
    for sr in sorted_ranges:
        num_valid_ids += sr[1] - sr[0] + 1

    return num_valid_ids

if __name__ == "__main__":
    ranges, ids = read_inputs(filepath="../../input/input05.txt")
    range_starts = [x[0] for x in ranges]

    # ids_idx = np.argsort(ids)
    ids_idx = list(range(len(ids)))
    quicksort(ids, ids_idx, 0, len(ids) - 1)
    sorted_ids = [ids[idx] for idx in ids_idx]
    sorted_combined_ranges = sort_combine_ranges(ranges)

    num_valid_ids = filter_valid_ids(sorted_combined_ranges, sorted_ids)

    num_all_valid_ids = all_valid_ids(sorted_combined_ranges)

    print(f"number of valid IDs (part 1): {num_valid_ids}")
    print(f"number of ALL valid IDs (part 2): {num_all_valid_ids}")

    print(f"execution time: {time.time() - start_time}")