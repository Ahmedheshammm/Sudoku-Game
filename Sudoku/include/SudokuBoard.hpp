#ifndef SUDOKU_BOARD_HPP
#define SUDOKU_BOARD_HPP

#include <vector>
#include <string>
#include <iostream>

class SudokuBoard
{
private:
    static const int BOARD_SIZE = 9;
    static const int BOX_SIZE = 3;
    std::vector<std::vector<int>> board;

public:
    // Constructor
    SudokuBoard();

    // Initialize board with given data
    void initializeBoard(const std::vector<std::vector<int>> &initialBoard);

    // Board operations
    bool isValidMove(int row, int col, int value) const;
    bool setValue(int row, int col, int value);
    int getValue(int row, int col) const;
    bool isEmpty(int row, int col) const;

    // Display
    void printBoard() const;

    // File operations
    bool loadFromFile(const std::string &filename);
    bool saveToFile(const std::string &filename) const;

    // Utility
    bool isFull() const;
    void clear();
    std::vector<std::vector<int>> &getBoard() { return board; }
    const std::vector<std::vector<int>> &getBoard() const { return board; }

    // Validation helpers
    bool isValidInRow(int row, int value) const;
    bool isValidInColumn(int col, int value) const;
    bool isValidInBox(int startRow, int startCol, int value) const;
};

#endif // SUDOKU_BOARD_HPP