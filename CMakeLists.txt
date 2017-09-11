cmake_minimum_required(VERSION 3.7)
project(DNS_server)

set(CMAKE_C_STANDARD 11)

set(SOURCE_FILES main.c config.c config.h)
add_executable(DNS_server ${SOURCE_FILES})