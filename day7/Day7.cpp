#include "Day7.h"
#include <string>
#include <fstream>
#include <iostream>
#include <ranges>
#include <unordered_set>

namespace day7 {

    constexpr char START_CHAR = 'S';
    constexpr char SPLITTER_CHAR = '^';

    int run() {
        const std::filesystem::path inputPath = "../day7/input.txt";

        std::ifstream file1(inputPath);
        const auto res1 = solve1(file1);
        std::cout << "Solution 1: " << res1 << std::endl;

        std::ifstream file2(inputPath);
        const auto res2 = solve2(file2);
        std::cout << "Solution 2: " << res2 << std::endl;
        return 0;
    }

    std::vector<std::string> readLines(std::istream& in) {
        std::vector<std::string> lines;
        for (std::string line; std::getline(in, line);) {
            lines.emplace_back(std::move(line));
        }
        return lines;
    }

    long solve1(std::istream& in) {
        const auto lines = readLines(in);

        std::unordered_set<std::size_t> positions;
        positions.insert(lines[0].find_first_of(START_CHAR));

        int res = 0;
        for (const auto& line : std::views::drop(lines, 1)) {
            std::unordered_set<std::size_t> nextPositions;

            for (const auto pos : positions) {
                if (line[pos] == SPLITTER_CHAR) {
                    res++;

                    if (pos >= 1) {
                        nextPositions.insert(pos-1);
                    }
                    if (pos <= lines.size() - 2) {
                        nextPositions.insert(pos+1);
                    }
                } else {
                    nextPositions.insert(pos);
                }
            }

            positions = std::move(nextPositions);
        }

        return res;
    }

    long solve2(std::istream& in) {
        const auto lines = readLines(in);

        std::unordered_map<std::size_t, long> positions;
        positions[lines[0].find_first_of(START_CHAR)] = 1;

        for (const auto& line : std::views::drop(lines, 1)) {
            std::unordered_map<std::size_t, long> nextPositions;

            for (const auto [pos, count] : positions) {
                if (line[pos] == SPLITTER_CHAR) {
                    if (pos >= 1) {
                        nextPositions[pos-1] += count;
                    }
                    if (pos <= lines.size() - 2) {
                        nextPositions[pos+1] += count;
                    }
                } else {
                    nextPositions[pos] += count;
                }
            }

            positions = std::move(nextPositions);
        }

        long res = 0;
        for (const auto count: std::views::values(positions)) {
            res += count;
        }

        return res;
    }
}
