#include "my_sort.hpp"

#include <algorithm>
#include <iostream>
#include <random>
#include <vector>

struct ByCoordinates {
    bool operator()(const Point& first, const Point& second) const {
        if (first.x != second.x) return first.x < second.x;
        return first.y < second.y;
    }
};

bool checkInts(std::vector<int> values) {
    std::vector<int> expected = values;
    mySort(values.begin(), values.end());

    if (!std::is_sorted(values.begin(), values.end())) return false;
    std::sort(expected.begin(), expected.end());
    return values == expected;
}

bool checkPoints(std::vector<Point> points) {
    std::vector<Point> expected = points;
    mySort(points.begin(), points.end(), ByDistance{});

    if (!std::is_sorted(points.begin(), points.end(), ByDistance{})) return false;

    std::sort(points.begin(), points.end(), ByCoordinates{});
    std::sort(expected.begin(), expected.end(), ByCoordinates{});
    for (int i = 0; i < static_cast<int>(points.size()); ++i) {
        if (points[i].x != expected[i].x || points[i].y != expected[i].y) return false;
    }
    return true;
}

int main() {
    std::vector<std::vector<int>> intTests = {
        {}, {5}, {-5, -2, 0, 3, 9}, {9, 3, 0, -2, -5},
        {7, 7, 7, 7}, {4, 1, 4, 1, 0}
    };

    bool passed = true;
    for (const auto& values : intTests) {
        if (!checkInts(values)) passed = false;
    }

    std::vector<std::vector<Point>> pointTests = {
        {}, {{-3, 4}}, {{0, 0}, {1, 0}, {0, 2}, {-3, 0}},
        {{-3, 0}, {0, 2}, {1, 0}, {0, 0}},
        {{2, -1}, {2, -1}, {2, -1}}
    };

    for (const auto& points : pointTests) {
        if (!checkPoints(points)) passed = false;
    }

    std::mt19937 randomGenerator(1729);
    int sizes[] = {10, 1000, 100000};
    for (int size : sizes) {
        std::vector<int> values(size);
        std::vector<Point> points(size);
        for (int i = 0; i < size; ++i) {
            values[i] = static_cast<int>(randomGenerator() % 200001) - 100000;
            points[i].x = static_cast<int>(randomGenerator() % 20001) - 10000;
            points[i].y = static_cast<int>(randomGenerator() % 20001) - 10000;
        }
        if (!checkInts(values)) passed = false;
        if (!checkPoints(points)) passed = false;
    }

    if (passed) {
        std::cout << "All correctness checks passed.\n";
        return 0;
    }

    std::cout << "A correctness check failed.\n";
    return 1;
}
