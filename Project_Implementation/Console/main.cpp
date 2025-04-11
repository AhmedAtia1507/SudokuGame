#include "include/SudokuInterface.hpp"
#include <stdexcept>
#include <iostream>

int main() {
    try {
        SudokuInterface sudokuInterface;
        sudokuInterface.playGame();
    }
    catch(const std::runtime_error& e) {
        std::cout << e.what() << std::endl;
    }
    catch(const std::invalid_argument& e) {
        std::cout << e.what() << std::endl;
    }
    return 0;
}