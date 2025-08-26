#include "SudokuSolver.hpp"

bool SudokuSolver::solve(SudokuBoard& board) {
    return solveRecursive(board);
}

bool SudokuSolver::solveRecursive(SudokuBoard& board) {
    int row, col;
    
    // Find next empty cell
    if (!findEmptyCell(board, row, col)) {
        // No empty cell found, puzzle is solved
        return true;
    }
    
    // Try values 1-9
    for (int num = 1; num <= 9; num++) {
        if (board.isValidMove(row, col, num)) {
            // Temporarily place the number
            board.getBoard()[row][col] = num;
            
            // Recursively solve
            if (solveRecursive(board)) {
                return true;
            }
            
            // Backtrack if solution not found
            board.getBoard()[row][col] = 0;
        }
    }
    
    // No solution found
    return false;
}

bool SudokuSolver::isValidBoard(const SudokuBoard& board) {
    const auto& boardData = board.getBoard();
    
    // Check each cell
    for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 9; j++) {
            int value = boardData[i][j];
            
            if (value != 0) {
                // Temporarily remove the value to check validity
                const_cast<SudokuBoard&>(board).getBoard()[i][j] = 0;
                
                bool isValid = board.isValidMove(i, j, value);
                
                // Restore the value
                const_cast<SudokuBoard&>(board).getBoard()[i][j] = value;
                
                if (!isValid) {
                    return false;
                }
            }
        }
    }
    
    return true;
}

bool SudokuSolver::findEmptyCell(const SudokuBoard& board, int& row, int& col) {
    for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 9; j++) {
            if (board.isEmpty(i, j)) {
                row = i;
                col = j;
                return true;
            }
        }
    }
    return false;
}