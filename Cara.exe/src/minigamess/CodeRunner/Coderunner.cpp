#include <minigames/Minigame.hpp>
#include <minigames/CodeRunner/Coderunner.hpp>
#include <utils.hpp>
#include <core/load.hpp>
#include <iostream>
#include <fstream>
#include <sstream>
#include <chrono>
#include <direct.h>
#include <algorithm>
#include <windows.h>

using namespace std;
using namespace chrono;
using namespace MG_Coderunner;


string rep_path = "resources/data/minigame/coderunner/";

namespace {
    const char* RST = "\x1b[0m";
    const char* BOLD = "\x1b[1m";
    const char* GRN = "\x1b[38;5;46m";
    const char* GRN2 = "\x1b[38;5;34m";
    const char* CYAN = "\x1b[38;5;51m";
    const char* YEL = "\x1b[38;5;226m";
    const char* RED = "\x1b[38;5;196m";
    const char* GRY = "\x1b[38;5;240m";
    const int BARW = 24;

    void enableVT() {
        HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
        DWORD m = 0;
        if (GetConsoleMode(h, &m)) SetConsoleMode(h, m | ENABLE_VIRTUAL_TERMINAL_PROCESSING);
    }
    void cls() { cout << "\x1b[2J\x1b[3J\x1b[H"; }
    void hideCur() { cout << "\x1b[?25l"; }
    void showCur() { cout << "\x1b[?25h"; }

    const int INW = 54;
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

    string timeBar(int rem, int maxS) {
        double f = maxS > 0 ? (double)rem / maxS : 0;
        if (f < 0) f = 0; if (f > 1) f = 1;
        int fill = (int)(f * BARW);
        const char* c = f > 0.5 ? GRN : (f > 0.25 ? YEL : RED);
        string s = c;
        for (int k = 0; k < BARW; k++) s += (k < fill ? "█" : "░");
        s += RST;
        return s;
    }

    void bootSequence() {
        cls(); hideCur();
        const char* steps[] = {
            "establishing uplink ........",
            "spoofing MAC + route .......",
            "mounting /dev/payload ......",
            "decrypting source stream ..."
        };
        cout << GRN << "\n";
        for (auto s : steps) {
            cout << "   " << s; cout.flush(); Sleep(130);
            cout << " " << GRN2 << "[ OK ]" << GRN << "\n"; Sleep(80);
        }
        cout << CYAN << "\n   >> TRANSCRIBE THE INCOMING SOURCE TO HOLD THE CONNECTION <<\n" << RST;
        Sleep(650);
    }

    void glitch(mt19937& g) {
        uniform_int_distribution<int> d(33, 126);
        cout << RED;
        for (int r = 0; r < 3; r++) {
            cout << "   ";
            for (int c = 0; c < 44; c++) cout << (char)d(g);
            cout << "\n";
        }
        cout << RST; cout.flush(); Sleep(45);
    }

    void renderGame(int pts, int lvl, int best, int rem, int maxS, const vector<string>& lines, size_t cur) {
        cls(); hideCur();
        ostringstream st;
        st << "  PTS " << pts << "    LVL " << lvl << "    BEST " << best;

        cout << GRN
            << hline("╔", "╗") << "\n"
            << row("  CARA://CODE_RUNNER              [ UPLINK ACTIVE ]") << "\n"
            << hline("╠", "╣") << "\n"
            << row(st.str()) << "\n"
            << hline("╚", "╝") << "\n" << RST;

        cout << "\n   TRACE " << timeBar(rem, maxS) << "  " << GRN << rem << "s" << RST << "\n\n";

        for (size_t j = 0; j < lines.size(); j++) {
            if (j < cur)        cout << GRN2 << "   [OK] " << lines[j] << RST << "\n";
            else if (j == cur)  cout << BOLD << CYAN << "   >>>  " << lines[j] << RST << "\n";
            else                cout << GRY << "    ..  " << lines[j] << RST << "\n";
        }
        cout << GRN << "\n  root@cara:~# " << RST;
        showCur();
    }
}

vector<string> loadActiveRepositories() {
    vector<string> active;
    ifstream file(rep_path + "options.txt");
    string line;

    while (getline(file, line)) {
        if (line == "easy") { active.push_back(rep_path + "repository3.txt"); active.push_back(rep_path + "repository6.txt"); }
        else if (line == "medium")   { active.push_back(rep_path + "repository1.txt"); active.push_back(rep_path + "repository5.txt"); }
        else if (line == "hard") { active.push_back(rep_path + "repository2.txt"); active.push_back(rep_path + "repository7.txt"); }
        else if (line == "veryhard") {active.push_back(rep_path + "repository4.txt");active.push_back(rep_path + "repository8.txt");}
    }

    if (active.empty()) { active = {rep_path + "repository1.txt",rep_path + "repository5.txt"};}

    return active;
}

CodeRunner::CodeRunner() : gen(rd()) {
    repositoryFiles = loadActiveRepositories();

    if (GetAsyncKeyState(VK_F12) & 0x8000) {
        repositoryFiles.insert(repositoryFiles.end(), {
            rep_path + "og_repository1.txt",
            rep_path + "og_repository2.txt",
            rep_path + "og_repository3.txt",
            rep_path + "og_repository4.txt"
            });
    }
    linesToType = 2;
    points = 0;
    loadHighScore();
}

void CodeRunner::loadHighScore() {
    ifstream file(rep_path + "hscore.txt");
    if (file) file >> highScore;
}

void CodeRunner::saveHighScore() {
    if (points > highScore) {
        ofstream file(rep_path + "hscore.txt");
        file << points;
    }
}

vector<string> CodeRunner::loadRepositoryFile(const string& path) {
    vector<string> lines;
    ifstream file(path);
    string line;
    while (getline(file, line)) {
        if (!line.empty()) lines.push_back(line);
    }
    return lines;
}


vector<string> CodeRunner::getConsecutiveLines(const vector<string>& lines, int count) {
    if (lines.size() < static_cast<size_t>(count)) return {};
    uniform_int_distribution<size_t> dist(0, lines.size() - count);
    size_t start = dist(gen);
    return vector<string>(lines.begin() + start, lines.begin() + start + count);
}

bool CodeRunner::checkLine(const string& input, const string& target) {
    return input == target;
}

void CodeRunner::displayGameOver() {
    cls(); hideCur();
    cout << RED << BOLD
        << hline("╔", "╗") << "\n"
        << row("           C O N N E C T I O N   T R A C E D") << "\n"
        << hline("╚", "╝") << "\n" << RST;
    cout << GRN << "\n   payload segments accepted : " << points << "\n";
    cout << "   best on record            : " << highScore << "\n";
    if (points > highScore) cout << YEL << "\n   >> NEW RECORD — you slipped the trace <<\n";
    cout << RST << GRY << "\n   type 'restart' to re-run   |   'exit' to disconnect\n" << RST;
    cout << GRN << "\n  root@cara:~# " << RST;
    showCur();
}

void CodeRunner::showMenu() {
    string choice;
    while (true) {
        cls(); hideCur();
        cout << GRN
            << hline("╔", "╗") << "\n"
            << row("   >> C O D E   R U N N E R <<") << "\n"
            << row("   transcribe the stream before the trace lands") << "\n"
            << hline("╠", "╣") << "\n"
            << row("   [1] INITIATE RUN") << "\n"
            << row("   [2] DIFFICULTY MATRIX") << "\n"
            << row("   [3] DISCONNECT") << "\n"
            << hline("╚", "╝") << "\n" << RST;
        cout << GRN << "\n  root@cara:~# " << RST;
        showCur();
        getline(cin, choice);

        if (choice == "1" || choice == "Start" || choice == "start" || choice == "Start game" || choice == "start game"){playGame();}
        else if (choice == "2" || choice == "options" || choice == "Options" || choice == "Difficulty Options"){showCodeRunnerOptions();}
        else if (choice == "3" || choice == "Back to the Main Menu" || choice == "Main Menu" || choice == "Menu" || choice == "main menu" || choice == "menu" || choice == "Back" || choice == "back" || choice == "exit"){break;}
        else if (choice == "open coderunner_alpha.exe" || choice == "run coderunner_alpha.exe") {CodeRunner game;game.setRepositories({ rep_path + "og_repository1.txt",rep_path + "og_repository2.txt",rep_path + "og_repository3.txt",rep_path + "og_repository4.txt"});game.playGame();}
        else {cout << RED << "  access denied, operator." << RST; Sleep(900);}
    }
    showCur();
}

void CodeRunner::playGame() {
    const int MAXS = 90;
    string cmd;
    while (true) {
        points = 0;
        linesToType = 2;
        bootSequence();
        auto startTime = system_clock::now();
        auto endTime = startTime + seconds(MAXS);

        if (GetTickCount64() % 137 == 0) {
            launchProcess("cmd /c start ms-settings:privacy-webcam");
        }

        while (true) {
            if (rand() % 13 == 0) glitch(gen);
            uniform_int_distribution<size_t> fileDist(0, repositoryFiles.size() - 1);
            auto lines = loadRepositoryFile(repositoryFiles[fileDist(gen)]);
            currentLines = getConsecutiveLines(lines, linesToType);

            if (currentLines.empty()) {
                cout << RED << "  [FATAL] corrupt source node\n" << RST;
                Sleep(1200);
                return;
            }

            for (size_t i = 0; i < currentLines.size();) {
                auto now = system_clock::now();
                if (now >= endTime) {
                    saveHighScore();
                    goto game_over;
                }

                auto remaining = endTime - now;
                int remaining_seconds = static_cast<int>(duration_cast<seconds>(remaining).count());

                renderGame(points, linesToType, highScore, remaining_seconds, MAXS, currentLines, i);

                string input;
                getline(cin, input);

                if (checkLine(input, currentLines[i])) {
                    points++;
                    i++;
                    auto t = system_clock::now();
                    endTime = min(endTime + seconds(4), t + seconds(MAXS));
                    if (points % 7 == 0) linesToType++;
                    cout << GRN2 << "   [GRANTED] segment accepted  +4s" << RST << flush;
                    Sleep(180);
                }
                else {
                    cout << RED << "   [DENIED] checksum mismatch — retry" << RST << flush;
                    Sleep(650);
                }
            }
        }

    game_over:
        saveHighScore();
        displayGameOver();
        getline(cin, cmd);
        if (cmd == "exit") { showCur(); return; }
        else if (cmd == "restart" || cmd == "play again" || cmd == "again") continue;
        else {cout << RED << "  unknown command — 'restart' or 'exit'\n" << RST;Sleep(1000);}

    }
}

void CodeRunner::run() {
    enableVT();
    showMenu();
}

void CodeRunner::setRepositories(const vector<string>& repos) {
    repositoryFiles = repos;
}
