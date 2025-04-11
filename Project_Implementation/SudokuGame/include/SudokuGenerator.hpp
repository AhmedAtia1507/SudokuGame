#pragma once

#include <vector>
#include "SudokuSolver.hpp"

class SudokuGenerator {
    public:
        enum class Difficulty {
            EASY,
            MEDIUM,
            HARD,
            EXPERT
        };
        static std::vector<std::vector<char>> generateGame(Difficulty difficulty);
};