#pragma once
#ifndef CODERUNNER_HPP
#define CODERUNNER_HPP
#include <minigames/Minigame.hpp>
#include <string>
#include <vector>
#include <random>

using namespace std;

namespace Minigame {

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
        void setRepositories(const vector<string>& repos);
        void showMenu();
        void playGame();
        void run();
    };

}   
#endif 