cmake_minimum_required(VERSION 3.21)
project(Icicle)

set(CMAKE_CXX_STANDARD 20)

add_executable(Icicle main.cpp RCL/Header.cpp RCL/DirectoryOffsetTable.cpp RCL/RclFile.cpp RCL/Directory.cpp RCL/ArtFile.cpp)
