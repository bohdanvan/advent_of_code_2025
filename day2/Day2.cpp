#include "Day2.h"
#include <string>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <sstream>

namespace day2 {

    int run() {
        const std::filesystem::path inputPath = "../day2/input.txt";

        std::ifstream file1(inputPath);
        const auto res1 = solve1(file1);
        std::cout << "Solution 1: " << res1 << std::endl;

        std::ifstream file2(inputPath);
        const auto res2 = solve2(file2);
        std::cout << "Solution 2: " << res2 << std::endl;
        return 0;
    }

    std::pair<long, long> parseRange(const std::string& rangeStr) {
        std::istringstream rangeStream(rangeStr);
        std::string fromStr, toStr;
        std::getline(rangeStream, fromStr, '-');
        std::getline(rangeStream, toStr);

        return { std::stol(fromStr), std::stol(toStr) };
    }

    long solve(std::istream& in, const std::function<bool(long)>& isInvalidIdFun) {
        std::string line;
        std::getline(in, line);

        long result = 0;
        std::istringstream lineStream(line);
        for (std::string range; std::getline(lineStream, range, ','); ) {
            auto [from, to] = parseRange(range);

            for (auto id = from; id <= to; id++) {
                if (isInvalidIdFun(id)) {
                    result += id;
                }
            }
        }
        return result;
    }

    bool isRepeatingSequences(const std::string_view& s, const int seqCount) {
        if (s.length() % seqCount != 0) {
            return false;
        }

        const int seqSize = s.length() / seqCount;

        const auto firstSeq = s.substr(0, seqSize);
        for (int k = 1; k < seqCount; k++) {
            if (s.substr(k * seqSize, seqSize) != firstSeq) {
                return false;
            }
        }
        return true;
    }

    bool isInvalidId1(const long id) {
        const std::string s = std::to_string(id);
        return isRepeatingSequences(s, 2);
    }

    bool isInvalidId2(const long id) {
        const std::string s = std::to_string(id);

        for (int seqCount = 2; seqCount <= s.length(); seqCount++) {
            if (isRepeatingSequences(s, seqCount)) {
                return true;
            }
        }
        return false;
    }

    long solve1(std::istream& in) {
        return solve(in, isInvalidId1);
    }

    long solve2(std::istream& in) {
        return solve(in, isInvalidId2);
    }
}
