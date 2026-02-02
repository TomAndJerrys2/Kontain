cmake_minimum_required(VERSION 3.27)
project(kontain)
set(CMAKE_C_COMPILER /usr/bin/gcc)

if (MSVC)
	add_compile_options(/W4)
else()
	add_compile_options(-Wall -Werror -lcap -lseccomp) 
endif()

add_executable(${PROJECT_NAME} kontain.c)
