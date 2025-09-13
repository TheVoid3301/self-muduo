cmake_minimum_required(VERSION 2.5)
project(self-muduo)

set(LIBRARY_OUTPUT_PUTH ${PROJECT_SOURCE_DIR}/lib)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g -std=c++14")

aux_source_directory(. SRC_LIST)

add_library(self-muduo SHARED ${SRC_LIST})