#ifndef SUDOKU_GAME_HPP
#define SUDOKU_GAME_HPP

#include "SudokuBoard.hpp"
#include <string>

class SudokuGame
{
private:
    SudokuBoard board;
    bool gameRunning;

    // Display the main menu
    void displayMenu();

    // Get menu choice from user
    int getMenuChoice();

    // Handle user entering a move
    void enterMove();

    // Automatically solve the puzzle
    void solveAutomatically();

    // Load puzzle from file
    void loadPuzzleFromFile();

    // Save puzzle to file
    void savePuzzleToFile();

    // Quit the game
    void quit();

    // Helper function to get integer input
    bool getIntegerInput(int &value, const std::string &prompt);

    // Helper function to validate range
    bool isValidRange(int value, int min, int max);

    // Initialize a default puzzle
    void initializeDefaultPuzzle();

public:
    // Constructor
    SudokuGame();

    // Main game loop
    void run();
};

#endif // SUDOKU_GAME_HPP