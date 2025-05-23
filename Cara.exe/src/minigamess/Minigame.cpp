#include <minigames/Minigame.hpp>
#include <minigames/CodeRunner/Coderunner.hpp>
#include <utils.hpp>
#include <core/load.hpp>
#include <core/VirtualAssistant.hpp>
#include <iostream>

using namespace std;

Minigame::Minigame() : VirtualAssistant() {}

void Minigame::run(){
    string choice;
    while (true) {
        system("cls");
        cout << "==== HACKER TERMINAL ====\n";
        cout << "1. INITIATE CODE RUNNER\n";
        cout << "2. RETURN TO MAIN SYSTEM\n";
        cout << ">> ";
        getline(cin, choice);

        if (choice == "1") {
            CodeRunner game;
            game.run();
        }
        else if (choice == "2") {
            break;
        }
        else {
            cout << "INVALID SELECTION!";
            Sleep(1000);
        }
    }
    system("cls");
    show_logotype();
    show_help();
}