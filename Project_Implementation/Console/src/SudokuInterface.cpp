#include "../include/SudokuInterface.hpp"
#include <iostream>
#include <stdexcept>

SudokuInterface::SudokuInterface() : board(new SudokuBoard()) {

}
SudokuInterface::SudokuInterface(std::initializer_list<std::initializer_list<char>>& board) : board(new SudokuBoard(board)) {
}

void SudokuInterface::printGreetingMessage() const {
    system("cls");

    std::cout << "==========================================" << std::endl;
    std::cout << "           WELCOME TO SUDOKU!             " << std::endl;
    std::cout << "==========================================" << std::endl;
    
    std::cout << "Sudoku. Because who needs a social life when you have numbers?" << std::endl;
    std::cout << "My name is Ahmed Atia Said, and I will be your host today." << std::endl;
    std::cout << "Let's get started!" << std::endl;
}

void SudokuInterface::printBoard() const {
    std::vector<std::vector<char>> currentBoard = board -> getBoard();
    std::cout << "===================" << std::endl;
    for(int rowIndex = 0; rowIndex < currentBoard.size(); rowIndex++) {
        std::cout << "|";
        for(int columnIndex = 0; columnIndex < currentBoard[rowIndex].size(); columnIndex++) {
            std::cout << currentBoard[rowIndex][columnIndex];
            if((columnIndex + 1) % 3 == 0) {
                std::cout << "|";
            }
            else {
                std::cout << " ";
            }
        }
        std::cout << std::endl;
        if((rowIndex + 1) % 3 == 0) {
            std::cout << "===================" << std::endl;
        }
    }
}

void SudokuInterface::printInstructions() const {
    std::cout << "Please choose from the following options: " << std::endl;
    std::cout << "1. Enter a move" << std::endl;
    std::cout << "2. Solve automatically" << std::endl;
    std::cout << "3. Load puzzle from file" << std::endl;
    std::cout << "4. Save puzzle to file" << std::endl;
    std::cout << "5. Create a new game" << std::endl;
    std::cout << "6. Delete a saved game" << std::endl;
    std::cout << "7. Quit" << std::endl;
    std::cout << "Enter your choice: ";
}

void SudokuInterface::printGoodbyeMessage() const {
    std::cout << "==========================================" << std::endl;
    std::cout << "         THANK YOU FOR PLAYING!!          " << std::endl;
    std::cout << "==========================================" << std::endl;
}

void SudokuInterface::enterMove() {
    std::cin.clear();
    std::cout << "Please enter the row [1-9], column [1-9], and value [1-9] separated by spaces: ";
    int row, column;
    int valueToBeSet;
    
    std::cin >> row >> column >> valueToBeSet;
    system("cls");
    if(board -> setMove(row - 1, column - 1, valueToBeSet)) {
        std::cout << "Move entered successfully." << std::endl;
    }
    else {
        std::cout << "Invalid move. Maybe due to trying to edit a fixed cell or placement is against sudoku rules. Please try again." << std::endl;
    }
}

void SudokuInterface::solveAutomatically() {
    std::cout << "==========================================" << std::endl;
    if(board -> autoSolve()) {
        std::cout << "Puzzle solved successfully." << std::endl;
        std::cout << "Solved Puzzle is: " << std::endl;
        printBoard();
    }
    else {
        std::cout << "Puzzle is not solvable." << std::endl;
    }
}

bool SudokuInterface::loadPuzzleFromFile() {
    std::cin.clear();
    int choice;
    std::string fileName;
    std::vector<std::string> savedGames = FileManager::getSavedGames();
    if(savedGames.size() == 0) {
        system("cls");
        std::cout << "No saved games found." << std::endl;
        return false;
    }
    std::cout << "Please select the name of the file containing the puzzle to load:" << std::endl;
    for(int i = 0; i < savedGames.size(); i++) {
        std::cout << i + 1 << ". " << savedGames[i] << std::endl;
    }
    std::cout << "Enter your choice: ";
    std::cin >> choice;
    while(choice < 1 || choice > savedGames.size()) {
        std::cout << "Invalid choice. Please try again." << std::endl;
        std::cin >> choice;
    }
    system("cls");
    try {
        board->loadBoard(savedGames[(choice - 1)]);
        std::cout << "Puzzle loaded successfully." << std::endl;
    }
    catch(const std::runtime_error& e) {
        std::cout << e.what() << std::endl;
    }
    catch(const std::invalid_argument& e) {
        std::cout << e.what() << std::endl;
    }
    return true;
}

void SudokuInterface::savePuzzleToFile() {
    std::cin.clear();
    std::string fileName;
    std::cout << "Please enter the name of the file to save the puzzle to: ";
    std::cin >> fileName;
    system("cls");
    try {
        board -> saveBoard(fileName);
        std::cout << "Puzzle saved successfully." << std::endl;
    }
    catch(const std::runtime_error& e) {
        std::cout << e.what() << std::endl;
    }
    catch(const std::invalid_argument& e) {
        std::cout << e.what() << std::endl;
    }
}

void SudokuInterface::deleteSavedGame() {
    int choice;
    std::string fileName;
    std::vector<std::string> savedGames = FileManager::getSavedGames();
    if(savedGames.size() == 0) {
        system("cls");
        std::cout << "No saved games found." << std::endl;
        return;
    }
    
    std::cout << "Please select the name of the file containing the puzzle to delete:" << std::endl;
    for(int i = 0; i < savedGames.size(); i++) {
        std::cout << i + 1 << ". " << savedGames[i] << std::endl;
    }
    std::cout << "Enter your choice: ";
    std::cin.clear();
    std::cin >> choice;
    while(choice < 1 || choice > savedGames.size()) {
        std::cout << "Invalid choice. Please try again." << std::endl;
        std::cin >> choice;
    }
    
    system("cls");
    
    if(board -> deleteBoard(savedGames[(choice - 1)])) {
        std::cout << "Puzzle deleted successfully." << std::endl;
    }
    else {
        std::cout << "Puzzle could not be deleted." << std::endl;
    }
}

void SudokuInterface::createNewGame() {
    std::cout << "==========================================" << std::endl;
    std::cout << "Please select the game difficulty: " << std::endl;
    std::cout << "1. Easy" << std::endl;
    std::cout << "2. Medium" << std::endl;
    std::cout << "3. Hard" << std::endl;
    std::cout << "4. Expert" << std::endl;
    std::cout << "Enter your choice: ";
    int choice;
    std::cin.clear();
    std::cin >> choice;
    while(choice < 1 || choice > 4) {
        std::cout << "Invalid choice. Please try again." << std::endl;
        std::cin >> choice;
    }

    system("cls");
    std::cout << "Generating a new game..." << std::endl;
    switch(choice) {
        case 1: {
            board -> generateNewBoard(SudokuGenerator::Difficulty::EASY);
            break;
        }
        case 2: {
            board -> generateNewBoard(SudokuGenerator::Difficulty::MEDIUM);
            break;
        }
        case 3: {
            board -> generateNewBoard(SudokuGenerator::Difficulty::HARD);
            break;
        }
        case 4: {
            board -> generateNewBoard(SudokuGenerator::Difficulty::EXPERT);
            break;
        }
        default: {
            std::cout << "Invalid choice. Please try again." << std::endl;
            break;
        }
    }
}
void SudokuInterface::selectGameMode() {
    std::cout << "===========================================" << std::endl;
    std::cout << "Please select the game mode: " << std::endl;
    std::cout << "1. Play a new game" << std::endl;
    std::cout << "2. Load a saved game" << std::endl;
    std::cout << "Enter your choice: ";
    char choice;
    std::cin >> choice;
    while(choice != '1' && choice != '2') {
        std::cout << "Invalid choice. Please try again." << std::endl;
        std::cin >> choice;
    }
    switch(choice) {
        case '1': {
            createNewGame();
            break;
        }
        case '2': {
            if(!loadPuzzleFromFile()) {
                std::cout << "Creating a new game instead..." << std::endl;
                createNewGame();
            }
            break;
        }
        default: {
            std::cout << "Invalid choice. Please try again." << std::endl;
            break;
        }
    }
}
/**
 * @brief Starts the main game loop for the Sudoku game.
 * 
 * This function handles the core gameplay mechanics, including:
 * - Displaying a greeting message and game instructions.
 * - Allowing the user to select a game mode.
 * - Continuously processing user input to perform various actions such as:
 *   - Entering a move.
 *   - Solving the puzzle automatically.
 *   - Loading a puzzle from a file.
 *   - Saving the current puzzle to a file.
 *   - Creating a new game.
 *   - Deleting a saved game.
 *   - Exiting the game.
 * - Checking if the Sudoku board is solved and congratulating the user if so.
 * - Displaying the game board and instructions after each action.
 * 
 * The game loop continues until the user chooses to exit or the board is solved.
 */
void SudokuInterface::playGame() {
    printGreetingMessage();
    selectGameMode();
    printBoard();
    printInstructions();

    char choice;

    while(true) {
        std::cin.clear();
        std::cin >> choice;
        switch(choice) {
            case '1': {     // Enter a move
                enterMove();
                break;
            }
            case '2': {     // Automatically solve the puzzle
                solveAutomatically();
                break;
            }
            case '3': {     // Load a puzzle from a file
                loadPuzzleFromFile();
                break;
            }
            case '4': {     // Save the current puzzle to a file
                savePuzzleToFile();
                break;
            }
            case '5': {     // Create a new game
                createNewGame();
                break;
            }
            case '6': {     // Delete a saved game
                deleteSavedGame();
                break;
            }
            case '7': {     // Quit the game
                printGoodbyeMessage();
                break;
            }
            default: {      // Invalid choice
                std::cout << "Invalid choice. Please try again." << std::endl;
                break;
            }
        }
        if((choice == '7')) {
            break;
        }
        if(board -> isSolved()) {
            if(choice != '2') {
                // Means that the user has solved the puzzle manually
                std::cout << "Congratulations! You've conquered the Sudoku challenge!" << std::endl;
                std::cout << "Your Sudoku skills are truly impressive!" << std::endl;
                printBoard();
            }
            printGoodbyeMessage();
            break;
        }
        printBoard();
        printInstructions();
    }
}

SudokuInterface::~SudokuInterface() {
    delete board;
}