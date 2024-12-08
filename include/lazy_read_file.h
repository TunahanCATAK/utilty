#ifndef TC_LAZY_READ_FILE_H
#define TC_LAZY_READ_FILE_H

#include <string>
#include <string_view>
#include <fstream>
#include <stdexcept>
#include <coroutine>
#include <iostream>

namespace tc {

class line_generator {
public:
    struct promise_type {
        std::string current_line;

        auto get_return_object() {
            return line_generator{std::coroutine_handle<promise_type>::from_promise(*this)};
        }

        std::suspend_always initial_suspend() noexcept { return {}; }

        std::suspend_always final_suspend() noexcept { return {}; }

        std::suspend_always yield_value(std::string_view line) noexcept {
            current_line = line;
            return {};
        }

        void return_void() {}

        void unhandled_exception() {
            throw;
        }
    };

    using handle_type = std::coroutine_handle<promise_type>;

    explicit line_generator(handle_type handle) : coro_handle(handle) {}

    ~line_generator() {
        if (coro_handle) coro_handle.destroy();
    }

    line_generator(const line_generator&) = delete;
    line_generator& operator=(const line_generator&) = delete;

    line_generator(line_generator&& other) noexcept : coro_handle(other.coro_handle) {
        other.coro_handle = nullptr;
    }

    line_generator& operator=(line_generator&& other) noexcept {
        if (this != &other) {
            if (coro_handle) coro_handle.destroy();
            coro_handle = other.coro_handle;
            other.coro_handle = nullptr;
        }
        return *this;
    }

    std::string_view next() {
        if (coro_handle && !coro_handle.done()) {
            coro_handle.resume();
            return coro_handle.done() ? std::string_view{} : coro_handle.promise().current_line;
        }
        return {};
    }

private:
    handle_type coro_handle;
};

line_generator read_lines(const std::string& filepath) {
    std::ifstream file(filepath, std::ios::in | std::ios::binary);
    if (!file.is_open()) {
        throw std::runtime_error("Failed to open file: " + filepath);
    }

    std::string line;
    while (std::getline(file, line)) {
        // Remove carriage return (\r) for Windows line endings.
        if (!line.empty() && line.back() == '\r') {
            line.pop_back();
        }
        co_yield line;
    }
}
}

#endif //TC_LAZY_READ_FILE_H
