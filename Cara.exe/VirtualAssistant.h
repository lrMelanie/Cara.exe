#pragma once
#include <string>
#include <vector>
#include <fstream>
#include <ctime>
#include <atomic>
#include <thread>
#include <random>
#include <iomanip>
#include <sstream>
#include <algorithm>

using namespace std;

class VirtualAssistant {
protected:
    vector<string> vol1;
    vector<string> vol2;
    vector<string> used_mottos;
    vector<string> used_sayings;
    vector<pair<time_t, string>> schedule;
    atomic<bool> reminderActive{ false };
    thread reminderThread;
    ofstream logFile;
    mt19937 gen;

    void reminderDaemon();
    vector<string> load_file(const string& path);
    void processMottoFile();
    void processSayingFile();

public:
    VirtualAssistant();
    virtual ~VirtualAssistant();
    void log(const string& action);
    void give_motto();
    void say();
    void add_event(const string& datetime, const string& event);
    void show_help();
    bool exit();
    void process_schedule_command(const string& args);
    void list_events();
    void remove_event(int index);
    void show_schedule_help();
    void print_slowly(const string& text, unsigned int delay = 30);
    void handle_query(const string& query);
    string get_ai_response(const string& query);
};
