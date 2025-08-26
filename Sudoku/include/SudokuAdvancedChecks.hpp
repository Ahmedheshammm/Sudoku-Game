#ifndef SUDOKU_ADVANCED_CHECKS_HPP
#define SUDOKU_ADVANCED_CHECKS_HPP

#include "SudokuBoard.hpp"
#include <vector>
#include <set>

class SudokuAdvancedChecks {
public:
    // Advanced solving techniques
    static bool nakedSingles(SudokuBoard& board);
    static bool hiddenSingles(SudokuBoard& board);
    static bool nakedPairs(SudokuBoard& board);
    static bool hiddenPairs(SudokuBoard& board);
    static bool lockedCandidates(SudokuBoard& board);
    
    // Apply all advanced techniques once
    static bool applyAllTechniques(SudokuBoard& board);
    
    // Solve using advanced techniques (no backtracking)
    static bool solveWithAdvancedTechniques(SudokuBoard& board);
    
    // Get possible values for a cell
    static std::set<int> getPossibleValues(const SudokuBoard& board, int row, int col);
    
    // Check if a value is the only possibility in a unit (row, column, or box)
    static bool isOnlyPossibilityInUnit(const SudokuBoard& board, int row, int col, int value);

private:
    // Helper functions for advanced techniques
    static bool processNakedPairsInUnit(SudokuBoard& board, const std::vector<std::pair<int, int>>& cells);
    static bool processHiddenPairsInUnit(SudokuBoard& board, const std::vector<std::pair<int, int>>& cells);
    static bool processLockedCandidatesInBox(SudokuBoard& board, int boxRow, int boxCol);
    
    // Get cells in a row, column, or box
    static std::vector<std::pair<int, int>> getRowCells(int row);
    static std::vector<std::pair<int, int>> getColumnCells(int col);
    static std::vector<std::pair<int, int>> getBoxCells(int boxRow, int boxCol);
};

#endif // SUDOKU_ADVANCED_CHECKS_HPP