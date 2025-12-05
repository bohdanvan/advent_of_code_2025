#include "Day4.h"
#include <string>
#include <fstream>
#include <iostream>

namespace day4 {

    constexpr char PAPER_CELL = '@';
    constexpr char EMPTY_CELL = '.';
    const std::vector<std::pair<int, int>> POS_AROUND_INC = {
        {-1, -1},
        {-1, 0},
        {-1, 1},
        {0, -1},
        {0, +1},
        {1, -1},
        {1, 0},
        {1, 1}
    };

    class Grid {
    public:
        explicit Grid(std::vector<std::string>&& data): grid_(std::move(data)) {}

        [[nodiscard]] char get(const int i, const int j, const char defaultVal = '\0') const {
            if (!isValidIdx(i, j)) {
                return defaultVal;
            }
            return grid_[i][j];
        }

        void set(const int i, const int j, const char value) {
            if (!isValidIdx(i, j)) {
                return;
            }
            grid_[i][j] = value;
        }

        [[nodiscard]] int rows() const noexcept {
            return static_cast<int>(grid_.size());
        }

        [[nodiscard]] int cols() const noexcept {
            return grid_.empty() ? 0 : static_cast<int>(grid_[0].size());
        }

    private:
        std::vector<std::string> grid_;

        [[nodiscard]] bool isValidIdx(const int i, const int j) const {
            return i >= 0 && i < grid_.size() && j >= 0 && j < grid_[0].size();
        }
    };

    int run() {
        const std::filesystem::path inputPath = "../day4/input.txt";

        std::ifstream file1(inputPath);
        const auto res1 = solve1(file1);
        std::cout << "Solution 1: " << res1 << std::endl;

        std::ifstream file2(inputPath);
        const auto res2 = solve2(file2);
        std::cout << "Solution 2: " << res2 << std::endl;
        return 0;
    }

    inline int countAround(const Grid& grid, const int i, const int j, const char value) {
        int count = 0;
        for (auto [incI, incJ]: POS_AROUND_INC) {
            if (grid.get(i + incI, j + incJ) == value) {
                count++;
            }
        }
        return count;
    }

    Grid readGrid(std::istream& in) {
        std::vector<std::string> lines;
        for (std::string line; std::getline(in, line);) {
            lines.push_back(std::move(line));
        }

        return Grid(std::move(lines));
    }

    int solve1(std::istream& in) {
        const Grid grid = readGrid(in);

        int res = 0;
        for (auto i = 0; i < grid.rows(); ++i) {
            for (auto j = 0; j < grid.cols(); ++j) {
                if (grid.get(i, j) == PAPER_CELL && countAround(grid, i, j, PAPER_CELL) < 4) {
                    res++;
                }
            }
        }
        return res;
    }

    int solve2(std::istream& in) {
        Grid grid = readGrid(in);

        int res = 0;
        bool needCleaning = true;
        while (needCleaning) {
            std::vector<std::pair<int, int>> cellsToClean;
            for (auto i = 0; i < grid.rows(); ++i) {
                for (auto j = 0; j < grid.cols(); ++j) {
                    if (grid.get(i, j) == PAPER_CELL && countAround(grid, i, j, PAPER_CELL) < 4) {
                        cellsToClean.emplace_back(i, j);
                    }
                }
            }

            for (auto [i, j]: cellsToClean) {
                grid.set(i, j, EMPTY_CELL);
            }

            res += static_cast<int>(cellsToClean.size());
            needCleaning = !cellsToClean.empty();
        }
        return res;
    }
}
