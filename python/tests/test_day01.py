import sys
sys.path.append("..")

import unittest

from src import day01

class TestDay01(unittest.TestCase):
    
    def test_count_zero_passes(self):
        test_clicks = day01.read_inputs(filepath="../../input/test01.txt")
        zero_cnt, zero_passed_cnt = day01.count_zero_passes(test_clicks)
        self.assertEqual(zero_cnt, 3)
        self.assertEqual(zero_passed_cnt, 3)

if __name__ == "__main_":
    unittest.main()