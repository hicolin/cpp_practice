//
// Created by 81168 on 2025/12/16.
//

#include <iostream>
#include <fmt/format.h>

// #define FMT_HEADER_ONLY
// #include "third_party/fmt/format.h"

void fmt_test() {
    const std::string message = fmt::format("The answer is {}.", 42);
    std::cout << message << std::endl;
}
