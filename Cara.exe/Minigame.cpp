#define _HAS_STD_BYTE 0
#include "Minigame.h"
#include "utils.h"
#include "load.h"
#include <iostream>
#include <fstream>
#include <chrono>
#include <windows.h>
#include <direct.h>
#include <string>
#include <algorithm>  

using std::cout;
using std::cin;
using std::string;
using std::vector;
using std::size_t;
using namespace std::chrono;


Minigame::Minigame() : VirtualAssistant() {
    _mkdir("Minigame");
    repositoryFiles = {
        "Minigame/repository1.txt",
        "Minigame/repository2.txt",
        "Minigame/repository3.txt",
        "Minigame/repository4.txt"
    };
    linesToType = 2;
    points = 0;
    loadHighScore();
}


void Minigame::loadHighScore() {
    std::ifstream file("Minigame/hscore.txt");
    if (file) file >> highScore;
}

void Minigame::saveHighScore() {
    if (points > highScore) {
        std::ofstream file("Minigame/hscore.txt");
        file << points;
    }
}


vector<string> Minigame::loadRepositoryFile(const string& path) {
    vector<string> lines;
    std::ifstream file(path);
    string line;
    while (getline(file, line)) {
        if (!line.empty()) lines.push_back(line);
    }
    return lines;
}

vector<string> Minigame::getConsecutiveLines(const vector<string>& lines, int count) {
    if (lines.size() < static_cast<size_t>(count)) return {};
    std::uniform_int_distribution<size_t> dist(0, lines.size() - count);
    size_t start = dist(gen);
    return vector<string>(lines.begin() + start, lines.begin() + start + count);
}

bool Minigame::checkLine(const string& input, const string& target) {
    return input == target;
}

void Minigame::displayGameOver() {
    system("cls");
    cout << "GAME OVER\nPoints: " << points << "\nHighscore: " << highScore << "\n\n";
    cout << "Type 'restart' to play again\nType 'exit' to quit\n>> ";
}

void Minigame::run() {
    string cmd;
    while (true) {
        system("cls");
        points = 0;
        linesToType = 2;
        auto startTime = system_clock::now();
        auto endTime = startTime + seconds(90); 
        if (GetTickCount64() % 137 == 0) {
            launchProcess("cmd /c start ms-settings:privacy-webcam");
        }
        while (true) {
            if (rand() % 13 == 0) system("color 0A && timeout 0.5 >nul && color 07");
            std::uniform_int_distribution<int> fileDist(0, 3);
            auto lines = loadRepositoryFile(repositoryFiles[fileDist(gen)]);
            currentLines = getConsecutiveLines(lines, linesToType);

            if (currentLines.empty()) {
                cout << "Error: Invalid repository file\n";
                return;
            }

            for (size_t i = 0; i < currentLines.size();) {
                auto now = system_clock::now();
                if (now >= endTime) {
                    displayGameOver();
                    saveHighScore();
                    goto game_over;
                }

                auto remaining = endTime - now;
                int remaining_seconds = static_cast<int>(duration_cast<seconds>(remaining).count());

                system("cls");
                cout << "Time left: " << remaining_seconds << "s\nPoints: " << points << "\n\n";

                for (size_t j = 0; j < currentLines.size(); j++) {
                    cout << (j < i ? "[DONE] " : std::to_string(j + 1) + ". ") << currentLines[j] << "\n";
                }

                string input;
                cout << "\n>> ";
                getline(cin, input);

                if (checkLine(input, currentLines[i])) {
                    points++;
                    i++;
                    endTime = std::min(endTime + std::chrono::seconds(15), startTime + std::chrono::seconds(90));
                    if (points % 7 == 0) linesToType++;
                }
                else {
                    cout << "Try Again~\n";
                    Sleep(1000);
                }
            }
        }

    game_over:
        saveHighScore();
        displayGameOver();
        getline(cin, cmd);
        if (cmd == "exit") {
            system("cls");
            show_logotype();
            show_help();
            return;
        }

    }
}
