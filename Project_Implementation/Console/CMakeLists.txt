cmake_minimum_required(VERSION 3.8)
project(SudokuProject)

# Use C++17 (adjust if you need a different standard)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Create options for optional features
option(BUILD_GENERATOR "Build the SudokuGenerator module for puzzle generation" ON)
option(BUILD_ADVANCED "Build the SudokuAdvancedChecks module for advanced Sudoku logic" ON)

# Core source files
set(SOURCES
    ../SudokuGame/src/FileManager.cpp
    ../SudokuGame/src/SudokuBoard.cpp
    ../SudokuGame/src/SudokuSolver.cpp
    src/SudokuInterface.cpp
    main.cpp
)

# Header files (not strictly required for add_executable, but good for clarity)
set(HEADERS
    ../SudokuGame/include/FileManager.hpp
    ../SudokuGame/include/SudokuBoard.hpp
    ../SudokuGame/include/SudokuSolver.hpp
    include/SudokuInterface.hpp
)

# If building puzzle generator, include its source/header
if(BUILD_GENERATOR)
    list(APPEND SOURCES ../SudokuGame/src/SudokuGenerator.cpp)
    list(APPEND HEADERS ../SudokuGame/include/SudokuGenerator.hpp)
endif()

# If building advanced checks, include those source/header
# if(BUILD_ADVANCED)
#     list(APPEND SOURCES SudokuAdvancedChecks.cpp)
#     list(APPEND HEADERS SudokuAdvancedChecks.hpp)
# endif()

# Create the final executable
add_executable(SudokuProject ${SOURCES} ${HEADERS})

# For example usage, you might do:
#    cmake -S . -B build -DBUILD_GENERATOR=OFF -DBUILD_ADVANCED=OFF
#    cmake --build build
#
# In that case, the project will build without the optional modules.
