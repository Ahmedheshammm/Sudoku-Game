cmake_minimum_required(VERSION 3.10)
project(SudokuProject)

# Use C++17
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Core source files
set(SOURCES
    SudokuBoard.cpp
    SudokuSolver.cpp
    SudokuGame.cpp
    SudokuGenerator.cpp
    SudokuAdvancedChecks.cpp
    main.cpp
)

# Create the final executable
add_executable(SudokuProject ${SOURCES})

# Set compiler flags for MinGW
if(MINGW)
    target_compile_options(SudokuProject PRIVATE -mconsole)
    target_link_options(SudokuProject PRIVATE -mconsole)
endif()