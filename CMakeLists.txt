cmake_minimum_required(VERSION 3.16)
project(fs)

set(CMAKE_CXX_STANDARD 17)

find_package(Qt6 REQUIRED COMPONENTS Core)

add_executable(fs main.cpp)
target_link_libraries(fs Qt6::Core)
