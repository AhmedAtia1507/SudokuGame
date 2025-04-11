#pragma once

#include <vector>

class SudokuSolver {
    private:
        static bool backtrack(std::vector<std::vector<char>>& board, int currentRow, int currentColumn);
    public:
        static bool checkValidMove(const std::vector<std::vector<char>>& board, int currentRow, int currentColumn, char numToBeEntered);
        static bool solveBoard(std::vector<std::vector<char>>& board);
        static bool isBoardSolvable(std::vector<std::vector<char>> board);
};