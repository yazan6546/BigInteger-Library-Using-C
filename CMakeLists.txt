cmake_minimum_required(VERSION 3.25)
project(Proj C)

set(CMAKE_C_STANDARD 11)

add_executable(Proj main.c
        LinkedList/LinkedList.h
        LinkedList/LinkedList.c)

add_executable(bigInt_test test.c
        bigint.c
        LinkedList/LinkedList.c
        Arithmetic/arithmetic.c
        Arithmetic/add.c
        Arithmetic/subtract.c
        Arithmetic/division.c
        Arithmetic/multiplication.c
)