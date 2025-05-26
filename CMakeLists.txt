cmake_minimum_required(VERSION 3.16)
project(OOP_Tetris)

set(CMAKE_CXX_STANDARD 17)

include_directories(
	blocks/base
	blocks/normal
	blocks/special
	brick
	board
	core
	domain
	presentation
	utils
)

file(GLOB_RECURSE SOURCES
	main.cpp
	blocks/**/*.cpp
	brick/*.cpp
	board/*.cpp
	core/*.cpp
	domain/*.cpp
	presentation/*.cpp
	utils/*.cpp
)

add_executable(OOP_Tetris ${SOURCES})