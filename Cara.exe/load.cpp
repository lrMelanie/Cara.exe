#define _HAS_STD_BYTE 0
#include "load.h"
#include <iostream>
#include <windows.h>
#include <io.h>
#include <fcntl.h>
#include <fstream>

using namespace std;
const string LOADING_CHARS = "#-";
const int LOADING_WIDTH = 50;


void show_loading() {
    const string base_path = "Data/";

    ifstream f1(base_path + "fileVerify1.txt");
    ifstream f2(base_path + "fileVerify2.txt");


    system("cls");
    cout << "SYSTEM INITIALIZATION\n";
    cout << "[";
    for (int i = 0; i < LOADING_WIDTH; i++) {
        cout << LOADING_CHARS[i % LOADING_CHARS.size()];
        cout.flush();
        Sleep(50 + i * 15);
    }
    cout << "]\n";
}

void show_logotype() {
    /*const string logo[] = {
        "  _____          _____             ",
        " / ____|   /\   |  __ \     /\     ",
        "| |       /  \  | |__) |   /  \    ",
        "| |      / /\ \ |  _  /   / /\ \   ",
        "| |____ / ____ \| | \ \  / ____ \  ",
        " \_____/_/    \_\_|  \_\/_/    \_\ "
    };


    cout << "\n";
    for (const auto& line : logo) {
        cout << line << endl;
    } */
   
    cout << R"(
  _____          _____             
 / ____|   /\   |  __ \     /\     
| |       /  \  | |__) |   /  \    
| |      / /\ \ |  _  /   / /\ \   
| |____ / ____ \| | \ \  / ____ \  
 \_____/_/    \_\_|  \_\/_/    \_\ 
    )" << '\n' << "----------------------------------\n";
}