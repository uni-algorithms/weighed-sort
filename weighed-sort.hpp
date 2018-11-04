#ifndef WEIGHED_SORT_HPP
#define WEIGHED_SORT_HPP

#include <algorithm>
#include <fstream>
#include <numeric>
#include <unordered_map>
#include <vector>

class swaps_weight {
    long swaps;
    long weight;

public:
    swaps_weight(const long swaps, const long weight) : swaps(swaps), weight(weight) {}

    bool operator==(const swaps_weight &rhs) const {
        return swaps == rhs.swaps &&
               weight == rhs.weight;
    }

    bool operator!=(const swaps_weight &rhs) const {
        return !(rhs == *this);
    }

    friend std::ostream &operator<<(std::ostream &os, const swaps_weight &th) {
        os << th.swaps << " " << th.weight;
        return os;
    }
};

std::vector<int>
cycle(std::unordered_map<int, int> &map, const int hd, const int to, std::vector<int> &until) {
    auto next = map.find(to);
    auto next_to = next->second;
    auto value = next->first;

    map.erase(next);
    until.push_back(value);

    return value == hd ? until : cycle(map, hd, next_to, until);
}

std::vector<std::vector<int>>
cycles(std::unordered_map<int, int> &map, std::vector<std::vector<int>> &until) {
    if (map.empty()) {
        return until;
    }

    std::vector<int> c;
    until.push_back(cycle(map, map.begin()->first, map.begin()->second, c));
    return cycles(map, until);
}

long min_swaps(const int acc, const std::vector<int> &cycle) {
    return acc + cycle.size() - 1;
}

long min_swaps_cs(const std::vector<std::vector<int>> &cycles) {
    return std::accumulate(cycles.begin(), cycles.end(), 0, min_swaps);
}

long min_weight(const int acc, const std::vector<int> &cycle) {
    auto size = cycle.size();
    auto min = *std::min_element(cycle.begin(), cycle.end());
    auto sum_with_min = std::accumulate(cycle.begin(), cycle.end(), min * (size - 2));
    auto sum_with_one = std::accumulate(cycle.begin(), cycle.end(), size + (1 + min));
    return acc + std::min(sum_with_one, sum_with_min);
}

long min_weight_cs(const std::vector<std::vector<int>> &cycles) {
    return std::accumulate(cycles.begin(), cycles.end(), 0, min_weight);
}

swaps_weight uncovered(std::istream &input) {
    unsigned long n;
    std::unordered_map<int, int> unordered;

    input >> n;

    for (auto i = 0; i < n; ++i) {
        int x;
        input >> x;
        if (x != i + 1) { unordered.emplace(i + 1, x); }
    }

    std::vector<std::vector<int>> empty;
    auto cs = cycles(unordered, empty);
    auto swaps = min_swaps_cs(cs);
    auto weight = min_weight_cs(cs);
    return {swaps, weight};
}

#endif //WEIGHED_SORT_HPP
