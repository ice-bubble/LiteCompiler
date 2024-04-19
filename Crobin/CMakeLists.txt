cmake_minimum_required(VERSION 3.28)
project(Crobin C)

set(CMAKE_C_STANDARD 11)

add_executable(Crobin main.c
        src/scanner/scanner.h
        src/scanner/scanner.c
        src/common.h
        src/debug/debug.h
        src/debug/debug.c
        src/memory/memory.h
        src/memory/memory.c
        src/token/token.h
        src/token/token.c
        src/environment/environment.h
        src/environment/environment.c
)
