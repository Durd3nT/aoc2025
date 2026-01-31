#include <print>
#include <fstream>
#include <vector>
#include <cstdint>
#include <ranges>


void read_input(const std::string filepath, std::vector<bool> & data, std::vector<int> & dims) {
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
 * NOTE STILL BUGGY
 */
void find_remove_rolls(
    std::vector<bool> & coords,
    const std::vector<int> & dims,
    std::vector<int> & roll_cnts
) {
    std::vector<int> offsets = {-1, 0, 1};
    std::vector<int> tmp_coords;
    int last_cnt = 1;
    while (last_cnt > 0) {
        int cnt = 0;
        for (const int x: std::views::iota(0, dims[0])) {
            for (const int y: std::views::iota(0, dims[1])) {
                if (coords[y * dims[0] + x]) {
                    int bool_sum = 0;
                    for (auto xo: offsets) {
                        int x_neighb = x + xo;
                        if (x_neighb < 0) {
                            continue;
                        }
                        for (auto yo: offsets) {    
                            int y_neighb = y + yo;
                            if (y_neighb < 0 or (xo == 0 and yo == 0)) {
                                continue;
                            }
                            bool_sum += coords[yo * dims[0] + xo];
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
    std::string filepath = "../input/test04.txt";
    std::vector<bool> coords;
    std::vector<int> dims;

    read_input(filepath, coords, dims);

    std::vector<int> roll_cnts;
    find_remove_rolls(coords, dims, roll_cnts);

    std::println("rolls removed in first iteration (part 1): {}", roll_cnts[0]);
    std::println("rolls removed in total (part 2): {}", roll_cnts);
}