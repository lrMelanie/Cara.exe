#pragma once
#ifndef MINIGAME_H
#define MINIGAME_H
#include "VirtualAssistant.h"
#include <random>
#include <string>
#include <vector>

using namespace std;

void showCodeRunnerOptions();

class Minigame : public VirtualAssistant {
public:
    class CodeRunner {
        int points;
        int highScore;
        int linesToType;
        vector<string> repositoryFiles;
        vector<string> currentLines;
        mt19937 gen;
        random_device rd;

        void loadHighScore();
        void saveHighScore();
        vector<string> loadRepositoryFile(const string& path);
        vector<string> getConsecutiveLines(const vector<string>& lines, int count);
        bool checkLine(const string& input, const string& target);
        void displayGameOver();

    public:
        CodeRunner();
        void setRepositories(const vector<string>& repos){repositoryFiles = repos;}
        void showMenu();
        void playGame();
        void run();
    };

public:
    Minigame();
    void run();
};
#endif