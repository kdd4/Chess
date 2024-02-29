cmake_minimum_required(VERSION 3.21)

if (CMAKE_CXX_COMPILER_ID MATCHES GNU OR CMAKE_CXX_COMPILER_ID MATCHES Clang)
	if(NOT CMAKE_BUILD_TYPE)
		set(CMAKE_BUILD_TYPE "Release" CACHE STRING "Choose Release or Debug" FORCE)
	endif()

	set(CMAKE_CXX_FLAGS "-Wall -Wpedantic")
	set(CMAKE_CXX_FLAGS_DEBUG "-g")
	set(CMAKE_CXX_FLAGS_RELEASE "-O3")

	option(WARNINGS_AS_ERRORS "Warmings cause errors" OFF)
	if(WARNINGS_AS_ERRORS)
		set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Werror")
	endif()
endif()

if (CMAKE_CXX_COMPILER_ID MATCHES MSVC)
	set(CMAKE_CXX_FLAGS "/Wall")
	set(CMAKE_CXX_FLAGS_RELEASE "/O2")
endif()

project(ChessLib VERSION 1.0.0 LANGUAGES CXX)

include(ChessLibConfig.cmake)
							
option(BUILD_EXAMPLES "Build examples" ON)
if(BUILD_EXAMPLES)
	add_subdirectory(examples)
endif()
