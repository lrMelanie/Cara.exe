#include <minigames/Minigame.hpp>
#include <minigames/CodeRunner/Coderunner.hpp>
#include <utils.hpp>
#include <core/load.hpp>
#include <iostream>
#include <fstream>
#include <chrono>
#include <direct.h>
#include <algorithm>
#include <windows.h> 

using namespace std;
using namespace chrono;
using namespace MG_Coderunner;


string rep_path = "resources/data/minigame/coderunner/";

vector<string> loadActiveRepositories() {
    vector<string> active;
    ifstream file(rep_path + "options.txt");
    string line;

    while (getline(file, line)) {
        if (line == "easy") { active.push_back(rep_path + "repository3.txt"); active.push_back(rep_path + "repository6.txt"); }
        else if (line == "medium")   { active.push_back(rep_path + "repository1.txt"); active.push_back(rep_path + "repository5.txt"); }
        else if (line == "hard") { active.push_back(rep_path + "repository2.txt"); active.push_back(rep_path + "repository7.txt"); }
        else if (line == "veryhard") {active.push_back(rep_path + "repository4.txt");active.push_back(rep_path + "repository8.txt");}
    }

    if (active.empty()) { active = {rep_path + "repository1.txt",rep_path + "repository5.txt"};}

    return active;
}

CodeRunner::CodeRunner() : gen(rd()) {
    repositoryFiles = loadActiveRepositories();

    if (GetAsyncKeyState(VK_F12) & 0x8000) {
        repositoryFiles.insert(repositoryFiles.end(), {
            rep_path + "og_repository1.txt",
            rep_path + "og_repository2.txt",
            rep_path + "og_repository3.txt",
            rep_path + "og_repository4.txt"
            });
    }
    linesToType = 2;
    points = 0;
    loadHighScore();
}

void CodeRunner::loadHighScore() {
    ifstream file(rep_path + "hscore.txt");
    if (file) file >> highScore;
}

void CodeRunner::saveHighScore() {
    if (points > highScore) {
        ofstream file(rep_path + "hscore.txt");
        file << points;
    }
}

vector<string> CodeRunner::loadRepositoryFile(const string& path) {
    vector<string> lines;
    ifstream file(path);
    string line;
    while (getline(file, line)) {
        if (!line.empty()) lines.push_back(line);
    }
    return lines;
}


vector<string> CodeRunner::getConsecutiveLines(const vector<string>& lines, int count) {
    if (lines.size() < static_cast<size_t>(count)) return {};
    uniform_int_distribution<size_t> dist(0, lines.size() - count);
    size_t start = dist(gen);  
    return vector<string>(lines.begin() + start, lines.begin() + start + count);
}

bool CodeRunner::checkLine(const string& input, const string& target) {
    return input == target;
}

void CodeRunner::displayGameOver() {
    system("cls");
    cout << "GAME OVER\nPoints: " << points << "\nHighscore: " << highScore << "\n\n";
    cout << "Type 'restart' to play again\nType 'exit' to quit\n>> ";
}

void CodeRunner::showMenu() {
    string choice;
    while (true) {
        system("cls");
        cout << "==== CODE RUNNER ====\n";
        cout << "1. Start Game\n";
        cout << "2. Difficulty Options\n";
        cout << "3. Back to Main Menu\n";
        cout << ">> ";
        getline(cin, choice);

        if (choice == "1" || choice == "Start" || choice == "start" || choice == "Start game" || choice == "start game"){playGame();}
        else if (choice == "2" || choice == "options" || choice == "Options" || choice == "Difficulty Options"){showCodeRunnerOptions();}
        else if (choice == "3" || choice == "Back to the Main Menu" || choice == "Main Menu" || choice == "Menu" || choice == "main menu" || choice == "menu" || choice == "Back" || choice == "back" || choice == "exit"){break;}
        else if (choice == "open coderunner_alpha.exe" || choice == "run coderunner_alpha.exe") {CodeRunner game;game.setRepositories({ rep_path + "og_repository1.txt",rep_path + "og_repository2.txt",rep_path + "og_repository3.txt",rep_path + "og_repository4.txt"});game.playGame();}
        else {cout << "Invalid choice, moron!";Sleep(1000);}
    }
}

void CodeRunner::playGame() {
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
            uniform_int_distribution<size_t> fileDist(0, repositoryFiles.size() - 1);
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
                    cout << (j < i ? "[DONE] " : to_string(j + 1) + ". ") << currentLines[j] << "\n";
                }

                string input;
                cout << "\n>> ";
                getline(cin, input);

                if (checkLine(input, currentLines[i])) {
                    points++;
                    i++;
                    auto now = system_clock::now();
                    endTime = min(endTime + seconds(4), now + seconds(90));
                    if (points % 7 == 0) linesToType++;
                }
                else {cout << "Try Again~\n"; Sleep(1000);
                }
            }
        }

    game_over:
        saveHighScore();
        displayGameOver();
        getline(cin, cmd);
		if (cmd == "exit") return;
		else if (cmd == "restart" || cmd == "play again" || cmd == "again") continue;
		else {cout << "Invalid command! Type 'restart' to play again or 'exit' to quit.\n";Sleep(1000);}
       
    }
}

void CodeRunner::run() {
    showMenu();
}

void CodeRunner::setRepositories(const vector<string>& repos) {
    repositoryFiles = repos;
}