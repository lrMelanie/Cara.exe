#pragma once
#ifndef DICEARENA_HPP
#define DICEARENA_HPP
#include <string>
#include <vector>
#include <random>

using namespace std;

namespace MG_DiceArena {

    class DiceArena {
        int hp;
        int maxHp;
        int shield;
        int wave;
        int score;
        int best;
        mt19937 gen;
        random_device rd;

        void loadBest();
        void saveBest();
        void intro();
        void render(const string& foe, int eHp, int eMax, int eAtk, int d1, int d2, int d3, const string& note);
        void gameOver();

    public:
        DiceArena();
        void run();
    };

}
#endif
