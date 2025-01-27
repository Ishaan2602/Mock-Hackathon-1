cmake_minimum_required(VERSION 3.30)
project(mock_hackathon_1)

set(CMAKE_CXX_STANDARD 20)

add_executable(mock_hackathon_1 src/main.cpp
        src/parser.cpp
        src/lexer.cpp)
