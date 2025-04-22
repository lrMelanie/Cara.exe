#pragma once
#include "VirtualAssistant.h"
#include <windows.h>
#include <shellapi.h>
#include <string>
#include <vector>

using namespace std;

class Minigame : public VirtualAssistant {
    int points;
    int highScore;
    int linesToType;
    vector<string> repositoryFiles;
    vector<string> currentLines;

    void loadHighScore();
    void saveHighScore();
    vector<string> loadRepositoryFile(const string& path);
    vector<string> getConsecutiveLines(const vector<string>& lines, int count);
    bool checkLine(const string& input, const string& target);
    void displayGameOver();

public:
    Minigame();
    void run();
};