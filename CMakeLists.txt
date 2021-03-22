cmake_minimum_required(VERSION 3.17)
project(compiladores_textiles)

set(CMAKE_CXX_STANDARD 17)

add_executable(compiladores_textiles main.cpp TOKEN.cpp TOKEN.h Lexer.cpp Lexer.h FirstsAndFollows.cpp FirstsAndFollows.h)