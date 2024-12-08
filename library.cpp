#include "include/lazy_read_file.h"

#include <iostream>
#include <string_view>
#include <cctype>
#include <thread>

int main() {
    try {
        const std::string filepath = "example.txt";

        // Read lines lazily and process them with std::transform.
        auto line_generator = tc::read_lines(filepath);
        for (std::string_view line; !(line = line_generator.next()).empty();) {
            std::string processed_line(line); // Convert string_view to string for modification.
            std::transform(processed_line.begin(), processed_line.end(), processed_line.begin(),
                           [](unsigned char c) {
                                std::this_thread::sleep_for(std::chrono::milliseconds(100));
                               return std::toupper(c);
                           });
            std::cout << processed_line << '\n';
        }
    } catch (const std::exception &ex) {
        std::cerr << "Error: " << ex.what() << '\n';
    }

    return 0;
}