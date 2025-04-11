#include "../include/SudokuGenerator.hpp"
#include <random>
#include <algorithm>

std::vector<std::vector<char>> SudokuGenerator::generateGame(SudokuGenerator::Difficulty difficulty) {
    std::vector<std::vector<char>> board(9, std::vector<char>(9, '.'));
    std::vector<int> numbers = {1, 2, 3, 4, 5, 6, 7, 8, 9};
    
    // Shuffling the numbers to fill the first row of the board
    std::random_device randDevice;
    std::mt19937 generator(randDevice());
    std::shuffle(numbers.begin(), numbers.end(), generator);
    
    for(int index = 0; index < 9; index++) {
        board[0][index] = (numbers[index] + '0');
    }

    // Solving the board
    SudokuSolver::solveBoard(board);

    // In order to generate the game, we need to remove some cells from the board
    int numberOfCellsToBeRemoved = 0;
    switch(difficulty) {
        case Difficulty::EASY: {
            numberOfCellsToBeRemoved = 30;
            break;
        }
        case Difficulty::MEDIUM: {
            numberOfCellsToBeRemoved = 40;
            break;
        }
        case Difficulty::HARD: {
            numberOfCellsToBeRemoved = 50;
            break;
        }
        case Difficulty::EXPERT: {
            numberOfCellsToBeRemoved = 60;
            break;
        }
        default: {
            numberOfCellsToBeRemoved = 30;
            break;
        }
    }
    // We generate a vector of 81 elements, each element represents a cell in the board
    // We shuffle the vector and remove the first n elements from the board
    std::vector<int> cellsToBeRemoved;
    for(int index = 0; index < 81; index++) {
        cellsToBeRemoved.push_back(index);
    }
    std::shuffle(cellsToBeRemoved.begin(), cellsToBeRemoved.end(), generator);
    for(int index = 0; index < numberOfCellsToBeRemoved; index++) {
        int row = cellsToBeRemoved[index] / 9;
        int column = cellsToBeRemoved[index] % 9;
        board[row][column] = '.';
    }
    return board;
}