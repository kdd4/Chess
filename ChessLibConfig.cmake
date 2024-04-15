cmake_minimum_required(VERSION 3.21)

get_filename_component(SOURCES_DIR "${CMAKE_CURRENT_LIST_FILE}" DIRECTORY)

file(GLOB_RECURSE HEADERS ${SOURCES_DIR}/include/ChessLib/*.hpp)
file(GLOB_RECURSE SOURCES ${SOURCES_DIR}/src/*.cpp)

add_library(ChessLib STATIC ${SOURCES} ${HEADERS})

set_target_properties(ChessLib PROPERTIES
    CXX_STANDARD 17
    CXX_STANDARD_REQUIRED YES
    CXX_EXTENSIONS NO
)

target_include_directories(	ChessLib PUBLIC
							${SOURCES_DIR}/include
							)
