cmake_minimum_required(VERSION 3.6)

project(redis_2_6_0)

set(CMAKE_CXX_STANDARD 11)

add_subdirectory(deps)

add_subdirectory(src)

add_subdirectory(tests)
