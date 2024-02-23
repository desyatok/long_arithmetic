cmake_minimum_required(VERSION 3.27)
project(long_arithmetic C)

set(CMAKE_C_STANDARD 11)

add_library(long_arithmetic STATIC bignum_lib.c)
