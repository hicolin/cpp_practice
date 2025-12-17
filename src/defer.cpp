//
// Created by 81168 on 2025/12/17.
//

#include <iostream>
#include "defer.h"


void defer_test() {
    // defer 不推荐使用，容易导致错误，不同于 go 中的 defer

    defer(std::cout << "defer 1" << std::endl);
    // defer(std::cout << "defer 2" << std::endl); // error

    // int* p = nullptr;
    // {
    //     int a = 20;
    //     defer(std::cout << *p << std::endl); // 捕获p的引用  // 当前输出20只是栈内存未被覆盖的巧合，代码本身是错误的，存在崩溃风险。必须通过延长对象生命周期或值捕获的方式，避免访问野指针。
    //     p = &a;
    // } // a 销毁，p 成野指针，defer执行时崩溃
    // defer(std::cout << *p << std::endl); // 捕获p的引用

    std::cout << "defer 3" << std::endl;
}
