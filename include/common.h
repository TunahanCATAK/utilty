//
// Created by Tunahan Catak on 07/01/2025.
//

#ifndef TC_COMMON_H
#define TC_COMMON_H

#include <ranges>
#include <concepts>

namespace tc::views{

    template <class R>
    concept simple_view = std::ranges::view<R> && std::ranges::range<const R> &&
            std::same_as<std::ranges::iterator_t<R>, std::ranges::iterator_t<const R>> &&
            std::same_as<std::ranges::sentinel_t<R>, std::ranges::sentinel_t<const R>>;

}

#endif //TC_COMMON_H
