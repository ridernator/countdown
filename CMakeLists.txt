cmake_minimum_required(VERSION 3.10)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

project(countdown VERSION 1.0)
add_compile_options(-Wall -Wextra -pedantic -Werror -O3)
add_executable(numbers numbers.cpp)
add_executable(letters letters.cpp)
