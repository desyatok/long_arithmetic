cmake_minimum_required(VERSION 3.22)
project(long_arithmetic C)

set(CMAKE_C_STANDARD 11)

add_library(long_arithmetic STATIC bignum_lib.c)
add_library(minunit INTERFACE minunit.h)

add_executable(tests tests.c)

target_link_libraries(tests long_arithmetic minunit)

enable_testing()
add_test(test_package tests)
