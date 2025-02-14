cmake_minimum_required(VERSION 3.10) 
project(Theta VERSION 1.0 LANGUAGES C)  

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_C_EXTENSIONS OFF)

set(SRC_FILES
    src/main.c
    src/move.c
		src/state.c
		src/bitboard.c
)

include_directories(include)

add_executable(theta ${SRC_FILES})

target_compile_options(theta PRIVATE
		-Wall
		-Werror
		-O2
		-Wpedantic
)


