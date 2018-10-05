cmake_minimum_required (VERSION 3.9)
project (algorithm)
set (algorithm_VERSION_MAJOR 0)
set (algorithm_VERSION_MINOR 1)
set (CMAKE_CXX_STANDARD 17)
set (CMAKE_CXX_STANDARD_REQUIRED ON)
set (CMAKE_CXX_EXTENSIONS OFF)
set (CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/CMakeModules)
set (CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(CATCH_INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/catch2)
set(BLOOM_FILTER_INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/bloom_filter)
set(HASH_INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/hash)
add_library (bloom_filter INTERFACE)
add_library(catch2 INTERFACE)
add_library(hash INTERFACE)

target_include_directories (bloom_filter INTERFACE ${BLOOM_FILTER_INCLUDE_DIR})
target_include_directories(catch2 INTERFACE ${CATCH_INCLUDE_DIR})
target_include_directories(hash INTERFACE ${HASH_INCLUDE_DIR})

file (GLOB SRCS test/*.cpp)
add_executable(test ${SRCS})

target_link_libraries(test
  bloom_filter
  catch2
  hash
)
