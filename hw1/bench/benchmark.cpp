#include "my_sort.hpp"

#include <algorithm>
#include <chrono>
#include <iomanip>
#include <iostream>
#include <numeric>
#include <random>
#include <vector>

double resultSum = 0;

double timeInts(const std::vector<int>& input, bool useMySort) {
    std::vector<int> values = input;
    auto start = std::chrono::steady_clock::now();
    if (useMySort) mySort(values.begin(), values.end());
    else std::sort(values.begin(), values.end());
    auto finish = std::chrono::steady_clock::now();

    resultSum += values.front() + values.back();
    return std::chrono::duration<double, std::milli>(finish - start).count();
}

double timePoints(const std::vector<Point>& input, bool useMySort) {
    std::vector<Point> points = input;
    auto start = std::chrono::steady_clock::now();
    if (useMySort) mySort(points.begin(), points.end(), ByDistance{});
    else std::sort(points.begin(), points.end(), ByDistance{});
    auto finish = std::chrono::steady_clock::now();

    resultSum += points.front().x + points.back().x;
    return std::chrono::duration<double, std::milli>(finish - start).count();
}

void printRow(int size, double myTime, double stdTime) {
    std::cout << size << ',' << std::fixed << std::setprecision(3)
              << myTime << ',' << stdTime << ',' << myTime / stdTime << '\n';
}

int main() {
    std::mt19937 randomGenerator(314159);
    int sizes[] = {1000, 10000, 100000, 1000000};
    std::uniform_int_distribution<int> intValue(-100000000, 100000000);
    std::uniform_real_distribution<double> coordinate(-100000, 100000);

    std::cout << "Random int data\nsize,mySort_ms,std_sort_ms,ratio\n";
    for (int size : sizes) {
        std::vector<int> values(size);
        for (int& value : values) value = intValue(randomGenerator);
        printRow(size, timeInts(values, true), timeInts(values, false));
    }

    std::cout << "\nRandom Point data\nsize,mySort_ms,std_sort_ms,ratio\n";
    for (int size : sizes) {
        std::vector<Point> points(size);
        for (Point& point : points) {
            point.x = coordinate(randomGenerator);
            point.y = coordinate(randomGenerator);
        }
        printRow(size, timePoints(points, true), timePoints(points, false));
    }

    std::cout << "\nAlready sorted data, size 100000\n";
    std::vector<int> sortedInts(100000);
    std::iota(sortedInts.begin(), sortedInts.end(), -50000);
    printRow(100000, timeInts(sortedInts, true), timeInts(sortedInts, false));

    std::vector<Point> sortedPoints(100000);
    for (int i = 0; i < 100000; ++i) sortedPoints[i] = {static_cast<double>(i), 0};
    printRow(100000, timePoints(sortedPoints, true), timePoints(sortedPoints, false));

    std::cout << "checksum: " << resultSum << '\n';
    return 0;
}
