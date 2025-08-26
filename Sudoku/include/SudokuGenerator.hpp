#ifndef SUDOKU_GENERATOR_HPP
#define SUDOKU_GENERATOR_HPP

#include "SudokuBoard.hpp"
#include <random>

enum class Difficulty
{
    EASY,   // Remove ~40 cells
    MEDIUM, // Remove ~50 cells
    HARD    // Remove ~60 cells
};

class SudokuGenerator
{
private:
    static std::mt19937 rng;

    // Fill a diagonal 3x3 box with random numbers
    static void fillDiagonalBox(SudokuBoard &board, int row, int col);

    // Fill a complete valid Sudoku board
    static bool fillBoard(SudokuBoard &board);

    // Remove cells while ensuring unique solution
    static void removeCells(SudokuBoard &board, int cellsToRemove);

    // Check if puzzle has unique solution
    static bool hasUniqueSolution(const SudokuBoard &board);

    // Count solutions (used for uniqueness check)
    static int countSolutions(SudokuBoard board, int maxSolutions = 2);

public:
    // Generate a new Sudoku puzzle with specified difficulty
    static SudokuBoard generatePuzzle(Difficulty difficulty = Difficulty::MEDIUM);

    // Generate a completely filled valid Sudoku board
    static SudokuBoard generateComplete();

    // Set seed for random number generator
    static void setSeed(unsigned int seed);
};

#endif // SUDOKU_GENERATOR_HPP