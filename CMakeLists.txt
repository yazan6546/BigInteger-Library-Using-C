cmake_minimum_required(VERSION 3.25)
project(Proj C)

set(CMAKE_C_STANDARD 11)

# Source files
set(CORE_SOURCES src/core/bigint.c)
set(ARITHMETIC_SOURCES
        src/arithmetic/add.c
        src/arithmetic/subtract.c
        src/arithmetic/multiplication.c
        src/arithmetic/division.c
        src/arithmetic/arithmetic.c
)
set(UTILS_SOURCES src/utils/LinkedList.c)

# Create static library
add_library(bigint STATIC
        ${CORE_SOURCES}
        ${ARITHMETIC_SOURCES}
        ${UTILS_SOURCES}
)

# Include directories
target_include_directories(bigint
        PUBLIC include              # Only bigint.h is public
        PRIVATE src                 # All other headers are private
)