//#include <iostream>
//#include <utility>  // for std::move
//
//template<typename T>
//class MyVector {
//public:
//    // 空构造函数
//    MyVector() : _start(nullptr), _finish(nullptr), _end_of_storage(nullptr) {}
//
//    // 带初始大小的构造函数
//    explicit MyVector(size_t n) {
//        reserve(n);  // 预留n个空间
//        for (size_t i = 0; i < n; ++i) {
//            // 定位new构造默认对象
//            new(_start + i) T();
//        }
//        _finish = _start + n;
//    }
//
//    // 析构函数：先析构元素，再释放内存
//    ~MyVector() {
//        // 遍历销毁所有已构造的元素
//        for (T *p = _start; p != _finish; ++p) {
//            p->~T();
//        }
//        // 释放整块内存
//        operator delete(_start);
//    }
//
//    // 禁用拷贝构造和拷贝赋值（简化版，避免浅拷贝问题）
//    MyVector(const MyVector &) = delete;
//
//    MyVector &operator=(const MyVector &) = delete;
//
//    // 移动构造：转移资源所有权
//    MyVector(MyVector &&other) noexcept {
//        _start = other._start;
//        _finish = other._finish;
//        _end_of_storage = other._end_of_storage;
//        // 置空原对象，避免析构时重复释放
//        other._start = other._finish = other._end_of_storage = nullptr;
//    }
//
//    // 移动赋值
//    MyVector &operator=(MyVector &&other) noexcept {
//        if (this != &other) {
//            // 销毁当前对象的元素并释放内存
//            for (T *p = _start; p != _finish; ++p) {
//                p->~T();
//            }
//            operator delete(_start);
//
//            // 转移资源
//            _start = other._start;
//            _finish = other._finish;
//            _end_of_storage = other._end_of_storage;
//            other._start = other._finish = other._end_of_storage = nullptr;
//        }
//        return *this;
//    }
//
//    // ========== 核心功能 ==========
//    // 尾部插入（拷贝版本）
//    void push_back(const T &val) {
//        // 检查容量，不足则扩容
//        if (_finish == _end_of_storage) {
//            reserve(capacity() == 0 ? 1 : 2 * capacity());
//        }
//        // 在_finish位置构造对象
//        new(_finish) T(val);
//        ++_finish;
//    }
//
//    // 尾部插入（移动版本）
//    void push_back(T &&val) {
//        if (_finish == _end_of_storage) {
//            reserve(capacity() == 0 ? 1 : 2 * capacity());
//        }
//        new(_finish) T(std::move(val));
//        ++_finish;
//    }
//
//    // 尾部删除
//    void pop_back() {
//        if (empty()) {
//            return;
//        }
//        --_finish;
//        // 销毁最后一个元素
//        _finish->~T();
//    }
//
//    // 预留空间（只扩容不构造元素）
//    void reserve(size_t new_cap) {
//        if (new_cap <= capacity()) {
//            return;
//        }
//
//        // 1. 分配新的原始内存
//        T *new_start = (T *) operator new(new_cap * sizeof(T));
//        size_t old_size = size();
//
//        // 2. 移动原元素到新内存
//        for (size_t i = 0; i < old_size; ++i) {
//            new(new_start + i) T(std::move(_start[i]));
//            _start[i].~T();  // 销毁原元素
//        }
//
//        // 3. 释放原内存
//        operator delete(_start);
//
//        // 4. 更新指针
//        _start = new_start;
//        _finish = new_start + old_size;
//        _end_of_storage = new_start + new_cap;
//    }
//
//    // ========== 访问功能 ==========
//    // 随机访问（非const版本）
//    T &operator[](size_t idx) {
//        // 简单越界检查（生产环境可抛异常）
//        if (idx >= size()) {
//            throw std::out_of_range("MyVector index out of range");
//        }
//        return _start[idx];
//    }
//
//    // 随机访问（const版本）
//    const T &operator[](size_t idx) const {
//        if (idx >= size()) {
//            throw std::out_of_range("MyVector index out of range");
//        }
//        return _start[idx];
//    }
//
//    // ========== 状态查询 ==========
//    // 元素个数
//    size_t size() const {
//        return _finish - _start;
//    }
//
//    // 容量
//    size_t capacity() const {
//        return _end_of_storage - _start;
//    }
//
//    // 是否为空
//    bool empty() const {
//        return _start == _finish;
//    }
//
//private:
//    T *_start;         // 指向数组起始
//    T *_finish;        // 指向已用空间末尾
//    T *_end_of_storage;// 指向内存末尾
//};
//
//// 测试代码
//int main() {
//    MyVector<int> vec;
//    vec.push_back(1);
//    vec.push_back(2);
//    vec.push_back(3);
//
//    std::cout << "size: " << vec.size() << ", capacity: " << vec.capacity() << std::endl;
//    for (size_t i = 0; i < vec.size(); ++i) {
//        std::cout << vec[i] << " ";
//    }
//    std::cout << std::endl;
//
//    vec.pop_back();
//    std::cout << "after pop_back, size: " << vec.size() << std::endl;
//
//    return 0;
//}