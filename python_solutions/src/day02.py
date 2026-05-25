import time
start_time = time.time()

def read_input(filepath):
    """
    Reads data from input file in the respective format.
    
    :param filepath: path to input file
    """
    start = []
    end = []

    with open(filepath) as f:
        for x in f:
            list = x.split(",")
            for l in list:
                s, e = l.split("-")
                start.append(int(s))
                end.append(int(e))
    
    return start, end

def brute_double_pattern(start, end):
    """
    Brute force method to find all integers within an interval [start, end] consisting of two
    repeated integers, e.g., 11, 1212, 342342, ... This is not efficient and not generalizable
    to general pattern-matching of multi-digit patterns repeated k times, e.g., 12121212,
    123123123, ...
    
    :param start: start of interval
    :param end: end of interval
    """
    invalid = []
    for i, s in enumerate(start):
        for a in range(s, end[i] + 1):
            num_str = str(a)
            if len(num_str) % 2 == 0 and 2 * num_str[:len(num_str)//2] == num_str:
                invalid.append(a)

    return invalid

def brute_multi_pattern(start, end):
    """
    Brute force method to find all integers within an interval [start, end] consisting of repeated
    integers, e.g., 1111, 121212, 342342, ... The method loops through all integers, then through
    all devisors of its length. For each divisor k, it checks whether the string is of the form
    k * string[:length/k]
    This is O(L*n) if for L integers within the interval of n digits, hence similar to more (and,
    since we are only interested in purely repetitive integers, unnecissarily) sophisticated
    methods such as computing the KMP prefix function (that is O(n) for strings of length n).
    
    :param start: start of interval
    :param end: end of interval
    """
    invalid = set()
    for i, s in enumerate(start):
        for a in range(s, end[i] + 1):
            num_str = str(a)
            len_str = len(num_str)
            for k in range(2, len_str + 1):
                if not len_str % k == 0:
                    continue
                if num_str == k * num_str[:len_str//k]:
                    invalid.add(a)
    return invalid

if __name__=="__main__":
    start, end = read_inputs(filepath = "../../input/input02.txt")

    invalid_ids_double = brute_double_pattern(start, end)
    ids_sum_double = sum(invalid_ids_double)

    invalid_ids_multi = brute_multi_pattern(start, end)
    ids_sum_multi = sum(invalid_ids_multi)

    print(f"sum of invalid IDs with double pattern: {ids_sum_double}")
    print(f"sum of invalid IDs with multi pattern: {ids_sum_multi}")
    print(f"execution time: {time.time() - start_time}")