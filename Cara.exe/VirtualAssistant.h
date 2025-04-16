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

class VirtualAssistant {
protected:
    std::vector<std::string> vol1;
    std::vector<std::string> vol2;
    std::vector<std::string> used_mottos;
    std::vector<std::string> used_sayings;
    std::vector<std::pair<time_t, std::string>> schedule;
    std::atomic<bool> reminderActive{ false };
    std::thread reminderThread;
    std::ofstream logFile;
    std::mt19937 gen;

    void reminderDaemon();
    std::vector<std::string> load_file(const std::string& path);
    void processMottoFile();
    void processSayingFile();

public:
    VirtualAssistant();
    virtual ~VirtualAssistant();
    void log(const std::string& action);
    void give_motto();
    void say();
    void add_event(const std::string& datetime, const std::string& event);
    void show_help();
    bool exit();
    void process_schedule_command(const std::string& args);
    void list_events();
    void remove_event(int index);
    void show_schedule_help();
    void print_slowly(const std::string& text, unsigned int delay = 30);
    void handle_query(const std::string& query);
    std::string get_ai_response(const std::string& query);
};
