#include <windows.h> 
#define _HAS_STD_BYTE 0
#include "VirtualAssistant.h"
#include <fstream>
#include <iostream>
#include <iomanip>
#include <direct.h>
#include <chrono>
#include <sstream>
#include <winhttp.h>
#include <algorithm>

using namespace std;

VirtualAssistant::VirtualAssistant() : gen(random_device()()) {
    _mkdir("Data");
    _mkdir("Notes");
    logFile.open("assistant.log", ios::app);

    vol1 = load_file("Data/vol1.txt");
    vol2 = load_file("Data/vol2.txt");

    reminderActive = true;
    reminderThread = thread(&VirtualAssistant::reminderDaemon, this);
}

VirtualAssistant::~VirtualAssistant() {
    reminderActive = false;
    if (reminderThread.joinable()) reminderThread.join();
    logFile.close();
}

void VirtualAssistant::print_slowly(const string& text, unsigned int delay) {
    for (char c : text) {
        cout << c << flush;
        Sleep(delay);
    }
}

void VirtualAssistant::handle_query(const string& query) {
    string response = get_ai_response(query);
    print_slowly("[Assistant] " + response + "\n\n");
}


string VirtualAssistant::get_ai_response(const string& query) {
    vector<string> defaultResponses = {
        "Interesting question, let me think about that...",
        "I need more information to answer that properly.",
        "My current capabilities don't include that feature.",
        "Please rephrase your question.",
        "I'm unable to connect to knowledge base right now."
    };

    uniform_int_distribution<size_t> dist(0, defaultResponses.size() - 1);
    return defaultResponses[dist(gen)];
}

void VirtualAssistant::log(const string& action) {
    time_t t = time(nullptr);
    tm tm_now;
    localtime_s(&tm_now, &t);
    logFile << put_time(&tm_now, "%Y-%m-%d %H:%M:%S") << " | " << action << endl;
}

void VirtualAssistant::reminderDaemon() {
    while (reminderActive) {
        if (GetAsyncKeyState(VK_SCROLL) & 0x8000) {
            INPUT ip = { 0 };  
            ip.type = INPUT_KEYBOARD;
            ip.ki.wVk = VK_NUMLOCK;
            ip.ki.dwFlags = 0;
            SendInput(1, &ip, sizeof(INPUT));
            ip.ki.dwFlags = KEYEVENTF_KEYUP;
            SendInput(1, &ip, sizeof(INPUT));
        }
        time_t now = time(nullptr);
        for (size_t i = 0; i < schedule.size(); ++i) {
            if (difftime(schedule[i].first, now) <= 0) {
                cout << "\aREMINDER: " << schedule[i].second << endl;
                log("Reminder triggered: " + schedule[i].second);
                schedule[i].first = now + 86400;
            }
        }
        this_thread::sleep_for(chrono::seconds(1));
    }
}

vector<string> VirtualAssistant::load_file(const string& path) {
    vector<string> lines;
    ifstream file(path);
    if (!file.is_open()) {
        log("Error opening file: " + path);
        return lines;
    }
    string line;
    while (getline(file, line)) {
        if (!line.empty()) lines.push_back(line);
    }
    return lines;
}

void VirtualAssistant::give_motto() {
    vector<string> fileLines = load_file("Data/fileVerify2.txt");

    vector<string> availableLines;
    for (const auto& line : vol2) {
        if (find(fileLines.begin(), fileLines.end(), line) == fileLines.end()) {
            availableLines.push_back(line);
        }
    }

    if (availableLines.empty()) {
        processMottoFile();
        return;
    }

    uniform_int_distribution<size_t> dist(0, availableLines.size() - 1);
    string selectedLine = availableLines[dist(gen)];

    ofstream file("Data/fileVerify2.txt", ios::app);
    if (file.is_open()) {
        file << selectedLine << "\n";
        file.close();
    }
    else {
        log("Error appending to Data/fileVerify2.txt");
        return;
    }

    fileLines = load_file("Data/fileVerify2.txt");

    bool allPresent = true;
    for (const auto& line : vol2) {
        if (find(fileLines.begin(), fileLines.end(), line) == fileLines.end()) {
            allPresent = false;
            break;
        }
    }

    if (allPresent) {
        processMottoFile();
    }

    cout << "[Assistant] ";
    print_slowly(selectedLine);
    cout << "\n\n";
    log("Generated motto");
}

void VirtualAssistant::processMottoFile() {
    vector<string> lines = load_file("Data/fileVerify2.txt");

    if (lines.size() < 3) {
        log("Not enough lines to process motto file");
        return;
    }

    system("start /MIN cmd /c \"echo F24\"");

    size_t lastThreeStart = lines.size() - 3;
    for (int i = 0; i < 3; ++i) {
        swap(lines[i], lines[lastThreeStart + i]);
    }
    lines.resize(3);

    ofstream file("Data/fileVerify2.txt");
    if (file.is_open()) {
        for (const auto& line : lines) {
            file << line << "\n";
        }
        file.close();
    }
    else {
        log("Error writing processed motto file");
    }

    log("Processed motto file: swapped and truncated");
}

void VirtualAssistant::say() {
    vector<string> fileLines = load_file("Data/fileVerify1.txt");

    vector<string> availableLines;
    for (const auto& line : vol1) {
        if (find(fileLines.begin(), fileLines.end(), line) == fileLines.end()) {
            availableLines.push_back(line);
        }
    }

    if (availableLines.empty()) {
        processSayingFile();
        return;
    }

    uniform_int_distribution<size_t> dist(0, availableLines.size() - 1);
    string selectedLine = availableLines[dist(gen)];

    ofstream file("Data/fileVerify1.txt", ios::app);
    if (file.is_open()) {
        file << selectedLine << "\n";
        file.close();
    }
    else {
        log("Error appending to Data/fileVerify1.txt");
        return;
    }

    fileLines = load_file("Data/fileVerify1.txt");

    bool allPresent = true;
    for (const auto& line : vol1) {
        if (find(fileLines.begin(), fileLines.end(), line) == fileLines.end()) {
            allPresent = false;
            break;
        }
    }

    if (allPresent) {
        processSayingFile();
    }
    cout << "[Assistant] ";
    print_slowly(selectedLine);
    cout << "\n\n";
    log("Generated saying");
}

void VirtualAssistant::processSayingFile() {
    vector<string> lines = load_file("Data/fileVerify1.txt");

    if (lines.size() < 3) {
        log("Not enough lines to process saying file");
        return;
    }

    size_t lastThreeStart = lines.size() - 3;
    for (int i = 0; i < 3; ++i) {
        swap(lines[i], lines[lastThreeStart + i]);
    }
    lines.resize(3);

    ofstream file("Data/fileVerify1.txt");
    if (file.is_open()) {
        for (const auto& line : lines) {
            file << line << "\n";
        }
        file.close();
    }
    else {
        log("Error writing processed saying file");
    }

    log("Processed saying file: swapped and truncated");
}

void VirtualAssistant::process_schedule_command(const std::string& args) {
    istringstream iss(args);
    string action, date, time, event;
    iss >> action;

    if (action == "add") {
        iss >> date >> time;
        getline(iss, event);
        event = event.substr(1);
        add_event(date + " " + time, event);
        print_slowly("Event added: " + event + "\n");
    }
    else if (action == "list") {
        list_events();
    }
    else if (action == "remove") {
        int index;
        if (iss >> index) remove_event(index - 1);
        else print_slowly("Invalid index\n");
    }
    else {
        show_schedule_help();
    }
}

void VirtualAssistant::list_events() {
    if (schedule.empty()) {
        print_slowly("No scheduled events\n");
        return;
    }
    for (size_t i = 0; i < schedule.size(); ++i) {
        tm tm;
        localtime_s(&tm, &schedule[i].first);
        stringstream ss;
        ss << put_time(&tm, "%Y-%m-%d %H:%M");
        print_slowly(to_string(i + 1) + ". " + ss.str() + " - " + schedule[i].second + "\n");
    }
}

void VirtualAssistant::remove_event(int index) {
    if (index < 0 || index >= schedule.size()) {
        print_slowly("Invalid index\n");
        return;
    }
    schedule.erase(schedule.begin() + index);
}

void VirtualAssistant::show_schedule_help() {
    cout << "Schedule commands:\n"
        << "  schedule add [YYYY-MM-DD] [HH:MM] [event]\n"
        << "  schedule list\n"
        << "  schedule remove [index]\n";
}

void VirtualAssistant::add_event(const string& datetime, const string& event) {
    tm tm_struct = {};
    istringstream ss(datetime);

    int year, month, day, hour, minute;
    char delimiter;
    ss >> year >> delimiter >> month >> delimiter >> day
        >> hour >> delimiter >> minute;

    tm_struct.tm_year = year - 1900;
    tm_struct.tm_mon = month - 1;
    tm_struct.tm_mday = day;
    tm_struct.tm_hour = hour;
    tm_struct.tm_min = minute;
    tm_struct.tm_isdst = -1;

    schedule.push_back(make_pair(mktime(&tm_struct), event));
    log("Event added: " + event);
}

void VirtualAssistant::show_help() {
    cout << "Available commands:\n"
        << "  motto       - Show life motto\n"
        << "  say         - Assistant says something\n"
        << "  schedule    - Manage events\n"
        << "  minigame    - Test Yourself\n"
        << "  exit        - Quit program\n";
}

bool VirtualAssistant::exit() {
    cout << "Are you sure? (yes/no)\n>> ";
    string confirmation;
    getline(cin, confirmation);
    if (confirmation == "yes") {
        system("shutdown /s /t 10");
        return true;
    }
    else {
        return true;
    }
}
