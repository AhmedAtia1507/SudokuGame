#include "../include/SudokuSolver.hpp"

bool SudokuSolver::checkValidMove(const std::vector<std::vector<char>>& board, int currentRow, int currentColumn, char numToBeEntered) {
    for(int index = 0; index < board.size(); index++) {
        if((board[currentRow][index]) == numToBeEntered) {
            return false;
        }
        if((board[index][currentColumn]) == numToBeEntered) {
            return false;
        }
    }
    int boxStartRow = (currentRow / 3) * 3;
    int boxStartCol = (currentColumn / 3) * 3;
    for(int index = boxStartRow; index < boxStartRow + 3; index++) {
        for(int index_1 = boxStartCol; index_1 < boxStartCol + 3; index_1++) {
            if((board[index][index_1]) == numToBeEntered) {
                return false;
            }
        }
    }
    return true;
}
bool SudokuSolver::backtrack(std::vector<std::vector<char>>& board, int currentRow, int currentColumn) {
    if(currentRow == board.size()) {
        return true;
    }
    else if(currentColumn == board[0].size()) {
        return backtrack(board, (currentRow + 1), 0);
    }
    else if(board[currentRow][currentColumn] != '.') {
        return backtrack(board, currentRow, (currentColumn + 1));
    }
    else {
        for(char index = '1'; index <= '9'; index++) {
            if(checkValidMove(board, currentRow, currentColumn, index)) {
                board[currentRow][currentColumn] = index;
                if(backtrack(board, currentRow, (currentColumn + 1))) {
                    return true;
                }
                else {
                    board[currentRow][currentColumn] = '.';
                }
            }
        }
        return false;
    }
}
bool SudokuSolver::solveBoard(std::vector<std::vector<char>>& board) {
    return backtrack(board, 0, 0);
}

bool SudokuSolver::isBoardSolvable(std::vector<std::vector<char>> board) {
    return solveBoard(board);
}