#include "../include/SudokuBoard.hpp"
#include "../include/FileManager.hpp"
#include "../include/SudokuSolver.hpp"
#include "../include/SudokuGenerator.hpp"
#include <stdexcept>

SudokuBoard::SudokuBoard() {
    board = std::vector<std::vector<char>>(9, std::vector<char>(9, '.'));
    fixedCells = std::vector<std::vector<bool>>(9, std::vector<bool>(9, false));
    board.shrink_to_fit();
    fixedCells.shrink_to_fit();
}
SudokuBoard::SudokuBoard(std::initializer_list<std::initializer_list<char>>& board) {
    if(board.size() != 9) {
        throw std::invalid_argument("Board must have 9 rows");
    }
    for(auto& boardRow : board) {
        if(boardRow.size() != 9) {
            throw std::invalid_argument("Each row must have 9 columns");
        }
        std::vector<char> row = boardRow;
        (this -> board).push_back(row);
    }
    (this -> board).shrink_to_fit();
    for(auto& row : (this -> board)) {
        row.shrink_to_fit();
    }
    fixedCells = std::vector<std::vector<bool>>(9, std::vector<bool>(9, false));
    setFixedCells();
}

void SudokuBoard::setFixedCells() {
    for(int row = 0; row < board.size(); row++) {
        for(int column = 0; column < board[0].size(); column++) {
            if(board[row][column] != '.') {
                fixedCells[row][column] = true;
            } 
            else {
                fixedCells[row][column] = false;
            }
        }
    }
}
bool SudokuBoard::setMove(int row, int column, int valueToBeSet) {
    if (
        (row < 0) || (row > 8) || 
        (column < 0) || (column > 8) || 
        (valueToBeSet < 1) || (valueToBeSet > 9)
    ) {
        return false;
    }
    if(fixedCells[row][column]) {
        return false;
    }
    if(!SudokuSolver::checkValidMove(board, row, column, (valueToBeSet + '0'))) {
        return false;
    }
    board[row][column] = (valueToBeSet + '0');
    return true;
}

void SudokuBoard::loadBoard(std::string fileName) {
    std::vector<std::vector<char>> newBoard = FileManager::loadBoard(fileName);
    board = newBoard;
}

void SudokuBoard::saveBoard(std::string filename) const {
    FileManager::saveBoard(board, filename);
}

bool SudokuBoard::autoSolve() {
    return SudokuSolver::solveBoard(board);
}

bool SudokuBoard::isSolved() const {
    for(auto& row : board) {
        for(auto& num : row) {
            if(num == '.') {
                return false;
            }
        }
    }
    return true;
}

void SudokuBoard::generateNewBoard(SudokuGenerator::Difficulty difficulty) {
    board = SudokuGenerator::generateGame(difficulty);
}

bool SudokuBoard::deleteBoard(std::string fileName) const {
    return FileManager::deleteSavedGame(fileName);
}