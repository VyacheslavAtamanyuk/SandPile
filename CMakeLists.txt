cmake_minimum_required(VERSION 3.0.0)

project(
        labwork3
        VERSION 1.0
        LANGUAGES CXX
)

set(CMAKE_CXX_STANDARD 17)

add_executable(labwork3 main.cpp ParseCommandLine.cpp ParseCommandLine.h SandPile.cpp SandPile.h BMP_READER.h)