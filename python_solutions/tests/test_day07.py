import sys
sys.path.append("..")

import unittest
from parameterized import parameterized

from rust_solutions import day07 as rust_day07

class TestDay07(unittest.TestCase):

    # Rust tests
    def test_count_beam_splits_RUST(self):
        data = rust_day07.read_input(filepath="../../input/test07.txt")

        (num_beam_splits, num_timelines) = rust_day07.count_beam_splits(data)

        self.assertEqual(num_beam_splits, 21)
        self.assertEqual(num_timelines, 40)

if __name__ == "__main_":
    unittest.main()