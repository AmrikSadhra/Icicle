cmake_minimum_required(VERSION 3.21)
project(Icicle)

set(CMAKE_CXX_STANDARD 20)

add_executable(Icicle src/main.cpp
                      src/RCL/Header.cpp
                      src/RCL/DirectoryOffsetTable.cpp
                      src/RCL/RclFile.cpp
                      src/RCL/Directory.cpp
                      src/RCL/ArtFile.cpp
                      src/RCL/ArtFileEntry.cpp)
