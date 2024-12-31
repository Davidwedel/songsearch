cmake_minimum_required(VERSION 3.16)
project(GrepFileSearch)

set(CMAKE_CXX_STANDARD 17)

find_package(Qt6 REQUIRED COMPONENTS Core)

add_executable(GrepFileSearch main.cpp)
target_link_libraries(GrepFileSearch Qt6::Core)
