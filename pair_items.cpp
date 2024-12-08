//
// Created by Tunahan Catak on 08/12/2024.
//

#include <iostream>
#include <vector>
#include <ranges>
#include <algorithm>
#include <set>

#include "include/pair_items.h"

template <typename T1, typename T2>
std::ostream& operator<<(std::ostream& os, const std::pair<T1, T2>& pair) {
    os << pair.first << ", " << pair.second;
    return os;
}

int main()
{
    std::cout << "Pair Items View Tests" << std::endl;

    std::vector<int> numbers = {1, 2, 3, 4, 5};

    auto x = tc::views::pair_items_view(numbers)
            | std::views::filter([](const auto& pair) {
                const auto& [first, second] = pair;
            });

    for (auto sum : x) {
        std::cout << sum << std::endl;
    }

    std::set<std::pair<int, int>> pairs;
    std::copy(tc::views::pair_items_view(numbers).begin(), tc::views::pair_items_view(numbers).end(),
              std::inserter(pairs, pairs.begin()));

    // print the set:
    for (const auto& pair : pairs) {
        std::cout << pair << std::endl;
    }

    pairs.clear();
    std::vector<int> empty_numbers;
    std::copy(tc::views::pair_items_view(empty_numbers).begin(),
              tc::views::pair_items_view(empty_numbers).end(),
              std::inserter(pairs, pairs.begin()));

    for (const auto& pair : pairs) {
        std::cout << pair << std::endl;
    }

    pairs.clear();
    std::vector<int> single_number = {1};
    std::copy(tc::views::pair_items_view(single_number).begin(),
              tc::views::pair_items_view(single_number).end(),
              std::inserter(pairs, pairs.begin()));

    for (const auto& pair : single_number) {
        std::cout << pair << std::endl;
    }


    return 0;

}