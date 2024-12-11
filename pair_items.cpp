//
// Created by Tunahan Catak on 08/12/2024.
//

#include <iostream>
#include <vector>
#include <ranges>
#include <algorithm>

#include "include/pair_items.h"


int main()
{
    std::cout << "Pair Items View Tests" << std::endl;

    const std::vector<int> numbers = {1, 2, 3, 4, 5};

    auto foo = views::pair_items(numbers);
    for (const auto& [first, second] : foo)
    {
        std::cout << first << " " << second << std::endl;
    }

    auto x = std::views::transform(views::pair_items(numbers), [](const auto& p) {
        return p.first + p.second;
    });

    std::cout << "Transformed" << std::endl;
    for (const auto& item : x)
    {
        std::cout << item << std::endl;
    }

    auto y = tc::views::pair_views(numbers) | std::views::transform([](const auto& p) {
        return p.first + p.second;
    });


    return 0;

}
