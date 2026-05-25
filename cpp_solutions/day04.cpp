#include <print>
#include <fstream>
#include <vector>
#include <cstdint>
#include <ranges>
#include <numeric>


void readInput(const std::string filepath, std::vector<bool> & data, std::vector<int> & dims) {
    std::ifstream inFile(filepath);

    if (inFile.is_open()) {
        size_t cnt = 0;
        size_t x_len = 0;
        std::string val;
        while (getline(inFile, val)) {
            x_len = val.size();
            data.resize((cnt + 1) * x_len);

            for (std::size_t i = 0; i < val.size(); ++i) {
                if (val[i] == '@'){
                    data[cnt * x_len + i] = true;
                }
            }
            ++cnt;
        }
        dims.push_back(x_len);
        dims.push_back(cnt);
    } else { std::println("ERROR: could not open file"); }
}

/**
 * Iterates through `roll_coords` dictionary. For every roll, checks all eight neighboring grid
 * points, counting the number of neighboring rolls. If there are less than four rolls in the
 * neighborhood of the original roll, this roll is removed from the grid dictionary by setting
 * its value to False. The method stops when the grid is cleared of all rolls and returns the
 * number of rolls removed in each iteration.
 * 
 * @param coords: coordinate vector of bools indicating whether that there is a roll at the
 *  respective grid point. This is being modified throughout computation
 * @param dims: grid dimensions N_x x N_y
 * @param roll_cnts: the target vector that is populated iteratively, with elements being the
 *  number of rolls removed at each iteration
 */
void findRemoveRolls(
    std::vector<bool> & coords,
    const std::vector<int> & dims,
    std::vector<int> & roll_cnts
) {
    std::vector<int> offsets = {-1, 0, 1};
    int last_cnt = 1;
    while (last_cnt > 0) {
        std::vector<int> tmp_coords;
        int cnt = 0;
        for (const int y: std::views::iota(0, dims[1])) {
            for (const int x: std::views::iota(0, dims[0])) {
                if (coords[y * dims[0] + x]) {
                    int bool_sum = 0;
                    for (auto yo: offsets) {
                        int y_neighb = y + yo;
                        if ((y_neighb < 0) or (y_neighb >= dims[1])) {
                            continue;
                        }
                        for (auto xo: offsets) {    
                            int x_neighb = x + xo;
                            if ((x_neighb < 0) or (x_neighb >= dims[0]) or (xo == 0 and yo == 0)) {
                                continue;
                            }
                            bool_sum += coords[y_neighb * dims[0] + x_neighb];
                            if (bool_sum >= 4) {
                                goto continue2;
                            }
                        }
                    }
                    if (bool_sum < 4) {
                        ++cnt;
                        tmp_coords.push_back(y * dims[0] + x);
                    }
                }
                continue2:;
            }
        }

        for (auto tc: tmp_coords) {
            coords[tc] = false;
        }

        roll_cnts.push_back(cnt);
        last_cnt = cnt;
    }
}

int main() {
    std::string filepath = "../input/input04.txt";
    std::vector<bool> coords;
    std::vector<int> dims;

    readInput(filepath, coords, dims);

    std::vector<int> roll_cnts;
    findRemoveRolls(coords, dims, roll_cnts);
    auto tot_roll_cnts = std::reduce(roll_cnts.begin(), roll_cnts.end());

    std::println("rolls removed in first iteration (part 1): {}", roll_cnts[0]);
    std::println("rolls removed in total (part 2): {}", tot_roll_cnts);
}