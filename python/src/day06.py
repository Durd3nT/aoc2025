import time
start_time = time.time()

import numpy as np

def read_inputs(filepath, columnwise=False):
    """
    Reads data from input file in the respective format.
    
    :param filepath: path to input file
    """

    if not columnwise:
        elements = []
        with open(filepath, "r") as f:
            for row in f:
                elements.append([])
                for n in row.split():
                    elements[-1].append(n)
    else:
        elements = []
        with open(filepath, "r") as f:
            for row in f:
                elements.append([])
                for char in row:
                    if char == '\n':
                        continue
                    elements[-1].append(char)
        elements = np.array(elements).transpose()

    return elements

def combine_numbers(elements, columnwise=False):
    """
    The puzzle input is a table of numbers of which the columns are to be summed or multiplied
    together. In part 1, the numbers in each column are read row-wise. In part 2, the numbers
    in each column are read column-wise. This is done by reading each char from the input file
    into a matrix and transposing for part 2.
    
    :param elements: character matrix from input
    :param columnwise: whether numbers are read column-wise or not
    """
    res = 0
    if not columnwise:
        numbers = np.array(elements[:-1]).astype(np.int32).transpose()
        ops = np.array(elements[-1])

        for i, col in enumerate(numbers):
            if ops[i] == "+":
                res += np.sum(col)
            elif ops[i] == "*":
                res += np.prod(col)
    else:
        op = ''
        for col in elements:
            if not col[-1] == ' ':
                op = col[-1]
                if op == '+':
                    sub_res = 0
                elif op == '*':
                    sub_res = 1

            num = ''
            for char in col[:-1]:
                if char == ' ': continue
                num += char

            if not num:
                res += sub_res
                continue

            if op == '+':
                sub_res += int(num)
            elif op == '*':
                sub_res *= int(num)

        res += sub_res

    return res

if __name__ == "__main__":
    elements = read_inputs(filepath="../../input/input06.txt")
    total = combine_numbers(elements)

    print(f"total of row-wise addition (part 1): {total}")

    elements = read_inputs(filepath="../../input/input06.txt", columnwise=True)
    total = combine_numbers(elements, columnwise=True)

    print(f"total of column-wise addition (part 2): {total}")
