cmake_minimum_required(VERSION 3.14)

set(CMAKE_CXX_FLAGS "-std=c++11 -Werror -Wall -O3 -Wpedantic -msse4.1 -Wpsabi -march=native")
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -msse4.1 -maes -mavx")

add_executable(Assignment2 "Problem2/assignment2.cpp")
add_executable(Assignment2Tests "Problem2/assignment2_tests.cpp")

add_executable(Assignment1 "Problem1/assignment1.cpp")
add_executable(Assignment1Tests "Problem1/assignment1_tests.cpp")