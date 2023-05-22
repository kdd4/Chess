cmake_minimum_required(VERSION 3.10)

project(ChessLib VERSION 1.0.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -Og -Wall")
set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -Wall")

set(HEADERS "include/ChessLib/Chess.hpp" 
			"include/ChessLib/Board.hpp" 
			"include/ChessLib/Figure.hpp" 
			"include/ChessLib/Figures.hpp" 
			"include/ChessLib/Position.hpp" 
			"include/ChessLib/Move.hpp" 
			"include/ChessLib/Defines.hpp"
			)

set(SOURCES "src/Chess.cpp"
			"src/Board.cpp"
			"src/Figure.cpp"
			"src/Figures.cpp"
			"src/Position.cpp"
			"src/Move.cpp"
			"src/Defines.cpp"
			)

include_directories("include/")

add_library(ChessLib STATIC ${SOURCES} ${HEADERS})
