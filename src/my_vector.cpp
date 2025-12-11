//
// Created by 81168 on 2025/12/11.
//

#include <iostream>

template<typename T>
class MyVector {
public:
    MyVector() : _start(nullptr), _finish(nullptr), _end_of_storage(nullptr) {}

    explicit MyVector(size_t n) {
        reserve(n);
        for (int i = 0; i < n; ++i) {
            new(_start + i) T();
        }
        _finish = _start + n;
    }

    ~MyVector() {
        for (T *p = _start; p != _finish; ++p) {
            p->~T();
        }
        operator delete(_start);
    }

    MyVector(const MyVector &) = delete;
    MyVector &operator=(const MyVector &) = delete;

    MyVector(MyVector &&other) noexcept {
        _start = other._start;
        _finish = other._finish;
        _end_of_storage = other._end_of_storage;
        other._start = other._finish = other._end_of_storage = nullptr;
    }

    MyVector &operator=(MyVector &&other) noexcept {
        if (this != &other) {
            for (T *p = _start; p != _finish; ++p) {
                p->~T();
            }
            operator delete(_start);

            _start = other._start;
            _finish = other._finish;
            _end_of_storage = other._end_of_storage;
            other._start = other._finish = other._end_of_storage = nullptr;
        }

        return *this;
    }

    void push_back(const T &val) {
        if (_finish == _end_of_storage) {
            reserve(capacity() == 0 ? 1 : 2 * capacity());
        }

        new(_finish) T(val);
        ++_finish;
    }

    void push_back(T &&val) {
        if (_finish == _end_of_storage) {
            reserve(capacity() == 0 ? 1 : 2 * capacity());
        }

        new(_finish) T(std::move(val));
        ++_finish;
    }

    void pop_back() {
        if (empty()) {
            return;
        }
        --_finish;
        _finish->~T();
    }

    void reserve(size_t new_cap) {
        if (new_cap <= capacity()) {
            return;
        }

        T *new_start = (T *) operator new(new_cap * sizeof(T));
        size_t old_size = size();
        for (size_t i = 0; i < old_size; ++i) {
            new(new_start + i) T(std::move(_start[i]));
            _start[i].~T();
        }

        operator delete(_start);

        _start = new_start;
        _finish = new_start + old_size;
        _end_of_storage = new_start + new_cap;

    }

    T &operator[](size_t idx) {
        if (idx >= size()) {
            throw std::out_of_range("MyVector index out of range");
        }
        return _start[idx];
    }

    const T &operator[](size_t idx) const {
        if (idx >= size()) {
            throw std::out_of_range("MyVector index out of range");
        }
        return _start[idx];
    }


    [[nodiscard]] size_t size() const {
        return _finish - _start;
    }

    [[nodiscard]] size_t capacity() const {
        return _end_of_storage - _start;
    }

    [[nodiscard]] bool empty() const {
        return _start == _finish;
    }

private:
    T *_start;
    T *_finish;
    T *_end_of_storage;
};

int main() {
    MyVector<int> vec;
    vec.push_back(1);
    vec.push_back(2);
    vec.push_back(3); // push_back(T &&val)
    int a = 4;
    vec.push_back(a); // push_back(const T &val)

    std::cout << "size: " << vec.size() << ", capacity: " << vec.capacity() << std::endl;
    for (size_t i = 0; i < vec.size(); ++i) {
        std::cout << vec[i] << " ";
    }
    std::cout << std::endl;

    vec.pop_back();
    std::cout << "after pop_back, size: " << vec.size() << std::endl;

    return 0;
}