cmake_minimum_required(VERSION 3.21)

project(ChessConsole VERSION 1.0.0 LANGUAGES CXX)

add_executable(ChessConsole "main.cpp")

target_link_libraries(ChessConsole PUBLIC ChessLib)