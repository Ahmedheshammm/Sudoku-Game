## Quick Start

**Just want to play? Here's the fastest way:**

```bash
# Navigate to your project folder
#example:
cd "c:\Soduku Game Project\project test"

# Compile and run (one command)
g++ -std=c++17 -o SudokuProject.exe main.cpp SudokuBoard.cpp SudokuSolver.cpp SudokuGame.cpp SudokuGenerator.cpp SudokuAdvancedChecks.cpp -mconsole && .\SudokuProject.exe
```

That's it! The game will start immediately with a default puzzle.

**For a cleaner build process, see the detailed build instructions below.**

## Prerequisites

- **C++ Compiler**: GCC 7+, Clang 5+, or MSVC 2017+ with C++17 support
- **CMake**: Version 3.10 or higher (can be installed via `winget install Kitware.CMake` on Windows)
- **Build Tools**: MinGW-w64 (Windows), GCC (Linux/macOS), or Visual Studio (Windows)

## Building the Project

### Prerequisites Installation (Windows)

If you don't have CMake installed:

```bash
# Using Windows Package Manager
winget install Kitware.CMake

# Restart your terminal or VS Code after installation
```

### Method 1: CMake Build (Recommended)

```bash
# Navigate to project directory
cd "path/to/your/project"

# Create and configure build directory
mkdir build
cmake -G "MinGW Makefiles" -S . -B build

# Build the project
cmake --build build

# Run the executable
.\build\SudokuProject.exe
```

### Method 2: Direct Compilation

```bash
# Navigate to project directory
cd "path/to/your/project"

# Compile all source files
g++ -std=c++17 -o SudokuProject.exe main.cpp SudokuBoard.cpp SudokuSolver.cpp SudokuGame.cpp SudokuGenerator.cpp SudokuAdvancedChecks.cpp -mconsole

# Run the executable
.\SudokuProject.exe
```

### Method 3: VS Code Build Task

If you're using VS Code, create a `.vscode/tasks.json` file:

```json
{
  "version": "2.0.0",
  "tasks": [
    {
      "label": "Build Sudoku Project",
      "type": "shell",
      "command": "g++",
      "args": [
        "-std=c++17",
        "-Wall",
        "-Wextra",
        "-O2",
        "-o",
        "SudokuProject.exe",
        "main.cpp",
        "SudokuBoard.cpp",
        "SudokuSolver.cpp",
        "SudokuGame.cpp",
        "SudokuGenerator.cpp",
        "SudokuAdvancedChecks.cpp",
        "-mconsole"
      ],
      "group": "build",
      "problemMatcher": ["$gcc"]
    }
  ]
}
```

### Platform-Specific Notes

**Windows (MinGW):**

- Use `-mconsole` flag for console applications
- Use `MinGW Makefiles` generator with CMake
- Executable will be named `SudokuProject.exe`

**Linux/macOS:**

```bash
mkdir build
cmake -S . -B build
cmake --build build
./build/SudokuProject
```

## Troubleshooting

### Common Build Issues

1. **"cmake is not recognized"**:

   - Install CMake: `winget install Kitware.CMake`
   - Restart terminal/VS Code after installation
   - Or use direct compilation method instead

2. **"undefined reference to WinMain"**:

   - Use `-mconsole` flag with g++: `g++ -std=c++17 -mconsole ...`
   - Or use CMake with MinGW Makefiles generator

3. **"C++17 not supported"**:

   - Update compiler to GCC 7+, Clang 5+, or MSVC 2017+

4. **"fillDiagonalBox undefined" or similar errors**:

   - Ensure all header files have correct content
   - Check that include statements are present in source files
   - Verify SudokuGame.hpp contains SudokuGame class (not SudokuGenerator)

5. **CMake configuration warnings**:
   - Update CMake version requirement to 3.10+
   - Warnings about project() command are usually non-critical

### Windows-Specific Issues

1. **MinGW linking problems**:

   - Ensure you're using MSYS2/MinGW-w64
   - Use the `-mconsole` compiler flag
   - Use `MinGW Makefiles` generator with CMake

2. **Path issues with spaces**:

   - Use quotes around paths: `cd "C:\Path With Spaces\project"`
   - Or use PowerShell's tab completion

3. **PowerShell execution policy**:
   - If scripts don't run: `Set-ExecutionPolicy -ExecutionPolicy RemoteSigned -Scope CurrentUser`

### Runtime Issues

1. **File not found**: Ensure puzzle files are in the working directory where you run the executable
2. **Invalid input**: Use exactly the format shown (space-separated integers)
3. **Console window closes immediately**: Run from command line, not by double-clicking
4. **Crash on invalid input**: Input validation should prevent this - please report bugs
