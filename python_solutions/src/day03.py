import time
start_time = time.time()

def read_input(filepath):
    """
    Reads data from input file in the respective format.
    
    :param filepath: path to input file
    """
    lines = []

    with open(filepath) as f:
        for x in f:
            lines.append(x)
    
    return lines

def find_max_digits(b_string, num_digits):
    """
    In a string of digits, finds the digits that will yield the largest possible integer when
    combined. Note that the order of digits cannot be changed. For example, in 818181911112111,
    the largest combination of three digits is 921 when respecting the order of digits (i.e.,
    disallowing 988 as the 8s would have to moved to the right of the 9)
    
    :param b_string: string of digits
    :param num_digits: How many digits to maximize
    """
    b = [int(x) for x in b_string]

    max_digits = [0] * num_digits
    max_digits[0] = b[0]
    max_idx = [0] * num_digits

    for k in range(num_digits):
        start = max_idx[0] + 1 if k == 0 else max_idx[k - 1] + 1
        for i in range(start, len(b) - num_digits + k + 1):
            if b[i] > max_digits[k]:
                max_digits[k] = b[i]
                max_idx[k] = i

    return max_digits

if __name__ == "__main__":
    batteries = read_inputs(filepath = "../../input/input03.txt")

    max_digits = []
    for b in batteries:
        jolts = find_max_digits(str(int(b)), 12)
        max_digits.append(int("".join([str(x) for x in jolts])))
    max_jolt = sum(max_digits)

    print(f"maximum joltage: {max_jolt}")
    print(f"execution time: {time.time() - start_time}")