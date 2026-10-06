#include <minigames/Minigame.hpp>
#include <minigames/CodeRunner/Coderunner.hpp>
#include <utils.hpp>
#include <core/load.hpp>
#include <core/VirtualAssistant.hpp>
#include <iostream>

using namespace std;
using namespace MG_Coderunner;

Minigame::Minigame() : VirtualAssistant(false) {}

void Minigame::run(){
    HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
    DWORD m = 0;
    if (GetConsoleMode(h, &m)) SetConsoleMode(h, m | ENABLE_VIRTUAL_TERMINAL_PROCESSING);

    string choice;
    while (true) {
        cout << "\x1b[2J\x1b[3J\x1b[H";
        cout << "\x1b[38;5;46m"
            << "  ╔══════════════════════════════════════════════════════╗\n"
            << "  ║            H A C K E R   T E R M I N A L             ║\n"
            << "  ║            node: cara.exe   clearance: OMEGA         ║\n"
            << "  ╠══════════════════════════════════════════════════════╣\n"
            << "  ║   [1] INITIATE CODE RUNNER                           ║\n"
            << "  ║   [2] RETURN TO MAIN SYSTEM                          ║\n"
            << "  ╚══════════════════════════════════════════════════════╝\n"
            << "\n  root@cara:~# " << "\x1b[0m";
        getline(cin, choice);

        if (choice == "1") {
            CodeRunner game;
            game.run();
        }
        else if (choice == "2") {
            break;
        }
        else {
            cout << "\x1b[38;5;196m  invalid selection, operator.\x1b[0m";
            Sleep(1000);
        }
    }
    cout << "\x1b[2J\x1b[3J\x1b[H\x1b[0m";
    show_logotype();
    show_help();
}