cmake_minimum_required(VERSION 3.28)
project(LiteCompiler_C++)

set(CMAKE_CXX_STANDARD 17)

add_executable(LiteCompiler_C++ main.cpp
        src/debug/debug.h
        src/debug/debug.cpp
        src/Token/Token.h
        src/Token/Token.cpp
        src/LexicalAnalysis/Lexer.h
        src/LexicalAnalysis/Lexer.cpp
        src/FileHandler/FileHandler.h
        src/FileHandler/FileHandler.cpp
        src/error/error.h
        src/error/error.cpp
        src/LexicalAnalysis/isInvalidToken.h
        src/LexicalAnalysis/isInvalidToken.cpp
        src/Parser/Parser.h
        src/Parser/Parser.cpp
        src/Parser/AST.h
        src/Parser/AST.cpp
)
