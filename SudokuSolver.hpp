#ifndef SUDOKU_SOLVER_HPP
#define SUDOKU_SOLVER_HPP

#include "SudokuBoard.hpp"

class SudokuSolver
{
public:
    // Solve the sudoku puzzle using backtracking
    static bool solve(SudokuBoard &board);

    // Check if the current board state is valid
    static bool isValidBoard(const SudokuBoard &board);

    // Find the next empty cell
    static bool findEmptyCell(const SudokuBoard &board, int &row, int &col);

private:
    // Recursive backtracking helper
    static bool solveRecursive(SudokuBoard &board);
};

#endif // SUDOKU_SOLVER_HPP