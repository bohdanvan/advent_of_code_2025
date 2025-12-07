#include "Day6.h"
#include <string>
#include <fstream>
#include <iostream>
#include <sstream>
#include <ranges>
#include <boost/algorithm/string.hpp>

namespace day6 {

    constexpr char DELIMITER = '_';
    constexpr std::string DELIMITER_STR = "_";

    int run() {
        const std::filesystem::path inputPath = "../day6/input.txt";

        std::ifstream file1(inputPath);
        const auto res1 = solve1(file1);
        std::cout << "Solution 1: " << res1 << std::endl;

        std::ifstream file2(inputPath);
        const auto res2 = solve2(file2);
        std::cout << "Solution 2: " << res2 << std::endl;
        return 0;
    }

    std::vector<std::vector<std::string>> readGrid(std::istream& in) {
        std::vector<std::vector<std::string>> grid;

        for (std::string line; std::getline(in, line);) {
            std::vector<std::string> row;
            boost::trim_left_if(line, boost::is_any_of(DELIMITER_STR));
            boost::split(row, line, boost::is_any_of(DELIMITER_STR), boost::token_compress_on);
            if (row[row.size() - 1].empty()) {
                row.pop_back();
            }
            grid.emplace_back(std::move(row));
        }

        return grid;
    }

    std::vector<std::string> readLines(std::istream& in) {
        std::vector<std::string> lines;
        for (std::string line; std::getline(in, line);) {
            lines.emplace_back(std::move(line));
        }
        return lines;
    }

    auto parseOperator(const char ch) -> long(*)(long, long) {
        return ch == '+'
                ? [](const long a, const long b) { return a + b; }
                : [](const long a, const long b) { return a * b; };
    }

    long calcCol1(const std::vector<std::vector<std::string>>& grid, const long col) {
        const char opChar = grid[grid.size() - 1][col][0];
        long res = opChar == '+' ? 0 : 1;
        const auto op = parseOperator(opChar);

        for (auto i = 0; i < grid.size() - 1; i++) {
            const long arg = std::stol(grid[i][col]);
            res = op(res, arg);
        }

        return res;
    }

    long solve1(std::istream& in) {
        const auto grid = readGrid(in);

        long res = 0;
        for (auto j = 0; j < grid[0].size(); j++) {
            res += calcCol1(grid, j);
        }

        return res;
    }

    inline int charToInt(const char ch) {
        return ch - '0';
    }

    long calcCol2(
        const std::vector<std::string>& lines,
        const char opChar,
        const std::size_t startPos,
        const std::size_t endPos) {

        long res = opChar == '+' ? 0 : 1;
        const auto op = parseOperator(opChar);

        for (auto j = startPos; j < endPos; j++) {
            long arg = 0;
            for (auto i = 0; i < lines.size() - 1; i++) {
                if (lines[i][j] != DELIMITER) {
                    arg = arg * 10 + charToInt(lines[i][j]);
                }
            }
            res = op(res, arg);
        }

        return res;
    }

    long solve2(std::istream& in) {
        const auto lines = readLines(in);
        const auto& opLine = lines[lines.size() - 1];

        long res = 0;

        auto opPos = opLine.find_first_of("+*");
        auto nextOpPos = opLine.find_first_of("+*", opPos + 1);
        while (nextOpPos != std::string::npos) {
            res += calcCol2(lines, opLine[opPos], opPos, nextOpPos-1);

            opPos = nextOpPos,
            nextOpPos = opLine.find_first_of("+*", opPos + 1);
        }
        res += calcCol2(lines, opLine[opPos], opPos, lines[0].size());

        return res;
    }
}
