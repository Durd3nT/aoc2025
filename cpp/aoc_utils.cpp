#include "aoc_utils.hpp"
#include <vector>

std::vector<std::string> split(const std::string & s, const std::string & delimiter) {
    std::vector<std::string> result;
    size_t delim_len = delimiter.length();
    size_t pos = 0, new_pos = 0;

    while (new_pos != std::string::npos)
    {
        new_pos = s.find(delimiter, pos);
        result.push_back(s.substr(pos, new_pos - pos));
        pos = new_pos + delim_len;
    }

    return result;
}
