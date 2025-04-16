#pragma once
#include "VirtualAssistant.h"
#include <windows.h>
#include <shellapi.h>
#include <string>
#include <vector>

class Minigame : public VirtualAssistant {
    int points;
    int highScore;
    int linesToType;
    std::vector<std::string> repositoryFiles;
    std::vector<std::string> currentLines;

    void loadHighScore();
    void saveHighScore();
    std::vector<std::string> loadRepositoryFile(const std::string& path);
    std::vector<std::string> getConsecutiveLines(const std::vector<std::string>& lines, int count);
    bool checkLine(const std::string& input, const std::string& target);
    void displayGameOver();

public:
    Minigame();
    void run();
};