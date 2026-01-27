import sys
sys.path.append("..")

import unittest
from parameterized import parameterized

from src import day04

class TestDay04(unittest.TestCase):
    def test_get_roll_coords(self):
        input_string = ["..@@.@@@@."]
        roll_coords = day04.get_roll_coords(input_string)
        expected = {
            (0, 0): False,
            (0, 1): False,
            (0, 2): True,
            (0, 3): True,
            (0, 4): False,
            (0, 5): True,
            (0, 6): True,
            (0, 7): True,
            (0, 8): True,
            (0, 9): False
        }
        self.assertEqual(roll_coords, expected)

    @parameterized.expand([
        ["part1", False, 13],
        ["part2", True, 43]
    ])
    def test_count_zero_passes(self, name, summed, expected):
        input_strings = day04.read_inputs(filepath="../../input/test04.txt")
        roll_coords = day04.get_roll_coords(input_strings)
        num_rolls = day04.find_remove_isolate_rolls(roll_coords)

        if not summed:
            self.assertEqual(num_rolls[0], expected)
        else:
            self.assertEqual(sum(num_rolls), expected)

if __name__ == "__main_":
    unittest.main()