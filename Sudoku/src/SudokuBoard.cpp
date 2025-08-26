#include "SudokuBoard.hpp"
#include <fstream>
#include <iomanip>

SudokuBoard::SudokuBoard() : board(BOARD_SIZE, std::vector<int>(BOARD_SIZE, 0)) {}

void SudokuBoard::initializeBoard(const std::vector<std::vector<int>> &initialBoard)
{
    if (initialBoard.size() == BOARD_SIZE && initialBoard[0].size() == BOARD_SIZE)
    {
        board = initialBoard;
    }
}

bool SudokuBoard::isValidMove(int row, int col, int value) const
{
    if (row < 0 || row >= BOARD_SIZE || col < 0 || col >= BOARD_SIZE)
    {
        return false;
    }

    if (value < 1 || value > 9)
    {
        return false;
    }

    if (board[row][col] != 0)
    {
        return false; // Cell already filled
    }

    return isValidInRow(row, value) &&
           isValidInColumn(col, value) &&
           isValidInBox((row / BOX_SIZE) * BOX_SIZE, (col / BOX_SIZE) * BOX_SIZE, value);
}

bool SudokuBoard::setValue(int row, int col, int value)
{
    if (isValidMove(row, col, value))
    {
        board[row][col] = value;
        return true;
    }
    return false;
}

int SudokuBoard::getValue(int row, int col) const
{
    if (row >= 0 && row < BOARD_SIZE && col >= 0 && col < BOARD_SIZE)
    {
        return board[row][col];
    }
    return -1; // Invalid position
}

bool SudokuBoard::isEmpty(int row, int col) const
{
    return getValue(row, col) == 0;
}

void SudokuBoard::printBoard() const
{
    std::cout << "-------------------------------------\n";

    for (int i = 0; i < BOARD_SIZE; i++)
    {
        for (int j = 0; j < BOARD_SIZE; j++)
        {
            if (board[i][j] == 0)
            {
                std::cout << ". ";
            }
            else
            {
                std::cout << board[i][j] << " ";
            }

            if (j % BOX_SIZE == BOX_SIZE - 1 && j != BOARD_SIZE - 1)
            {
                std::cout << "| ";
            }
        }
        std::cout << "\n";

        if (i % BOX_SIZE == BOX_SIZE - 1 && i != BOARD_SIZE - 1)
        {
            std::cout << "-------------------------------------\n";
        }
    }
    std::cout << "-------------------------------------\n";
}

bool SudokuBoard::loadFromFile(const std::string &filename)
{
    std::ifstream file(filename);
    if (!file.is_open())
    {
        return false;
    }

    for (int i = 0; i < BOARD_SIZE; i++)
    {
        for (int j = 0; j < BOARD_SIZE; j++)
        {
            if (!(file >> board[i][j]))
            {
                return false;
            }
        }
    }

    file.close();
    return true;
}

bool SudokuBoard::saveToFile(const std::string &filename) const
{
    std::ofstream file(filename);
    if (!file.is_open())
    {
        return false;
    }

    for (int i = 0; i < BOARD_SIZE; i++)
    {
        for (int j = 0; j < BOARD_SIZE; j++)
        {
            file << board[i][j];
            if (j != BOARD_SIZE - 1)
            {
                file << " ";
            }
        }
        file << "\n";
    }

    file.close();
    return true;
}

bool SudokuBoard::isFull() const
{
    for (int i = 0; i < BOARD_SIZE; i++)
    {
        for (int j = 0; j < BOARD_SIZE; j++)
        {
            if (board[i][j] == 0)
            {
                return false;
            }
        }
    }
    return true;
}

void SudokuBoard::clear()
{
    for (int i = 0; i < BOARD_SIZE; i++)
    {
        for (int j = 0; j < BOARD_SIZE; j++)
        {
            board[i][j] = 0;
        }
    }
}

bool SudokuBoard::isValidInRow(int row, int value) const
{
    for (int col = 0; col < BOARD_SIZE; col++)
    {
        if (board[row][col] == value)
        {
            return false;
        }
    }
    return true;
}

bool SudokuBoard::isValidInColumn(int col, int value) const
{
    for (int row = 0; row < BOARD_SIZE; row++)
    {
        if (board[row][col] == value)
        {
            return false;
        }
    }
    return true;
}

bool SudokuBoard::isValidInBox(int startRow, int startCol, int value) const
{
    for (int i = 0; i < BOX_SIZE; i++)
    {
        for (int j = 0; j < BOX_SIZE; j++)
        {
            if (board[startRow + i][startCol + j] == value)
            {
                return false;
            }
        }
    }
    return true;
}