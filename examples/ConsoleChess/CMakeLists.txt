cmake_minimum_required(VERSION 3.10)

project(ChessConsole VERSION 1.0.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDART_REQUIRED TRUE)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O3 -Wall")

set(HEADERS "")
set(SOURCES "main.cpp")

add_executable(ChessConsole ${SOURCES} ${HEADERS})

#add_subdirectory("ChessLib/")
target_link_libraries(ChessConsole PUBLIC ChessLib)
target_include_directories(ChessConsole PUBLIC
                          "${PROJECT_SOURCE_DIR}/ChessLib/include"
                          )