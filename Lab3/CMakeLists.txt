cmake_minimum_required(VERSION 3.21)
project(Lab3_Graph)

set(CMAKE_CXX_STANDARD 23)

add_executable(Lab3_Graph main.cpp Graph_mr.h Graph_ms.h Vertex.h Test.h)
set(CMAKE_CXX_FLAGS_RELEASE "-O3")