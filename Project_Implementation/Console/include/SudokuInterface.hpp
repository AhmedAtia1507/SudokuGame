#pragma once

#include "../../SudokuGame/include/SudokuBoard.hpp"
#include "../../SudokuGame/include/FileManager.hpp"

class SudokuInterface {
    SudokuBoard* board;
    
    void printGreetingMessage() const;
    void printGoodbyeMessage() const;
    void printBoard() const;
    void printInstructions() const;

    void createNewGame();
    void selectGameMode();
    void enterMove();
    void solveAutomatically();
    bool loadPuzzleFromFile();
    void savePuzzleToFile();
    void deleteSavedGame();
    public:
        SudokuInterface();
        SudokuInterface(std::initializer_list<std::initializer_list<char>>& board);

        void playGame();

        ~SudokuInterface();
};