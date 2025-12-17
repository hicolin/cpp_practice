//
// Created by 81168 on 2025/12/17.
//

#pragma once
#include <functional>

class Defer {
public:
    explicit Defer(std::function<void()> func) : func(std::move(func)) {
    }

    ~Defer() {
        if (func) {
            // 防止空函数调用
            func();
        }
    }

    // 禁用拷贝，避免重复执行
    Defer(const Defer &) = delete;

    Defer &operator=(const Defer &) = delete;

    // 允许移动（可选）
    Defer(Defer &&) = default;

    Defer &operator=(Defer &&) = default;

private:
    std::function<void()> func;
};

#define defer(x) Defer defer_obj##__LINE__([&](){x;})

void defer_test();
