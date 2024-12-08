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

    std::vector<int> numbers = {1, 2, 3, 4, 5};
    for (const auto& [first, second] : tc::views::pair_items_view(numbers))
    {
        std::cout << first << " " << second << std::endl;
    }
    
    auto x = std::views::transform(tc::views::pair_items_view(numbers), [](const auto& p) {
        return p.first + p.second;
    });


    return 0;

}
