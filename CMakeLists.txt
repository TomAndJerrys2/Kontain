cmake_minimum_required(VERSION 3.27)
project(kontain)
set(CMAKE_C_COMPILER /usr/bin/gcc)

add_compile_options(-Wall -Werror -lcap -lseccomp) 

add_executable(${build/kontain} kontain.h kontain.c syscalls.c resources.c)
