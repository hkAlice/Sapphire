cmake_minimum_required(VERSION 2.6)
project (Sapphire_root)
 
set(EXECUTABLE_OUTPUT_PATH ${CMAKE_BINARY_DIR})
set(LIBRARY_OUTPUT_PATH ${CMAKE_BINARY_DIR})
 
set(PROJECT_INCLUDE_DIR ${PROJECT_SOURCE_DIR}/include)

include_directories("${PROJECT_INCLUDE_DIR}")
include_directories("${PROJECT_SOURCE_DIR}")

add_subdirectory(${PROJECT_SOURCE_DIR}/Common)
add_subdirectory(${PROJECT_SOURCE_DIR}/Sapphire_Lobby)
add_subdirectory(${PROJECT_SOURCE_DIR}/Sapphire_REST)
add_subdirectory(${PROJECT_SOURCE_DIR}/Sapphire_Zone)
