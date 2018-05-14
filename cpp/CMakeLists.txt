cmake_minimum_required(VERSION 3.0.0 )

project(tire LANGUAGES CXX)

set(SRCS
tire/main.cpp
tire/my_tire.cpp
tire/my_tire.h
)
include_directories(tire)

source_group(sources FILES ${SRCS})

add_executable(t ${SRCS})

