#include "Day8.h"
#include <string>
#include <fstream>
#include <iostream>
#include <numeric>
#include <ranges>
#include <sstream>
#include <boost/pending/disjoint_sets.hpp>

namespace day8 {

    struct Point3D {
        int x;
        int y;
        int z;
    };

    struct DistanceEntry {
        double distance;
        int idxA;
        int idxB;

        friend auto operator<=>(const DistanceEntry& lhs, const DistanceEntry& rhs) {
            return lhs.distance <=> rhs.distance;
        }
    };

    int run() {
        const std::filesystem::path inputPath = "../day8/input.txt";

        std::ifstream file1(inputPath);
        const auto res1 = solve1(file1);
        std::cout << "Solution 1: " << res1 << std::endl;

        std::ifstream file2(inputPath);
        const auto res2 = solve2(file2);
        std::cout << "Solution 2: " << res2 << std::endl;
        return 0;
    }

    Point3D parsePoint(std::string& s) {
        std::string temp{s};
        std::ranges::replace(temp, ',', ' ');
        std::istringstream ss{temp};
        int a, b, c;
        ss >> a >> b >> c;
        return { a, b, c };
    }

    std::vector<Point3D> parsePoints(std::istream& in) {
        std::vector<Point3D> res;
        for (std::string line; std::getline(in, line);) {
            res.emplace_back(parsePoint(line));
        }
        return res;
    }

    double calcDistance(const Point3D& a, const Point3D& b) {
        return sqrt(pow(a.x - b.x, 2) + pow(a.y - b.y, 2) + pow(a.z - b.z, 2));
    }

    template<class Compare>
    std::priority_queue<DistanceEntry, std::vector<DistanceEntry>, Compare> buildDistancePq(
        const std::vector<Point3D>& points,
        const int capacity = INT_MAX) {

        std::priority_queue<DistanceEntry, std::vector<DistanceEntry>, Compare> distancePq;

        for (auto i = 0; i < points.size(); i++) {
            for (auto j = i+1; j < points.size(); j++) {
                const auto distance = calcDistance(points.at(i), points.at(j));
                distancePq.emplace(distance, i, j);
                if (distancePq.size() > capacity) {
                    distancePq.pop();
                }
            }
        }

        return distancePq;
    }

    long solve1(std::istream& in) {
        constexpr int connectionsLimit = 1000;
        constexpr int resLimit = 3;

        const auto points = parsePoints(in);
        auto distancePq = buildDistancePq<std::less<DistanceEntry>>(points, connectionsLimit);

        boost::disjoint_sets_with_storage groups(points.size());
        while (!distancePq.empty()) {
            auto [_, idxA, idxB] = distancePq.top();
            distancePq.pop();
            groups.union_set(idxA, idxB);
        }

        std::unordered_map<int, int> groupCounter;
        for (auto i = 0; i < points.size(); i++) {
            groupCounter[groups.find_set(i)]++;
        }

        std::priority_queue<int, std::vector<int>, std::greater<int>> groupCounterPq;
        for (const auto &count: groupCounter | std::views::values) {
            groupCounterPq.push(count);
            if (groupCounterPq.size() > resLimit) {
                groupCounterPq.pop();
            }
        }

        int res = 1;
        while (!groupCounterPq.empty()) {
            res *= groupCounterPq.top();
            groupCounterPq.pop();
        }

        return res;
    }

    long solve2(std::istream& in) {
        const auto points = parsePoints(in);

        auto distancePq = buildDistancePq<std::greater<DistanceEntry>>(points);

        boost::disjoint_sets_with_storage groups(points.size());
        auto idxRange = std::views::iota(0, static_cast<int>(points.size()));
        while (!distancePq.empty()) {
            const auto [_, idxA, idxB] = distancePq.top();
            distancePq.pop();
            groups.union_set(idxA, idxB);

            if (groups.count_sets(idxRange.begin(), idxRange.end()) == 1) {
                const auto pointA = points[idxA];
                const auto pointB = points[idxB];
                return pointA.x * pointB.x;
            }
        }

        return 0;
    }
}
