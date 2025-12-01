#include "Day1.h"
#include <string>
#include <filesystem>
#include <fstream>
#include <iostream>

namespace day1 {
    constexpr int MOD = 100;

    int run() {
        const std::filesystem::path inputPath = "../day1/input.txt";

        std::ifstream file1(inputPath);
        const auto res1 = solve1(file1);
        std::cout << "Solution 1: " << res1 << std::endl;

        std::ifstream file2(inputPath);
        const auto res2 = solve2(file2);
        std::cout << "Solution 2: " << res2 << std::endl;
        return 0;
    }

    int solve1(std::istream& in) {
        int result = 0;
        int currValue = 50;
        for (std::string line; getline(in, line);) {
            const auto direction = line[0];
            const auto num = std::stoi(line.substr(1, line.size() - 1));

            if (direction == 'R') {
                currValue = (currValue + num) % MOD;
            } else {
                currValue = (currValue - num + MOD) % MOD;
            }

            if (currValue == 0) {
                result++;
            }
        }
        return result;
    }

    int solve2(std::istream& in) {
        int result = 0;
        int currValue = 50;
        for (std::string line; getline(in, line);) {
            const auto direction = line[0];
            auto num = std::stoi(line.substr(1, line.size() - 1));

            result += num / MOD;
            num %= MOD;

            if (direction == 'R') {
                result += (currValue + num) / MOD;
                currValue = (currValue + num) % MOD;
            } else {
                result += currValue != 0 && num >= currValue ? 1 : 0;
                currValue = (currValue - num + MOD) % MOD;
            }
        }
        return result;
    }
}
