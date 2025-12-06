cmake_minimum_required(VERSION 4.0)
project(advent_of_code_2025)
set(CMAKE_CXX_STANDARD 20)

find_package(Boost REQUIRED)

add_executable(advent_of_code_2025
        day1/Day1.cpp
        day1/Day1.h
        day2/Day2.cpp
        day2/Day2.h
        day3/Day3.cpp
        day3/Day3.h
        day4/Day4.cpp
        day4/Day4.h
        day5/Day5.cpp
        day5/Day5.h
        runner.cpp)

target_compile_definitions(advent_of_code_2025 PRIVATE _GNU_SOURCE)
target_link_libraries(advent_of_code_2025 PRIVATE Boost::boost)
target_link_options(advent_of_code_2025 PRIVATE -rdynamic)
