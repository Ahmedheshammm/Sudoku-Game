#include "SudokuGenerator.hpp"
#include "SudokuSolver.hpp"
#include <algorithm>
#include <chrono>
#include <random>
#include <vector>

std::mt19937 SudokuGenerator::rng(std::chrono::steady_clock::now().time_since_epoch().count());

SudokuBoard SudokuGenerator::generatePuzzle(Difficulty difficulty)
{
    // First generate a complete board
    SudokuBoard board = generateComplete();

    // Determine how many cells to remove based on difficulty
    int cellsToRemove;
    switch (difficulty)
    {
    case Difficulty::EASY:
        cellsToRemove = 40;
        break;
    case Difficulty::MEDIUM:
        cellsToRemove = 50;
        break;
    case Difficulty::HARD:
        cellsToRemove = 60;
        break;
    default:
        cellsToRemove = 50;
        break;
    }

    // Remove cells while ensuring unique solution
    removeCells(board, cellsToRemove);

    return board;
}

SudokuBoard SudokuGenerator::generateComplete()
{
    SudokuBoard board;

    // Fill diagonal 3x3 boxes first (they don't interfere with each other)
    for (int box = 0; box < 3; box++)
    {
        fillDiagonalBox(board, box * 3, box * 3);
    }

    // Fill remaining cells
    if (SudokuSolver::solve(board))
    {
        return board;
    }

    // If somehow we can't solve, try again (very rare)
    return generateComplete();
}

void SudokuGenerator::fillDiagonalBox(SudokuBoard &board, int row, int col)
{
    std::vector<int> numbers = {1, 2, 3, 4, 5, 6, 7, 8, 9};
    std::shuffle(numbers.begin(), numbers.end(), rng);

    int index = 0;
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            board.getBoard()[row + i][col + j] = numbers[index++];
        }
    }
}

bool SudokuGenerator::fillBoard(SudokuBoard &board)
{
    return SudokuSolver::solve(board);
}

void SudokuGenerator::removeCells(SudokuBoard &board, int cellsToRemove)
{
    // Create list of all cell positions
    std::vector<std::pair<int, int>> positions;
    for (int i = 0; i < 9; i++)
    {
        for (int j = 0; j < 9; j++)
        {
            positions.push_back({i, j});
        }
    }

    // Shuffle positions
    std::shuffle(positions.begin(), positions.end(), rng);

    int removed = 0;
    for (auto &pos : positions)
    {
        if (removed >= cellsToRemove)
            break;

        int row = pos.first;
        int col = pos.second;
        int backup = board.getValue(row, col);

        // Temporarily remove the cell
        board.getBoard()[row][col] = 0;

        // Check if puzzle still has unique solution
        if (hasUniqueSolution(board))
        {
            removed++;
        }
        else
        {
            // Restore the cell if removing it makes puzzle non-unique
            board.getBoard()[row][col] = backup;
        }
    }
}

bool SudokuGenerator::hasUniqueSolution(const SudokuBoard &board)
{
    return countSolutions(board, 2) == 1;
}

int SudokuGenerator::countSolutions(SudokuBoard board, int maxSolutions)
{
    int row, col;
    if (!SudokuSolver::findEmptyCell(board, row, col))
    {
        return 1; // Puzzle is complete
    }

    int solutionCount = 0;

    for (int num = 1; num <= 9 && solutionCount < maxSolutions; num++)
    {
        if (board.isValidMove(row, col, num))
        {
            board.getBoard()[row][col] = num;
            solutionCount += countSolutions(board, maxSolutions - solutionCount);
            board.getBoard()[row][col] = 0;
        }
    }

    return solutionCount;
}

void SudokuGenerator::setSeed(unsigned int seed)
{
    rng.seed(seed);
}