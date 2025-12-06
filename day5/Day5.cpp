#include "Day5.h"
#include <string>
#include <fstream>
#include <iostream>
#include <sstream>
#include <ranges>

namespace day5 {

    int run() {
        const std::filesystem::path inputPath = "../day5/input.txt";

        std::ifstream file1(inputPath);
        const auto res1 = solve1(file1);
        std::cout << "Solution 1: " << res1 << std::endl;

        std::ifstream file2(inputPath);
        const auto res2 = solve2(file2);
        std::cout << "Solution 2: " << res2 << std::endl;
        return 0;
    }

    std::pair<long, long> parseRange(const std::string& line) {
        std::istringstream lineStream(line);
        std::string firstStr, secondStr;
        std::getline(lineStream, firstStr, '-');
        std::getline(lineStream, secondStr, '-');
        return std::make_pair(std::stol(firstStr), std::stol(secondStr));
    }

    std::vector<std::pair<long, long>> readRanges(std::istream& in) {
        std::vector<std::pair<long, long>> res;
        for (std::string line; std::getline(in, line) && !line.empty(); ) {
            res.emplace_back(parseRange(line));
        }
        return res;
    }

    std::vector<long> readNumbers(std::istream& in) {
        std::vector<long> res;
        for (std::string line; std::getline(in, line); ) {
            res.emplace_back(std::stol(line));
        }
        return res;
    }

    int solve1(std::istream& in) {
        const auto ranges = readRanges(in);
        const auto numbers = readNumbers(in);

        int res = 0;
        for (const auto n: numbers) {
            for (const auto [start, end] : ranges) {
                if (n >= start && n <= end) {
                    res++;
                    break;
                }
            }
        }
        return res;
    }

    long solve2(std::istream& in) {
        auto ranges = readRanges(in);
        std::ranges::sort(ranges, [](const auto& a, const auto& b) {
            if (a.first == b.first) {
                return a.second < b.second;
            }
            return a.first < b.first;
        });

        long res = 0;
        std::pair<long, long> currRange = ranges[0];
        for (const auto range: std::views::drop(ranges, 1)) {
            if (range.first <= currRange.second) {
                currRange = std::make_pair(currRange.first, std::max(currRange.second, range.second));
            } else {
                res += currRange.second - currRange.first + 1;
                currRange = range;
            }
        }
        res += currRange.second - currRange.first + 1;

        return res;
    }
}
