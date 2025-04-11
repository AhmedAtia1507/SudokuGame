#include "../include/FileManager.hpp"
#include <iostream>
#include <fstream>
#include <filesystem>

constexpr const char* SAVED_GAME_PATH = "../gameData/";

std::vector<std::vector<char>> FileManager::loadBoard(const std::string fileName) {
    std::ifstream loadedFile(static_cast<std::string>(SAVED_GAME_PATH) + fileName);
    if(!loadedFile.is_open()) {
        throw std::runtime_error("File not found or inaccessible");
    }
    std::vector<std::vector<char>> board;
    std::string line;

    while(std::getline(loadedFile, line)) {
        std::vector<char> row;
        for(char& character : line) {
            if(character == ' ') {
                continue;
            }
            row.push_back(character);
        }
        if(row.size() != 9) {
            throw std::invalid_argument("Each row must have 9 columns");
        }
        board.push_back(row);
    }
    if(board.size() != 9) {
        throw std::invalid_argument("Board must have 9 rows");
    }

    board.shrink_to_fit();
    for(auto& row : board) {
        row.shrink_to_fit();
    }
    return board;
}
void FileManager::saveBoard(const std::vector<std::vector<char>>& board, const std::string fileName) {
    std::filesystem::create_directory(SAVED_GAME_PATH);
    std::ofstream savedFile(static_cast<std::string>(SAVED_GAME_PATH) + fileName);
    if(!savedFile.is_open()) {
        throw std::runtime_error("File not created or inaccessible");
    }
    for(const auto& row : board) {
        for(const auto& character : row) {
            savedFile << character << ' ';
        }
        savedFile << std::endl;
    }
}

std::vector<std::string> FileManager::getSavedGames() {
    std::vector<std::string> savedGames;
    if(!std::filesystem::exists(SAVED_GAME_PATH)) {
        return savedGames;
    }
    // Iterate over the directory and push the file names into the vector
    std::filesystem::directory_iterator dir(SAVED_GAME_PATH);
    for(const auto& file : dir) {
        savedGames.push_back(file.path().filename().string());
    }
    return savedGames;
}

bool FileManager::deleteSavedGame(const std::string fileName) {
    if(!std::filesystem::exists(SAVED_GAME_PATH + fileName)) {
        return false;
    }
    std::filesystem::remove(SAVED_GAME_PATH + fileName);
    return true;
}