#ifndef TC_PAIR_ITEMS_H
#define TC_PAIR_ITEMS_H

#include <iterator>
#include <concepts>

namespace tc::views {

    template <std::ranges::range R>
    class pair_views : public std::ranges::view_interface<pair_views<R>> {
        R m_base;

        class cursor {
            std::size_t position_ = 0;
            std::size_t size_ = 0;
            std::ranges::iterator_t<R> current_{};

        public:
            using difference_type = std::ptrdiff_t;
            using value_type = std::pair<std::ranges::range_value_t<R>, std::ranges::range_value_t<R>>;

            cursor() = default;
            cursor(const std::ranges::iterator_t<R> current, std::size_t start, std::size_t size) : current_{current}, position_(start), size_{size} {}

            cursor(const cursor&) = default;
            cursor &operator=(const cursor&) = default;

            value_type operator*() const {
                //std::cout << "operator*" << std::endl;
                auto [firstInd, secondInd] = indexes(position_, size_);
                return {current_[firstInd], current_[secondInd]};
            }

            value_type operator*() {
                //std::cout << "operator*" << std::endl;
                auto [firstInd, secondInd] = indexes(position_, size_);
                return {current_[firstInd], current_[secondInd]};
            }

            cursor &operator++() {
                //++current_;
                ++position_;
                return *this;
            }

            cursor operator++(int) {
                cursor copy = *this;
                //++current_;
                ++position_;
                return copy;
            }

            bool operator==(const cursor &other) const {
                return position_ == other.position_;
            }

            bool operator!=(const cursor &other) const {
                return position_ != other.position_;
            }

            friend class cursor;

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
        pair_views() = default;
        constexpr pair_views(R base) : m_base(base) {
            //std::cout << "pair_views" << std::endl;
        }

//        constexpr R base() const& requires std::copy_constructible<R> {
//            return m_base;
//        }
//        constexpr R base()&& { return std::move(m_base); }


        constexpr auto begin() { return cursor(std::ranges::begin(m_base), 0, m_base.size()); }
        constexpr auto begin() const { return cursor(std::ranges::begin(m_base), 0, m_base.size()); }

        constexpr auto end() { return cursor(std::ranges::begin(m_base), size(), m_base.size()); }
        constexpr auto end() const { return cursor(std::ranges::begin(m_base), size(), m_base.size()); }

    private:
        std::size_t size() const {
            return m_base.size() * (m_base.size() - 1) / 2;
        }

    };

    template <class R>
    pair_views(R&&)->pair_views<std::views::all_t<R>>;

    namespace detail {
        class pair_items_fn {
        public:
            template <std::ranges::viewable_range R>
            constexpr auto operator()(R&& r) const
            requires std::ranges::input_range<R> {
                //std::cout << "pair_items_fn" << std::endl;
                return tc::views::pair_views{std::forward<R>(r)};
            }
        };
    }
}

namespace views {
    inline tc::views::detail::pair_items_fn pair_items{};
}

#endif