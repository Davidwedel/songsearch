cmake_minimum_required(VERSION 3.16)
project(filesearch)

set(CMAKE_CXX_STANDARD 17)

find_package(Qt6 REQUIRED COMPONENTS Core)

add_executable(filesearch main.cpp)
target_link_libraries(filesearch Qt6::Core)
