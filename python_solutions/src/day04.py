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
            lines.append(x.rstrip("\n"))
    
    return lines

def get_roll_coords(string_list):
    """
    Getting all roll coordinates and then for every roll checking if the neighboring coordinates
    are in the coords list too would be O(n^2) (O(n) for searching a list a max of n times).
    Therefore, it is more efficient to hash all coordinates of the grid with a bool indicating
    whether there is a roll at this coord and then loop through the grid only once, since looking
    up dict keys is O(1).
    
    :param string_list: 
    """
    coords = {}

    for i, row in enumerate(string_list):
        for j in range(len(row)):
            if row[j] == "@":
                coords[i, j] = True
            else:
                coords[i, j] = False

    return coords

def find_remove_isolate_rolls(roll_coords):
    """
    Iterates through `roll_coords` dictionary. For every roll, checks all eight neighboring grid
    points, counting the number of neighboring rolls. If there are less than four rolls in the
    neighborhood of the original roll, this roll is removed from the grid dictionary by setting
    its value to False. The method stops when the grid is cleared of all rolls and returns the
    number of rolls removed in each iteration.
    
    :param roll_coords: dictionary with grid coordinates as keys and bool values indicating
    whether grid point holds a roll (True)
    """
    offsets = [-1, 0, 1]

    iter_cnts = []
    last_cnt = 1
    while last_cnt > 0:
        iter_cnts.append(0)
        tmp_coords = []
        for key in roll_coords.keys():
            if roll_coords[key]:
                bool_sum = 0
                for x in offsets:
                    for y in offsets:
                        if x==0 and y==0:
                            continue
                        bool_sum += roll_coords.get((key[0] + y, key[1] + x), False)

                if bool_sum < 4:
                    iter_cnts[-1] += 1
                    tmp_coords.append(key)

        for coord in tmp_coords:
            roll_coords[coord] = False

        last_cnt = iter_cnts[-1]

    return iter_cnts

if __name__ == "__main__":
    input_strings = read_inputs(filepath="../../input/input04.txt")

    roll_coords = get_roll_coords(input_strings)
    num_rolls = find_remove_isolate_rolls(roll_coords)

    print(f"rolls removed in first iteration: {num_rolls[0]}")
    print(f"rolls removed in total: {sum(num_rolls)}")
    print(f"execution time: {time.time() - start_time}")