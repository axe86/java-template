#pragma once

#include <functional>
#include <iterator>
#include <vector>

struct Point {
    double x;
    double y;
};

struct ByDistance {
    bool operator()(const Point& first, const Point& second) const {
        double firstDistance = first.x * first.x + first.y * first.y;
        double secondDistance = second.x * second.x + second.y * second.y;
        return firstDistance < secondDistance;
    }
};

template <typename It, typename Compare>
void mergeSort(It first,
               int left,
               int right,
               const Compare& compare,
               std::vector<typename std::iterator_traits<It>::value_type>& temp) {
    if (right - left <= 1) {
        return;
    }

    const int middle = left + (right - left) / 2;

    mergeSort(first, left, middle, compare, temp);
    mergeSort(first, middle, right, compare, temp);

    int leftIndex = left;
    int rightIndex = middle;
    int tempIndex = left;

    while (leftIndex < middle && rightIndex < right) {
        if (compare(*(first + rightIndex), *(first + leftIndex))) {
            temp[tempIndex] = *(first + rightIndex);
            ++rightIndex;
        } else {
            temp[tempIndex] = *(first + leftIndex);
            ++leftIndex;
        }
        ++tempIndex;
    }

    while (leftIndex < middle) {
        temp[tempIndex] = *(first + leftIndex);
        ++leftIndex;
        ++tempIndex;
    }
    while (rightIndex < right) {
        temp[tempIndex] = *(first + rightIndex);
        ++rightIndex;
        ++tempIndex;
    }

    for (int index = left; index < right; ++index) {
        *(first + index) = temp[index];
    }
}

template <typename It,
          typename Compare = std::less<typename std::iterator_traits<It>::value_type>>
void mySort(It first, It last, Compare compare = Compare{}) {
    using Value = typename std::iterator_traits<It>::value_type;

    const int length = static_cast<int>(last - first);
    if (length <= 1) {
        return;
    }

    std::vector<Value> temp(length);
    mergeSort(first, 0, length, compare, temp);
}
