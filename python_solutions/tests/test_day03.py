import sys
sys.path.append("..")

import unittest
from parameterized import parameterized

from src import day03

class TestDay03(unittest.TestCase):

    @parameterized.expand([
        ["part1", 2, 357],
        ["part2", 12, 3121910778619]
    ])
    def test_find_max_digits_(self, name, length, expected):
        batteries = day03.read_input(filepath="../../input/test03.txt")

        max_digits = []
        for b in batteries:
            jolts = day03.find_max_digits(str(int(b)), length)
            max_digits.append(int("".join([str(x) for x in jolts])))
        max_jolt = sum(max_digits)

        self.assertEqual(max_jolt, expected)

if __name__ == "__main_":
    unittest.main()