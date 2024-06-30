cmake_minimum_required(VERSION 3.21)
project(Icicle)

set(CMAKE_CXX_STANDARD 20)
set(COMPILE_WARNING_AS_ERROR YES)

add_executable(Icicle src/main.cpp
        src/RCL/art_file.cpp
        src/RCL/art_file_entry.cpp
        src/RCL/directory.cpp
        src/RCL/directory_offset_table.cpp
        src/RCL/header.cpp
        src/RCL/rcl_file.cpp)
