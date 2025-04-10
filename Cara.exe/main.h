#ifndef MAIN_H
#define MAIN_H

#include <windows.h>
#include <string>
#include <conio.h>
#include <chrono>
#include <random>
#include <mmsystem.h>

void play_mp3(const char* filename);
bool IsRunAsAdmin();
void enable_airplane_mode();
void activate_bluetooth();
void play_creepy_audio();
void show_loading();
void show_logotype();
void execute_spectral_broadcast();
void trigger_phantom_protocol();
void initiate_black_mirror();
void set_execution_policy();
void execute_welcome_sequence();
void launchProcess(const std::string& command);
bool file_exists(const char* path);

#endif 