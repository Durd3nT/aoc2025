import sys
sys.path.append("..")

import unittest

from src import day02
from rust_solutions import day02 as rust_day02

class TestDay02(unittest.TestCase):

    # Python tests
    def test_brute_double_pattern_PYTHON(self):
        start, end = day02.read_input(filepath="../../input/test02.txt")
        invalid_ids = day02.brute_double_pattern(start, end)
        self.assertEqual((sum(invalid_ids)), 1227775554)

    def test_brute_multi_pattern_PYTHON(self):
        start, end = day02.read_input(filepath="../../input/test02.txt")
        invalid_ids = day02.brute_multi_pattern(start, end)
        self.assertEqual((sum(invalid_ids)), 4174379265)

    # Rust tests
    def test_digit_count_RUST(self):
        result1 = rust_day02.digit_count(123456)
        self.assertEqual(result1, 6)

    def test_is_repeated_pattern_RUST(self):
        result1 = rust_day02.is_repeated_pattern(123123, 2)
        result2 = rust_day02.is_repeated_pattern(121212, -1)
        self.assertTrue(result1)
        self.assertTrue(result2)

    def test_find_repeated_patterns_RUST(self):
        ranges = rust_day02.read_input(filepath="../../input/test02.txt")
        result1 = rust_day02.find_repeated_patterns(ranges, 2)
        result2 = rust_day02.find_repeated_patterns(ranges, -1)
        self.assertEqual(result1, 1227775554)
        self.assertEqual(result2, 4174379265)

if __name__ == "__main_":
    unittest.main()