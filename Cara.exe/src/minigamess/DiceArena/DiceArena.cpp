#include <minigames/DiceArena/DiceArena.hpp>
#include <windows.h>
#include <iostream>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <cctype>

using namespace std;

namespace {
    const char* RST = "\x1b[0m";
    const char* BOLD = "\x1b[1m";
    const char* GRN = "\x1b[38;5;46m";
    const char* GRN2 = "\x1b[38;5;34m";
    const char* CYAN = "\x1b[38;5;51m";
    const char* YEL = "\x1b[38;5;226m";
    const char* RED = "\x1b[38;5;196m";
    const char* GRY = "\x1b[38;5;240m";
    const int INW = 54;

    void enableVT() {
        HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
        DWORD m = 0;
        if (GetConsoleMode(h, &m)) SetConsoleMode(h, m | ENABLE_VIRTUAL_TERMINAL_PROCESSING);
    }
    void cls() { cout << "\x1b[2J\x1b[3J\x1b[H"; }
    void hideCur() { cout << "\x1b[?25l"; }
    void showCur() { cout << "\x1b[?25h"; }

    string hline(const char* l, const char* r) {
        string s = l;
        for (int i = 0; i < INW; i++) s += "═";
        return "  " + s + r;
    }
    string row(const string& content) {
        string c = content;
        if ((int)c.size() < INW) c += string(INW - c.size(), ' ');
        else c = c.substr(0, INW);
        return "  ║" + c + "║";
    }

    string bar(int cur, int mx, const char* col) {
        if (cur < 0) cur = 0;
        int w = 20;
        int fill = mx > 0 ? (cur * w) / mx : 0;
        if (fill > w) fill = w;
        string s = col;
        for (int k = 0; k < w; k++) s += (k < fill ? "█" : "░");
        s += RST;
        return s;
    }
}

namespace MG_DiceArena {

static const string FOES[] = {
    "WORM.exe", "ROOTKIT", "TROJAN", "DAEMON",
    "RANSOM.dll", "B0TNET", "KEYL0GGER", "WRAITH"
};

DiceArena::DiceArena() : gen(rd()) {
    hp = maxHp = 25;
    shield = 0;
    wave = 1;
    score = 0;
    best = 0;
}

void DiceArena::loadBest() {
    best = 0;
    ifstream file("resources/data/minigame/dicearena/best.txt");
    if (file) file >> best;
}

void DiceArena::saveBest() {
    if (score > best) {
        ofstream file("resources/data/minigame/dicearena/best.txt");
        file << score;
    }
}

void DiceArena::intro() {
    cls(); hideCur();
    cout << GRN
        << hline("╔", "╗") << "\n"
        << row("   >> D I C E   A R E N A <<") << "\n"
        << row("   roll 3 dice, assign each one, survive the queue") << "\n"
        << hline("╠", "╣") << "\n"
        << row("   a = attack   spend a die as damage to the process") << "\n"
        << row("   d = block    add the die to your shield this turn") << "\n"
        << row("   h = heal      restore that many HP (up to max)") << "\n"
        << row("   type 3 letters, e.g.  ada   (enter = all attack)") << "\n"
        << hline("╚", "╝") << "\n" << RST;
    cout << CYAN << "\n   The daemons are queued. Clear as many waves as you can.\n" << RST;
    cout << GRN << "\n  press Enter to start..." << RST;
    showCur();
    string dummy; getline(cin, dummy);
}

void DiceArena::render(const string& foe, int eHp, int eMax, int eAtk, int d1, int d2, int d3, const string& note) {
    cls(); hideCur();
    ostringstream top;
    top << "  WAVE " << wave << "    SCORE " << score << "    BEST " << best;

    cout << GRN
        << hline("╔", "╗") << "\n"
        << row("  DICE ARENA                          [ COMBAT ]") << "\n"
        << hline("╠", "╣") << "\n"
        << row(top.str()) << "\n"
        << hline("╚", "╝") << "\n" << RST;

    ostringstream eline;
    eline << "   " << RED << foe << RST << "  (atk " << eAtk << ")";
    cout << "\n" << eline.str() << "\n";
    cout << "   FOE  " << bar(eHp, eMax, RED) << "  " << RED << eHp << "/" << eMax << RST << "\n\n";
    cout << "   YOU  " << bar(hp, maxHp, GRN) << "  " << GRN << hp << "/" << maxHp << RST
         << "   " << CYAN << "shield " << shield << RST << "\n\n";

    cout << "   DICE   " << BOLD << CYAN
         << "[1] " << d1 << "     [2] " << d2 << "     [3] " << d3 << RST << "\n";
    cout << GRY << "   a=attack  d=block  h=heal   (3 letters, enter = all attack)\n" << RST;

    if (!note.empty()) cout << YEL << "\n   " << note << RST << "\n";
    cout << GRN << "\n  assign >> " << RST;
    showCur();
}

void DiceArena::gameOver() {
    cls(); hideCur();
    cout << RED << BOLD
        << hline("╔", "╗") << "\n"
        << row("           P R O C E S S   K I L L E D") << "\n"
        << hline("╚", "╝") << "\n" << RST;
    cout << GRN << "\n   waves cleared : " << score << "\n";
    cout << "   best on record : " << best << "\n";
    if (score > best) cout << YEL << "\n   >> NEW RECORD <<\n";
    cout << RST << GRY << "\n   type 'restart' to fight again   |   'exit' to leave\n" << RST;
    cout << GRN << "\n  root@cara:~# " << RST;
    showCur();
}

void DiceArena::run() {
    enableVT();
    string cmd;
    do {
        hp = maxHp = 25;
        shield = 0;
        wave = 1;
        score = 0;
        loadBest();
        intro();

        while (hp > 0) {
            string foe = FOES[(wave - 1) % (sizeof(FOES) / sizeof(FOES[0]))];
            int eMax = 8 + wave * 4;
            int eHp = eMax;
            int eAtk = 3 + wave;
            string note = "a hostile process spawns: " + foe;

            while (eHp > 0 && hp > 0) {
                shield = 0;
                uniform_int_distribution<int> die(1, 6);
                int d1 = die(gen), d2 = die(gen), d3 = die(gen);
                render(foe, eHp, eMax, eAtk, d1, d2, d3, note);

                string a;
                getline(cin, a);

                int dvals[3] = { d1, d2, d3 };
                int atk = 0, def = 0, heal = 0;
                for (int i = 0; i < 3; i++) {
                    char c = (i < (int)a.size()) ? (char)tolower((unsigned char)a[i]) : 'a';
                    if (c == 'd') def += dvals[i];
                    else if (c == 'h') heal += dvals[i];
                    else atk += dvals[i];
                }

                eHp -= atk;
                shield += def;
                int before = hp;
                hp = min(maxHp, hp + heal);
                int healed = hp - before;

                if (eHp <= 0) {
                    note = foe + " terminated! (" + to_string(atk) + " dmg)";
                    break;
                }

                int dmg = eAtk - shield;
                if (dmg < 0) dmg = 0;
                hp -= dmg;

                ostringstream ns;
                ns << "you: " << atk << " dmg";
                if (def) ns << ", " << def << " block";
                if (healed) ns << ", +" << healed << " hp";
                ns << "   |   " << foe << " hits for " << dmg;
                note = ns.str();
            }

            if (hp > 0) {
                score++;
                wave++;
                int before = hp;
                hp = min(maxHp, hp + 5);
                cls(); hideCur();
                cout << GRN2 << "\n   [PURGED] " << foe << " cleared.  +" << (hp - before) << " HP restored.\n" << RST;
                cout << GRY << "   next process incoming...\n" << RST;
                cout << GRN << "\n  press Enter..." << RST;
                showCur();
                string dummy; getline(cin, dummy);
            }
        }

        gameOver();
        getline(cin, cmd);
        for (auto& ch : cmd) ch = (char)tolower((unsigned char)ch);

    } while (cmd == "restart" || cmd == "again" || cmd == "r");

    showCur();
}

}
