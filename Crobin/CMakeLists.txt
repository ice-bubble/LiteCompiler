cmake_minimum_required(VERSION 3.28)
project(Crobin C)

set(CMAKE_C_STANDARD 11)

add_executable(Crobin main.c
        src/scanner/scanner.h
        src/scanner/scanner.c
        src/common.h
        src/debug/debug.h
        src/debug/debug.c)
