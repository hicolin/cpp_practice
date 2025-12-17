#include <iostream>
#include "src/fmt.h"
#include "src/defer.h"


int main() {
    std::cout << "Hello, World!" << std::endl;

    // fmt_test();

    defer_test();

    return 0;
}