cmake_minimum_required(VERSION 4.0)

project (main)

set (EXECUTABLE_OUTPUT_PATH ${CMAKE_SOURCE_DIR}/bin)

aux_source_directory(src SRC_LIST)

include_directories(inc)

add_executable(main ${SRC_LIST})
