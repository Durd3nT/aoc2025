import sys
sys.path.append("..")

import unittest

from src import day02

class TestDay02(unittest.TestCase):

    def test_brute_double_pattern(self):
        start, end = day02.read_input(filepath="../../input/test02.txt")
        invalid_ids = day02.brute_double_pattern(start, end)
        self.assertEqual((sum(invalid_ids)), 1227775554)

    def test_brute_multi_pattern(self):
        start, end = day02.read_input(filepath="../../input/test02.txt")
        invalid_ids = day02.brute_multi_pattern(start, end)
        self.assertEqual((sum(invalid_ids)), 4174379265)

if __name__ == "__main_":
    unittest.main()