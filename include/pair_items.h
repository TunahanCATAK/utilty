#ifndef TC_PAIR_ITEMS_H
#define TC_PAIR_ITEMS_H

#include <iterator>
#include <concepts>

namespace tc::views {

// Define a concept for a container with .size()
template <typename T>
concept SizedContainer = requires(T t) {
    { t.size() } -> std::convertible_to<std::size_t>;
};

template <SizedContainer T>
class pair_items_view {
    T* container;

    struct iterator {
        const T* container;
        std::size_t current;
        using difference_type = std::ptrdiff_t;
        using value_type = std::pair<typename T::value_type, typename T::value_type>;

        iterator() = default;
        iterator(const T* container, std::size_t start) : container(container), current(start) {}
        iterator(const iterator&) = default;
        iterator& operator=(const iterator&) = default;

        std::pair<typename T::value_type, typename T::value_type> operator*() const {
            auto [firstInd, secondInd] = indexes(current, container->size());
            return {(*container)[firstInd], (*container)[secondInd]};
        }

        iterator& operator++() {
            ++current;
            return *this;
        }
        iterator operator++(int) {
            iterator copy = *this;
            ++current;
            return copy;
        }

        bool operator==(const iterator& other) const {
            return current == other.current;
        }
        bool operator!=(const iterator& other) const {
            return current != other.current;
        }

    private:
        static std::pair<size_t, size_t> indexes(size_t index, size_t size) {
            size_t row = 0;
            size_t cumulative_count = 0;

            while (index >= cumulative_count + (size - row - 1)) {
                cumulative_count += (size - row - 1);
                row++;
            }

            size_t col = index - cumulative_count + row + 1;

            return {row, col};
        }
    };


public:
    pair_items_view(T& container) : container(std::addressof(container)) {}

    iterator begin() { return iterator(container, 0); }
    iterator end() { return iterator(container, size()); }

    std::size_t size() const {
        return container->size() * (container->size() - 1) / 2;
    }
};
}

#endif TC_PAIR_ITEMS_H