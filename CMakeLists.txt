cmake_minimum_required(VERSION 3.27)
project(GOST_R_34_11_94)

set(CMAKE_CXX_STANDARD 17)

add_executable(GOST_R_34_11_94 main.cpp
        hash.cpp
        hash.h
        test.h
        Utils.cpp
        Utils.h
)
