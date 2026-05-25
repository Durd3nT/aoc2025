import sys
sys.path.append("..")

import unittest
from parameterized import parameterized

from src import day06

class TestDay06(unittest.TestCase):
    @parameterized.expand([
        ["part1", False, 4277556],
        ["part2", True, 3263827]
    ])
    def test_combine_numbers(self, name, columnwise, expected):
        elements = day06.read_input(filepath="../../input/test06.txt", columnwise=columnwise)
        total = day06.combine_numbers(elements, columnwise=columnwise)

        self.assertEqual(total, expected)

if __name__ == "__main_":
    unittest.main()