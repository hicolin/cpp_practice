cmake_minimum_required(VERSION 3.31)
project(cpp_practice)


# 启用 FetchContent
include(FetchContent)

# 拉取 fmt 源码（指定版本，推荐固定 Tag）
FetchContent_Declare(
        fmt
        GIT_REPOSITORY https://github.com/fmtlib/fmt.git
        GIT_TAG 10.2.1  # 替换为你需要的版本（如 9.1.0、8.1.1）
)

# 编译 fmt 库
FetchContent_MakeAvailable(fmt)

set(CMAKE_CXX_STANDARD 20)

add_executable(cpp_practice main.cpp src/fmt.cpp src/defer.cpp)

# 链接 fmt
target_link_libraries(cpp_practice PRIVATE fmt::fmt)
