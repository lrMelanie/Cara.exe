#pragma once
#ifndef REACTOR_HPP
#define REACTOR_HPP
#include <string>
#include <random>

using namespace std;

namespace MG_Reactor {

    class Reactor {
        int best;
        mt19937 gen;
        random_device rd;

        void loadBest();
        void saveBest(int score);
        void playSimple();
        void playExtended();

    public:
        Reactor();
        void run();
    };

}
#endif
