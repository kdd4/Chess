cmake_minimum_required(VERSION 3.10)

project(Chess VERSION 1.0.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O3 -Wall")

set(HEADERS "include/Chess/Chess.hpp" "include/Chess/Board.hpp" "include/Chess/Figure.hpp" "include/Chess/Figures.hpp" "include/Chess/Position.hpp" "include/Chess/Move.hpp" "include/Chess/Defines.hpp")
set(SOURCES "src/Chess.cpp" "src/Board.cpp" "src/Figure.cpp" "src/Figures.cpp" "src/Position.cpp" "src/Move.cpp" "src/Defines.cpp")

include_directories("include/")

add_library(Chess STATIC ${SOURCES} ${HEADERS})
