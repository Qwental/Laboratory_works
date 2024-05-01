cmake_minimum_required(VERSION 3.26)
project(23 C)

set(CMAKE_C_STANDARD 11)

add_executable(23 main.c
        tree_lib.h
        tree.c
        tree_lib.c)
