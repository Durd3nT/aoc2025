import sys
sys.path.append("..")

import numpy as np
import unittest
from parameterized import parameterized

from src import day05

class TestDay05(unittest.TestCase):
    def test_quicksort(self):
        unsorted = [15, 7, 10, 1, 34, 12, 4]
        idx_list = list(range(len(unsorted)))
        day05.quicksort(unsorted, idx_list, 0, len(unsorted) - 1)
        
        expected_idxs = [3, 6, 1, 2, 5, 0, 4]
        
        self.assertEqual(idx_list, expected_idxs)

    def test_sort_combine_ranges(self):
        ranges = [[1, 3], [2, 4], [6, 8], [9, 10]]
        sorted_combined_ranges = day05.sort_combine_ranges(ranges)

        expected = [[1, 4], [6, 8], [9, 10]]

        self.assertEqual(sorted_combined_ranges, expected)

    def test_valid_ids(self):
        ranges, ids = day05.read_inputs(filepath="../../input/test05.txt")
        ids_idx = np.argsort(ids)
        sorted_ids = [ids[idx] for idx in ids_idx]
        sorted_combined_ranges = day05.sort_combine_ranges(ranges)
        num_valid_ids = day05.filter_valid_ids(sorted_combined_ranges, sorted_ids)
        num_all_valid_ids = day05.all_valid_ids(sorted_combined_ranges)
        
        expected_num_valid_ids = 3
        expected_num_all_valid_ids = 14

        self.assertEqual(num_valid_ids, expected_num_valid_ids)
        self.assertEqual(num_all_valid_ids, expected_num_all_valid_ids)

if __name__ == "__main_":
    unittest.main()