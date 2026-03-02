cmake_minimum_required(VERSION 3.10)

project(cmake_demo LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(cmake_demo
    src/main.cpp
    src/MyLinkedList.cpp
)

target_include_directories(cmake_demo
    PRIVATE
        ${CMAKE_SOURCE_DIR}/include
)
