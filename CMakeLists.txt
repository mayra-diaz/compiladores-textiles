cmake_minimum_required(VERSION 3.17)
project(compiladores_textiles)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(compiladores_textiles
        FirstsAndFollows.cpp
        FirstsAndFollows.h
        Lexer.cpp
        Lexer.h
        main.cpp
        TOKEN.cpp
        TOKEN.h)
