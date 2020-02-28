cmake_minimum_required(VERSION 3.15)
project(popolvar C)

set(CMAKE_C_STANDARD 99)

add_executable(popolvar main.c min_heap.c min_heap.h node.h node.c dijkstra.c dijkstra.h)