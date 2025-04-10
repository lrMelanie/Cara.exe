#define _HAS_STD_BYTE 0
#include "main.h"
#include "utils.h"
#include "VirtualAssistant.h"
#include "Minigame.h"
#include "load.h"
#include <iostream>
#include <windows.h>
#include <fstream>
#include <mmsystem.h>
#include <string>
#include <cstdio>
#include <cstdlib>
#include <sstream>

using namespace std;

#pragma comment(lib, "winmm.lib")
#pragma comment(lib, "kernel32.lib")
#pragma comment(lib, "user32.lib")
#pragma comment(lib, "advapi32.lib")
#pragma comment(lib, "ole32.lib")


int APIENTRY WinMain(
    _In_ HINSTANCE hInstance,
    _In_opt_ HINSTANCE hPrevInstance,
    _In_ LPSTR lpCmdLine,
    _In_ int nCmdShow)
{
    srand(static_cast<unsigned int>(time(nullptr)));
    if (!IsRunAsAdmin()) {
        MessageBoxW(nullptr, L"Uruchom jako administrator!", L"Błąd", MB_ICONERROR);
        return 1;
    }

    AllocConsole();
    FILE* fpOut, * fpIn;

    if (freopen_s(&fpOut, "CONOUT$", "w", stdout) != 0 ||
        freopen_s(&fpIn, "CONIN$", "r", stdin) != 0)
    {
        MessageBoxW(nullptr, L"Błąd inicjalizacji konsoli!", L"Error", MB_ICONERROR);
        return 1;
    }

    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);
    VirtualAssistant assistant;

    show_loading();
    system("cls");
    cout << "----------------------------------";
    show_logotype();

    Sleep(600);
    assistant.print_slowly( "Hello! I'm Cara and I am your virtual assistant.\n");
    Sleep(600);
    assistant.show_help();

    string command;
    while (true) {
        cout << ">> ";
        getline(cin, command);

        if (command == "WELCOMETOTHEGAME") {execute_welcome_sequence();}
        else if (command.rfind("schedule ", 0) == 0) {assistant.process_schedule_command(command.substr(9));}
        else if (command == "schedule") {assistant.show_schedule_help();}
        else if (command == "A.L.I.V.E") {execute_spectral_broadcast();cout << "[System] Audio calibration complete\n";}
        else if (command == "exit" || command == "quit") {if (assistant.exit()) break;}
        else if (command == "minigame") {Minigame mg;mg.run();}
        else if (command == "help") {assistant.show_help();}
        else if (command == "HELP-ME") {trigger_phantom_protocol();cout << "[System] Diagnostic tools activated\n";}
        else if (command == "motto") {assistant.give_motto();}
        else if (command == "say") {assistant.say();}
        else if (command == "D0N'T-L00K-B3H1ND-Y0U") {initiate_black_mirror();cout << "[System] Environment scan initialized\n";}
        else {assistant.handle_query(command); }
    }

    cout << "Goodbye!\n";
    FreeConsole();
    system("PAUSE");
    return 0;
}