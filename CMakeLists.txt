cmake_minimum_required(VERSION 3.10)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE "Release" CACHE STRING "Choose Release or Debug" FORCE)
endif()
set(CMAKE_CXX_FLAGS_DEBUG "-Og -Wall -Wpedantic")
set(CMAKE_CXX_FLAGS_RELEASE "-Wall -Wpedantic")

option(WARMINGS_AS_ERRORS "Warmings cause errors" OFF)
if(WARMINGS_AS_ERRORS)
	set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -Werror")
	set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -Werror")
endif()

project(ChessLib VERSION 1.0.0 LANGUAGES CXX)

set(HEADERS "include/ChessLib/Chess.hpp" 
			"include/ChessLib/Board.hpp" 
			"include/ChessLib/Figure.hpp" 
			"include/ChessLib/Figures.hpp" 
			"include/ChessLib/Position.hpp" 
			"include/ChessLib/Move.hpp" 
			"include/ChessLib/Defines.hpp"
			)

set(SOURCES "src/ChessLib/Chess.cpp"
			"src/ChessLib/Board.cpp"
			"src/ChessLib/Figure.cpp"
			"src/ChessLib/Figures.cpp"
			"src/ChessLib/Position.cpp"
			"src/ChessLib/Move.cpp"
			"src/ChessLib/Defines.cpp"
			)

include_directories("include/")

add_library(ChessLib STATIC ${SOURCES} ${HEADERS})

option(BUILD_EXAMPLES "Build examples" OFF)
if(BUILD_EXAMPLES)
	add_subdirectory(examples)
endif()
