#include <catch2/catch_all.hpp>

#include "pair_items.h"
#include <ranges>
#include <vector>

TEST_CASE("basic vector") {
    std::vector a{1, 2, 3};
    std::vector<std::pair<int, int>> expected {
        {1, 2},
        {1, 3},
        {2, 3}
    };
    int i = 0;
    for (auto&& [lItem, rItem] : views::pair_items(a)) {
        REQUIRE(lItem == expected[i].first);
        REQUIRE(rItem == expected[i].second);
        ++i;
    }
}

TEST_CASE("basic const vector") {
    const std::vector a{1, 2, 3};
    std::vector<std::pair<int, int>> expected {
            {1, 2},
            {1, 3},
            {2, 3}
    };
    int i = 0;
    for (auto&& [lItem, rItem] : views::pair_items(a)) {
        REQUIRE(lItem == expected[i].first);
        REQUIRE(rItem == expected[i].second);
        ++i;
    }
}

TEST_CASE("transform") {
    const std::vector a{1, 2, 3};
    std::vector<std::pair<int, int>> expected {
            {0, 1},
            {0, 2},
            {1, 2}
    };

    int i = 0;
    for (auto&& [lItem, rItem] :
            views::pair_items(a | std::views::transform([](auto i) { return i - 1; }))) {
        REQUIRE(lItem == expected[i].first);
        REQUIRE(rItem == expected[i].second);
        ++i;
    }
}

