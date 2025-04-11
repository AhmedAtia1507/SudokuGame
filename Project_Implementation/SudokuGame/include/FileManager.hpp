#pragma once

#include <vector>
#include <string>

class FileManager {
    public:
        static std::vector<std::vector<char>> loadBoard(const std::string fileName);
        static void saveBoard(const std::vector<std::vector<char>>& board, const std::string fileName);
        static std::vector<std::string> getSavedGames();
        static bool deleteSavedGame(const std::string fileName);
};