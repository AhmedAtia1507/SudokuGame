# Sudoku Game

A comprehensive Sudoku puzzle game implementation in C++ with both console and graphical user interfaces. This project demonstrates object-oriented programming principles, CMake build system usage, and cross-platform development with Qt.

## 📋 Table of Contents

- [Features](#features)
- [Project Structure](#project-structure)
- [Prerequisites](#prerequisites)
- [Installation](#installation)
- [Usage](#usage)
- [Game Features](#game-features)
- [Technical Details](#technical-details)
- [Build Options](#build-options)
- [Contributing](#contributing)

## ✨ Features

- **Dual Interface**: Both console-based and Qt GUI applications
- **Puzzle Generation**: Multiple difficulty levels (Easy, Medium, Hard, Expert)
- **Game Management**: Save, load, and delete game sessions
- **Auto-Solver**: Automatic puzzle solving with backtracking algorithm
- **Input Validation**: Real-time move validation and game state checking
- **Cross-Platform**: Compatible with Windows, Linux, and macOS

## 🏗️ Project Structure

```
Project_Implementation/
├── Console/                    # Console-based Sudoku game
│   ├── CMakeLists.txt         # Console app build configuration
│   ├── main.cpp               # Console application entry point
│   ├── include/
│   │   └── SudokuInterface.hpp # Console UI interface
│   ├── src/
│   │   └── SudokuInterface.cpp # Console UI implementation
│   └── gameData/              # Saved game files
│
├── QT_App/Sudoku/             # Qt GUI-based Sudoku game
│   ├── CMakeLists.txt         # Qt app build configuration
│   ├── main.cpp               # Qt application entry point
│   ├── SudokuWindow.h/cpp     # Main game window
│   ├── NewGameDialog.h/cpp    # New game creation dialog
│   ├── SaveGameDialog.h/cpp   # Save game dialog
│   ├── LoadGameDialog.h/cpp   # Load game dialog
│   └── build/                 # Qt build artifacts
│
└── SudokuGame/                # Core game library
    ├── include/               # Header files
    │   ├── SudokuBoard.hpp    # Game board management
    │   ├── SudokuGenerator.hpp # Puzzle generation
    │   ├── SudokuSolver.hpp   # Solving algorithms
    │   └── FileManager.hpp    # File I/O operations
    └── src/                   # Implementation files
        ├── SudokuBoard.cpp
        ├── SudokuGenerator.cpp
        ├── SudokuSolver.cpp
        └── FileManager.cpp
```

## 🔧 Prerequisites

### For Console Application:
- **CMake** 3.8 or higher
- **C++17** compatible compiler (GCC, Clang, MSVC)

### For Qt GUI Application:
- **CMake** 3.16 or higher
- **Qt6** or **Qt5** with Widgets module
- **C++17** compatible compiler

### Platform-Specific Requirements:

#### Windows:
- Visual Studio 2019+ or MinGW-w64
- Qt6 (recommended) or Qt5

#### Linux:
```bash
# Ubuntu/Debian
sudo apt update
sudo apt install build-essential cmake qt6-base-dev

# Fedora/CentOS
sudo dnf install gcc-c++ cmake qt6-qtbase-devel
```

#### macOS:
```bash
# Using Homebrew
brew install cmake qt6
```

## 🚀 Installation

### 1. Clone the Repository
```bash
git clone <repository-url>
cd SudokuGame
```

### 2. Build Console Application
```bash
cd Project_Implementation/Console
mkdir build
cd build
cmake ..
cmake --build .
```

### 3. Build Qt GUI Application
```bash
cd Project_Implementation/QT_App/Sudoku
mkdir build
cd build
cmake ..
cmake --build .
```

## 🎮 Usage

### Console Application
```bash
# From Project_Implementation/Console/build/
./SudokuProject          # Linux/macOS
SudokuProject.exe        # Windows
```

### Qt GUI Application
```bash
# From Project_Implementation/QT_App/Sudoku/build/
./Sudoku                 # Linux/macOS
Sudoku.exe              # Windows
```

## 🎯 Game Features

### Core Gameplay
- **9x9 Sudoku Grid**: Standard Sudoku board with 3x3 sub-grids
- **Multiple Difficulty Levels**:
  - Easy: More pre-filled numbers
  - Medium: Moderate challenge
  - Hard: Fewer clues
  - Expert: Maximum difficulty

### Game Operations
- **New Game**: Generate puzzles with selected difficulty
- **Move Entry**: Enter numbers with automatic validation
- **Save/Load**: Persist game state to files
- **Auto-Solve**: Let the algorithm solve the puzzle
- **Game Management**: Delete saved games

### Input Validation
- Real-time move validation
- Sudoku rule enforcement (row, column, 3x3 box uniqueness)
- Fixed cell protection (pre-filled numbers cannot be changed)

## 🔬 Technical Details

### Core Classes

#### `SudokuBoard`
- Manages the 9x9 game grid
- Handles move validation and game state
- Integrates with file operations and solving algorithms

#### `SudokuGenerator`
- Creates new puzzles with specified difficulty
- Uses solving algorithms to ensure puzzle validity
- Implements difficulty by controlling the number of given clues

#### `SudokuSolver`
- Backtracking algorithm for puzzle solving
- Move validation functions
- Solvability checking

#### `FileManager`
- Save/load game states to/from files
- List available saved games
- Delete saved game files

### Algorithms
- **Backtracking**: Recursive solving algorithm
- **Constraint Propagation**: Real-time move validation
- **Puzzle Generation**: Random filled grid with strategic removal

## ⚙️ Build Options

### Console Application Build Options
```bash
# Default build (includes all features)
cmake ..

# Build without puzzle generator
cmake .. -DBUILD_GENERATOR=OFF

# Build without advanced features
cmake .. -DBUILD_ADVANCED=OFF
```

### Qt Application Configuration
The Qt application automatically detects Qt5 or Qt6 and configures accordingly:
- Supports both Qt5 and Qt6
- Auto-generates MOC files for Qt objects
- Includes all necessary Qt Widgets components

## 🤝 Contributing

1. Fork the repository
2. Create a feature branch (`git checkout -b feature/amazing-feature`)
3. Commit your changes (`git commit -m 'Add amazing feature'`)
4. Push to the branch (`git push origin feature/amazing-feature`)
5. Open a Pull Request

### Development Guidelines
- Follow C++17 standards
- Maintain consistent code formatting
- Add comments for complex algorithms
- Test both console and GUI applications
- Ensure cross-platform compatibility

## 📝 License

This project is part of a Software Development Diploma program and is intended for educational purposes.

## 🐛 Known Issues

- Qt application may require specific Qt version configuration on some systems
- Save files are stored in relative paths (gameData folder)

---

**Note**: This project demonstrates C++ OOP principles, CMake build systems, Qt GUI development, and software architecture design patterns.