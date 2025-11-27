cmake_minimum_required(VERSION 3.31)
project(game4)

set(CMAKE_CXX_STANDARD 20)

add_executable(game4 WORD_Classes.cpp
                            WORD_Demo.cpp)
configure_file(${CMAKE_SOURCE_DIR}/dic.txt ${CMAKE_BINARY_DIR}/dic.txt COPYONLY)
