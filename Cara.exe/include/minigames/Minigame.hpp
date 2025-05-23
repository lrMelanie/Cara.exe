#pragma once
#ifndef MINIGAME_H
#define MINIGAME_H
#include <core/VirtualAssistant.hpp>

void showCodeRunnerOptions();

class Minigame : public VirtualAssistant {
public:
    Minigame();
    void run();
};

#endif