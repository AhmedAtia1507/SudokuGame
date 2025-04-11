#pragma once

#include <vector>
#include <string>
#include "../include/SudokuGenerator.hpp"

class SudokuBoard {
    std::vector<std::vector<char>> board;
    std::vector<std::vector<bool>> fixedCells;

    void setFixedCells();
    public:
        SudokuBoard();
        SudokuBoard(std::initializer_list<std::initializer_list<char>>& board);
        
        inline std::vector<std::vector<char>> getBoard() const {
            return board;
        }

        bool setMove(int row, int col, int valueToBeSet);
        void loadBoard(std::string filename);
        void saveBoard(std::string filename) const;
        bool deleteBoard(std::string filename) const;
        bool autoSolve();
        void generateNewBoard(SudokuGenerator::Difficulty difficulty);
        bool isSolved() const;
};