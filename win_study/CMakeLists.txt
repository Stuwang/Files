	cmake_minimum_required(VERSION 3.0.0)

project(WinStudy)

set(SIMPLE_SOURCES
	src/main.cpp
	)

set(WIN_PROCESS_SRCS
	src/process.cpp
	src/net.cpp
	src/net.h
	)

set(BASE_SRCS
	src/base.h
	src/base.cpp
	src/logger.h
	src/logger.cpp
	)

add_definitions(-DUNICODE)

include_directories(src)

add_library(base STATIC ${BASE_SRCS})

add_executable(Simple ${SIMPLE_SOURCES})
target_link_libraries(Simple base)

add_executable(ChildProcess ${WIN_PROCESS_SRCS})
target_link_libraries(ChildProcess base)
target_link_libraries(ChildProcess ws2_32.lib)