cmake_minimum_required(VERSION 2.8.12)
project(hexll C)

add_executable(${PROJECT_NAME} src/main.c)
target_compile_options(${PROJECT_NAME} PRIVATE -Wall -Werror -Wconversion -pedantic)
