#include "SudokuGame.hpp"
#include "SudokuSolver.hpp"
#include <iostream>
#include <limits>
#include <sstream>

#ifdef BUILD_GENERATOR
#include "SudokuGenerator.hpp"
#endif

#ifdef BUILD_ADVANCED
#include "SudokuAdvancedChecks.hpp"
#endif

SudokuGame::SudokuGame() : gameRunning(true)
{
    initializeDefaultPuzzle();
}

void SudokuGame::run()
{
    std::cout << "Welcome to Sudoku Game!\n\n";

    while (gameRunning)
    {
        board.printBoard();
        displayMenu();

        int choice = getMenuChoice();

        switch (choice)
        {
        case 1:
            enterMove();
            break;
        case 2:
            solveAutomatically();
            break;
        case 3:
            loadPuzzleFromFile();
            break;
        case 4:
            savePuzzleToFile();
            break;
#ifdef BUILD_GENERATOR
        case 5:
            generateNewPuzzle();
            break;
#endif
#ifdef BUILD_ADVANCED
        case 6:
            solveWithAdvancedTechniques();
            break;
#endif
        default:
            // Handle exit option dynamically
            int exitOption = 5;
#ifdef BUILD_GENERATOR
            exitOption = 6;
#endif
#ifdef BUILD_ADVANCED
            exitOption = 7;
#endif
            if (choice == exitOption)
            {
                quit();
            }
            else
            {
                std::cout << "Invalid choice. Please select a valid option.\n\n";
            }
            break;
        }
    }
}

void SudokuGame::displayMenu()
{
    std::cout << "1) Enter a move\n";
    std::cout << "2) Solve automatically\n";
    std::cout << "3) Load puzzle from file\n";
    std::cout << "4) Save current puzzle to file\n";

#ifdef BUILD_GENERATOR
    std::cout << "5) Generate new puzzle\n";
#endif

#ifdef BUILD_ADVANCED
    std::cout << "6) Solve with advanced techniques\n";
#endif

    // Exit option adjusts based on optional features
    int exitOption = 5;
#ifdef BUILD_GENERATOR
    exitOption = 6;
#endif
#ifdef BUILD_ADVANCED
    exitOption = 7;
#endif

    std::cout << exitOption << ") Exit\n";
    std::cout << "Choice: ";
}

int SudokuGame::getMenuChoice()
{
    int choice;
    if (getIntegerInput(choice, ""))
    {
        return choice;
    }
    return -1; // Invalid input
}

void SudokuGame::enterMove()
{
    int row, col, value;

    std::cout << "Enter row (1-9), column (1-9), and value (1-9): ";

    if (!(std::cin >> row >> col >> value))
    {
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cout << "Invalid input. Please enter three integers.\n\n";
        return;
    }

    // Validate ranges
    if (!isValidRange(row, 1, 9))
    {
        std::cout << "Row must be between 1 and 9.\n\n";
        return;
    }

    if (!isValidRange(col, 1, 9))
    {
        std::cout << "Column must be between 1 and 9.\n\n";
        return;
    }

    if (!isValidRange(value, 1, 9))
    {
        std::cout << "Value must be between 1 and 9.\n\n";
        return;
    }

    // Convert to 0-based indexing
    row--;
    col--;

    // Check if cell is already filled or move is invalid
    if (!board.isEmpty(row, col) || !board.isValidMove(row, col, value))
    {
        std::cout << "Invalid move. That cell might be occupied or the placement breaks Sudoku rules.\n\n";
        return;
    }

    // Attempt to set the value
    if (board.setValue(row, col, value))
    {
        std::cout << "Move accepted!\n\n";

        // Check if puzzle is solved
        if (board.isFull())
        {
            std::cout << "Great job! The Sudoku is solved!\n\n";
        }
    }
    else
    {
        std::cout << "Invalid move. That cell might be occupied or the placement breaks Sudoku rules.\n\n";
    }
}

void SudokuGame::solveAutomatically()
{
    std::cout << "Solving puzzle...\n";

    if (SudokuSolver::solve(board))
    {
        std::cout << "Puzzle solved!\n\n";
    }
    else
    {
        std::cout << "No solution found. The puzzle may be unsolvable.\n\n";
    }
}

void SudokuGame::loadPuzzleFromFile()
{
    std::string filename;
    std::cout << "Enter filename: ";
    std::cin >> filename;

    if (board.loadFromFile(filename))
    {
        std::cout << "Puzzle loaded successfully!\n\n";
    }
    else
    {
        std::cout << "Failed to load puzzle from file. Check filename and format.\n\n";
    }
}

void SudokuGame::savePuzzleToFile()
{
    std::string filename;
    std::cout << "Enter filename to save puzzle to: ";
    std::cin >> filename;

    if (board.saveToFile(filename))
    {
        std::cout << "Puzzle saved to " << filename << "!\n\n";
    }
    else
    {
        std::cout << "Failed to save puzzle to file.\n\n";
    }
}

void SudokuGame::quit()
{
    gameRunning = false;
    std::cout << "Thank you for playing Sudoku!\n";
}

bool SudokuGame::getIntegerInput(int &value, const std::string &prompt)
{
    if (!prompt.empty())
    {
        std::cout << prompt;
    }

    if (std::cin >> value)
    {
        return true;
    }

    // Clear error flags and input buffer
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    return false;
}

bool SudokuGame::isValidRange(int value, int min, int max)
{
    return value >= min && value <= max;
}

void SudokuGame::initializeDefaultPuzzle()
{
    // Initialize with a sample Sudoku puzzle
    std::vector<std::vector<int>> defaultPuzzle = {
        {5, 3, 0, 0, 7, 0, 0, 0, 0},
        {6, 0, 0, 1, 9, 5, 0, 0, 0},
        {0, 9, 8, 0, 0, 0, 0, 6, 0},
        {8, 0, 0, 0, 6, 0, 0, 0, 3},
        {4, 0, 0, 8, 0, 3, 0, 0, 1},
        {7, 0, 0, 0, 2, 0, 0, 0, 6},
        {0, 6, 0, 0, 0, 0, 2, 8, 0},
        {0, 0, 0, 4, 1, 9, 0, 0, 5},
        {0, 0, 0, 0, 8, 0, 0, 7, 9}};

    board.initializeBoard(defaultPuzzle);
}

#ifdef BUILD_GENERATOR
void SudokuGame::generateNewPuzzle()
{
    std::cout << "Select difficulty:\n";
    std::cout << "1) Easy\n";
    std::cout << "2) Medium\n";
    std::cout << "3) Hard\n";
    std::cout << "Choice: ";

    int difficultyChoice;
    if (!getIntegerInput(difficultyChoice, "") || difficultyChoice < 1 || difficultyChoice > 3)
    {
        std::cout << "Invalid choice. Generating medium difficulty puzzle.\n";
        difficultyChoice = 2;
    }

    Difficulty difficulty;
    switch (difficultyChoice)
    {
    case 1:
        difficulty = Difficulty::EASY;
        break;
    case 2:
        difficulty = Difficulty::MEDIUM;
        break;
    case 3:
        difficulty = Difficulty::HARD;
        break;
    default:
        difficulty = Difficulty::MEDIUM;
        break;
    }

    std::cout << "Generating new puzzle...\n";
    board = SudokuGenerator::generatePuzzle(difficulty);
    std::cout << "New puzzle generated!\n\n";
}
#endif

#ifdef BUILD_ADVANCED
void SudokuGame::solveWithAdvancedTechniques()
{
    std::cout << "Solving with advanced techniques...\n";

    if (SudokuAdvancedChecks::solveWithAdvancedTechniques(board))
    {
        std::cout << "Puzzle solved using advanced techniques!\n\n";
    }
    else
    {
        std::cout << "Advanced techniques couldn't solve the puzzle completely.\n";
        std::cout << "You may need to use backtracking or make manual moves.\n\n";
    }
}
#endif