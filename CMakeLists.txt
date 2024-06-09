cmake_minimum_required(VERSION 3.25)
project(Proj C)

set(CMAKE_C_STANDARD 11)

add_executable(Proj main.c
        LinkedList/LinkedList.h
        LinkedList/LinkedList.c)

