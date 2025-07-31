cmake_minimum_required(VERSION 3.25)
project(Proj C CXX)

set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)

# Add the path to your custom find modules
list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake")

option(BUILD_TESTING "Enable testing" ON)

message(STATUS "TESTING IS " ${BUILD_TESTING})

# Source files
set(CORE_SOURCES src/core/bigint.c)
set(ARITHMETIC_SOURCES
        src/arithmetic/add.c
        src/arithmetic/subtract.c
        src/arithmetic/multiplication.c
        src/arithmetic/division.c
        src/arithmetic/arithmetic.c
)
set(UTILS_SOURCES ${CMAKE_SOURCE_DIR}/src/utils/LinkedList.c)

# Create static library
add_library(bigint STATIC
        ${CORE_SOURCES}
        ${ARITHMETIC_SOURCES}
        ${UTILS_SOURCES}
)

# Include directories
target_include_directories(bigint
        PUBLIC include              # Only bigint.h is public
        PUBLIC src                 # All other headers are private
)

# Add tests only if BUILD_TESTING is enabled
if(BUILD_TESTING)
    include(cmake/tests.cmake)
    find_package(GTest REQUIRED)
    enable_testing()
    add_subdirectory(tests)
endif()