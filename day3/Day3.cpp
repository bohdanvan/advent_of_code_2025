#include "Day3.h"
#include <string>
#include <fstream>
#include <iostream>

namespace day3 {

    int run() {
        const std::filesystem::path inputPath = "../day3/input.txt";

        std::ifstream file1(inputPath);
        const auto res1 = solve1(file1);
        std::cout << "Solution 1: " << res1 << std::endl;

        std::ifstream file2(inputPath);
        const auto res2 = solve2(file2);
        std::cout << "Solution 2: " << res2 << std::endl;
        return 0;
    }

    std::pair<long, int> calcJoltage(const std::string_view& s, int digits) {
        if (s.empty() || digits == 0) {
            return std::make_pair(0, digits);
        }

        const auto firstMaxIdx = std::distance(s.begin(), std::ranges::max_element(s));
        const auto [rightJoltage, remainingDigits] =
            calcJoltage(s.substr(firstMaxIdx + 1, s.length() - firstMaxIdx), digits - 1);
        const auto [leftJoltage, remainingDigits2] =
            calcJoltage(s.substr(0, firstMaxIdx), remainingDigits);

        std::string res;
        if (leftJoltage != 0) {
            res += std::to_string(leftJoltage);
        }
        res += s[firstMaxIdx];
        if (rightJoltage != 0) {
            res += std::to_string(rightJoltage);
        }

        return std::make_pair(std::stol(res), remainingDigits2);
    }

    long solve(std::istream& in, const int digits) {
        long result = 0;
        for (std::string line; std::getline(in, line);) {
            auto [joltage, _] = calcJoltage(line, digits);
            result += joltage;
        }
        return result;
    }

    long solve1(std::istream& in) {
        return solve(in, 2);
    }

    long solve2(std::istream& in) {
        return solve(in, 12);
    }
}
