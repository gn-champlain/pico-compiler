cmake_minimum_required(VERSION 3.15)

project(PicoPPFrontend LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include_directories(include)

add_executable(pico_pp_frontend
    src/main.cpp
    src/token.cpp
    src/lexer.cpp
    src/ast.cpp
    src/parser.cpp
    src/semantic.cpp
    src/symbol_table.cpp
)
