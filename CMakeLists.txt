cmake_minimum_required(VERSION 3.20)
project(mmn23 C)

set(CMAKE_C_STANDARD 90)

add_executable(mmn23 seek.c seek_records.c seek_records.h)
