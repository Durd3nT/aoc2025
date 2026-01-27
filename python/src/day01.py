def read_inputs(filepath):
    """
    Reads data from input file in the respective format.
    
    :param filepath: path to input file
    """
    clicks = []

    with open(filepath) as f:
        for x in f:
            if x[0] == "L":
                clicks.append(- int(x[1::]))
            elif x[0] == "R":
                clicks.append(int(x[1::]))
    
    return clicks

def count_zero_passes(clicks):
    """
    On a dial 0-99, counts how often the 0 is passed if the dial is turned by the values in
    `clicks`, and how often the dial stops at 0, given it is initiated at the value 50.
    
    :param clicks: list of values by which to turn the dial
    """

    dial = 50
    zero_cnt = 0
    zero_passed_cnt = 0
    for c in clicks:
        new_dial = (dial + c) % 100

        click_periods = abs(c) // 100
        zero_passed_cnt += click_periods

        if ((new_dial > dial and c < 0) or (new_dial < dial and c > 0)) \
                and not new_dial == 0 \
                and not dial == 0:
            zero_passed_cnt += 1

        dial = new_dial
        if dial == 0:
            zero_cnt += 1
        
    return zero_cnt, zero_passed_cnt

if __name__ == "__main__":
    filepath = "../../input/input01.txt"

    clicks = read_inputs(filepath)

    zero_cnt, zero_passed_cnt = count_zero_passes(clicks)

    print(f"Dial turned to 0 a total of {zero_cnt} times ")
    print(f"Dial passed 0 a total of {zero_passed_cnt} times")
    print(f"Sum: {zero_cnt + zero_passed_cnt}")