#include <minigames/Minigame.hpp>
#include <minigames/CodeRunner/Coderunner.hpp>
#include <windows.h> 
#include <iostream>
#include <fstream>
#include <algorithm>

using namespace std;

string reppath = "resources/data/minigame/coderunner/";

void showCodeRunnerOptions() {
    vector<string> options;
    ifstream in(reppath + "options.txt");
    if (!in.is_open()) {
        ofstream createFile(reppath + "options.txt");
        createFile.close();
        in.open(reppath + "options.txt");
    }

    string line;
    while (getline(in, line)) {
        if (!line.empty()) options.push_back(line);
    }

    while (true) {
        system("cls");
        cout << "=== DIFFICULTY OPTIONS ===\n";
        cout << "1. Easy ["
            << (count(options.begin(), options.end(), "easy") ? "X" : " ")
            << "]\n";
       cout << "2. Medium [" 
            << (count(options.begin(), options.end(), "medium") ? "X" : " ")
            << "]\n";
        cout << "3. Hard ["
            << (count(options.begin(), options.end(), "hard") ? "X" : " ")
            << "]\n";
        cout << "4. Very Hard ["
            << (count(options.begin(), options.end(), "veryhard") ? "X" : " ")
            << "]\n";
        cout << "0. Back\n>> ";

        string choice;
        getline(cin, choice);

        if (choice == "0") break;

        string difficulty;
        if (choice == "1") difficulty = "easy";
        else if (choice == "2") difficulty = "medium";
        else if (choice == "3") difficulty = "hard";
        else if (choice == "4") difficulty = "veryhard";
        else continue;

        auto it = find(options.begin(), options.end(), difficulty);
        if (it != options.end()) options.erase(it);
        else options.push_back(difficulty);

        ofstream out(reppath + "options.txt");
        if (!out.is_open()) {
            MessageBoxA(NULL, "Failed to save options!", "Error", MB_ICONERROR);
            return;
        }
        for (auto& o : options) out << o << endl;
    }
}