cmake_minimum_required(VERSION 3.28)
project(FileUtilsV2 C)

set(CMAKE_C_STANDARD 11)

add_executable(FileUtilsV2 main.c
        src/core/User.database.c
        src/core/User.database.h
)
