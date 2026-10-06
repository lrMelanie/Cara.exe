#include <minigames/Reactor/Reactor.hpp>
#include <windows.h>
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <algorithm>
#include <cctype>
#include <cstdlib>

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

    string gauge(int v, int mx, const char* col) {
        if (v < 0) v = 0;
        int w = 22;
        int fill = mx > 0 ? (v * w) / mx : 0;
        if (fill > w) fill = w;
        string s = col;
        for (int k = 0; k < w; k++) s += (k < fill ? "█" : "░");
        s += RST;
        return s;
    }

    const char* heatColor(int t) {
        if (t < 50) return GRN;
        if (t < 80) return YEL;
        return RED;
    }

    int readInt(int fallback) {
        string line;
        getline(cin, line);
        try { return stoi(line); }
        catch (...) { return fallback; }
    }

    char readKey() {
        string line;
        getline(cin, line);
        return line.empty() ? ' ' : (char)tolower((unsigned char)line[0]);
    }

    void pause(const char* msg) {
        cout << GRN << "\n  " << msg << RST;
        showCur();
        string dummy; getline(cin, dummy);
    }
}

namespace MG_Reactor {

Reactor::Reactor() : gen(rd()) {
    best = 0;
}

void Reactor::loadBest() {
    best = 0;
    ifstream file("resources/data/minigame/reactor/best.txt");
    if (file) file >> best;
}

void Reactor::saveBest(int score) {
    if (score > best) {
        best = score;
        ofstream file("resources/data/minigame/reactor/best.txt");
        file << score;
    }
}

void Reactor::playSimple() {
    int temp;
    int timer = 10, loading = 0, szansa, points = 0;
    int irp = 0, irc = 0, irw = 0, ira = 0, ira1 = 0, ira2 = 0, iro = 0, awari = 0, nawari = 0;
    char doing;
    string zatrzymanie;

    cls(); showCur();
    cout << GRN << "WCZYTYWANIE...\n" << RST;
    for (int i = 0; i < 19; i++) {
        cout << loading << "%\n";
        if (loading <= 10) { loading++; Sleep(120); }
        else { loading += 10; Sleep(60); }
    }
    cout << loading << "%\n";
    loading += 8;
    cout << loading << "%\n";
    Sleep(800);
    cout << "100%\n";
    Sleep(500);

    cout << "-------------------\n";
    Sleep(400);
    cout << "WPROWADZ AKTUALNA TEMPERATURE REAKTORA : ";
    temp = readInt(0);

    do {
        if (temp < 0) temp = 0;
        cout << "\n" << heatColor(temp) << "AKTUALNA TEMPERATURA: " << temp << RST << "\n";
        if (temp == 0) cout << "REAKTOR W TRYBIE CZUWANIA PROSZENIE O WLACZENIE MOCY";
        else if (temp < 30) cout << GRN << "TEMPERATURA PRAWIDLOWA. NIE REAGOWAC" << RST;
        else if (temp < 50) cout << "REAKTOR W STANIE PILNOWANIA. OBUDZIC PRACOWNIKA";
        else if (temp < 70) cout << YEL << "TEMPERATURA WYSOKA. DOLAC WODY." << RST;
        else if (temp < 100) cout << RED << "TEMPERATURA REAKTORA BLISKO STANU KRYTYCZNEGO. WYLACZYC DO CZASU SCHLODZENIA" << RST;
        else {
            cout << RED << BOLD << "REAKTOR SIEGNAL STANU KRYTYCZNEGO. WYBUCH ZA 45 SEKUND. TWOJE KOLA RATUNKOWE: ZADZWON DO RODZINY LUB ZACZNIJ SIE MODLIC" << RST;
            for (timer = 10; timer >= 0; timer--) {
                cout << "\n" << RED << timer << RST << "\n";
                Sleep(400);
            }
            cout << RED << BOLD << "GOODBYE" << RST << "\n";
            break;
        }

        cout << "\nLISTA POLECEN: \nW - WLACZENIE CHLODZENIA \nP - ZWIEKSZENIE MOCY \nQ - WYLACZENIE \nC - OBSERWUJ DALEJ\n";
        cout << ">> ";
        doing = readKey();

        switch (doing) {
        case 'p':
            temp = temp + rand() % 11 + 1;
            points = points + 3;
            irp++;
            break;

        case 'w':
            temp = temp - (rand() % 11 + 1);
            points = points - 5;
            irw++;
            break;

        case 'q':
            cout << "SYSTEM WYLACZONY\n";
            zatrzymanie = "STOP";
            break;

        case 'c':
            temp = temp + rand() % 5 + 1;
            points = points + 1;
            irc++;
            break;

        default:
            ira++;
            szansa = rand() % 25 + 1;
            if (szansa > 10) {
                cout << RED << "WYLACZENIE AWARYJNE NIE ZADZIALALO. AWARIA SYSTEMU" << RST;
                temp = temp + (rand() % 45 + 10);
                awari = awari + points;
                points = points + points;
                ira1++;
            }
            else {
                cout << "WYLACZANIE AWARYJNE SYSTEMU";
                temp = temp - (rand() % 45 + 10);
                nawari = nawari + (points / 2);
                points = points - (points / 2);
                ira2++;
            }
        }

        iro++;

        if (zatrzymanie == "STOP") {
            cout << "\n\nTwoje Punkty: " << points;
            cout << "\nIlosc ruchow: " << iro;
            cout << "\nIlosc chlodzenia: " << irw << "(" << irw * 5 << ")";
            cout << "\nIlosc zwiekszania mocy: " << irp << "(+" << irp * 3 << ")";
            cout << "\nIlosc obserwowania: " << irc << "(+" << irc * 1 << ")";
            cout << "\nIlosc zasilania awaryjnego: " << ira;
            cout << "\nIlosc awarii: " << ira1 << "(+" << awari << ")";
            cout << "\nIlosc wylaczen awaryjnych: " << ira2 << "(" << nawari << ")";
            break;
        }

    } while (true);

    pause("nacisnij Enter...");
}

void Reactor::playExtended() {
    int temp = 20, pressure = 10, coolant = 100, power = 0, turn = 0;
    loadBest();
    string note = "Reaktor online. Trzymaj temp i cisnienie ponizej 100, produkuj moc.";
    bool scram = false;

    auto render = [&]() {
        cls(); hideCur();
        ostringstream st;
        st << "  ZMIANA " << turn << "     MOC " << power << "     REKORD " << best;
        cout << GRN
            << hline("╔", "╗") << "\n"
            << row("  REACTOR CORE // EXTENDED            [ ONLINE ]") << "\n"
            << hline("╠", "╣") << "\n"
            << row(st.str()) << "\n"
            << hline("╚", "╝") << "\n" << RST;

        cout << "\n   TEMP      " << gauge(temp, 100, heatColor(temp)) << "  " << heatColor(temp) << temp << "/100" << RST << "\n";
        cout << "   CISNIENIE " << gauge(pressure, 100, heatColor(pressure)) << "  " << heatColor(pressure) << pressure << "/100" << RST << "\n";
        cout << "   CHLODZIWO " << gauge(coolant, 100, CYAN) << "  " << CYAN << coolant << "/100" << RST << "\n\n";

        cout << GRY << "   B=boost moc   C=chlodzenie   V=upust cisnienia   H=hold   S=scram\n" << RST;
        if (!note.empty()) cout << YEL << "\n   " << note << RST << "\n";
        cout << GRN << "\n  reaktor >> " << RST;
        showCur();
    };

    while (true) {
        turn++;
        temp += (int)(gen() % 3);
        int ev = (int)(gen() % 100) + 1;
        if (ev <= 15) { int s = 8 + (int)(gen() % 8); temp += s; pressure += 6; note = "ZDARZENIE: skok mocy! temp +" + to_string(s) + ", cisnienie rosnie."; }
        else if (ev <= 30) { int leak = 10 + (int)(gen() % 10); coolant -= leak; if (coolant < 0) coolant = 0; temp += 5; note = "ZDARZENIE: wyciek chlodziwa (-" + to_string(leak) + ")."; }
        else if (ev <= 40) { if (temp < 50 && pressure < 60) { power += 15; note = "ZDARZENIE: inspekcja zaliczona (+15 mocy)."; } else { note = "ZDARZENIE: inspekcja oblana (reaktor zbyt obciazony)."; } }
        else if (turn > 1) { note = "Reaktor stabilny."; }

        if (coolant > 100) coolant = 100;
        if (temp < 0) temp = 0;
        if (pressure < 0) pressure = 0;

        render();
        char c = readKey();

        if (c == 'b') { int g = 8 + (int)(gen() % 8); temp += g; pressure += 5; power += 10; note = "BOOST: +10 mocy, temp +" + to_string(g) + "."; }
        else if (c == 'c') { if (coolant >= 15) { coolant -= 15; int cd = 12 + (int)(gen() % 9); temp -= cd; if (temp < 0) temp = 0; note = "CHLODZENIE: temp -" + to_string(cd) + ", chlodziwo -15."; } else note = "Brak chlodziwa! Nie mozna schlodzic."; }
        else if (c == 'v') { int vd = 20 + (int)(gen() % 11); pressure -= vd; if (pressure < 0) pressure = 0; temp -= 5; if (temp < 0) temp = 0; power -= 3; if (power < 0) power = 0; note = "UPUST: cisnienie -" + to_string(vd) + ", -3 mocy."; }
        else if (c == 'h') { power += 2; coolant += 5; if (coolant > 100) coolant = 100; temp += 1 + (int)(gen() % 3); note = "HOLD: +2 mocy, chlodziwo regeneruje."; }
        else if (c == 's') { scram = true; break; }
        else { note = "Nieznana komenda. Reaktor czeka."; }

        if (temp >= 100 || pressure >= 100) {
            cls(); hideCur();
            cout << RED << BOLD
                << hline("╔", "╗") << "\n"
                << row("              M E L T D O W N") << "\n"
                << hline("╚", "╝") << "\n" << RST;
            for (int k = 5; k >= 1; k--) { cout << RED << "\n        rdzen przegrzany... " << k << RST << "\n"; Sleep(350); }
            cout << RED << BOLD << "\n   REAKTOR UTRACONY.\n" << RST;
            cout << GRN << "\n   moc wyprodukowana : " << power << "\n   rekord : " << best << "\n" << RST;
            saveBest(power);
            pause("nacisnij Enter...");
            return;
        }
    }

    cls(); hideCur();
    cout << GRN2 << BOLD
        << hline("╔", "╗") << "\n"
        << row("        SCRAM - BEZPIECZNE WYLACZENIE") << "\n"
        << hline("╚", "╝") << "\n" << RST;
    cout << GRN << "\n   zmiany przetrwane : " << turn << "\n   moc wyprodukowana : " << power << "\n   rekord : " << best << "\n";
    saveBest(power);
    if (power >= best) cout << YEL << "\n   >> NOWY REKORD <<\n" << RST;
    (void)scram;
    pause("nacisnij Enter...");
}

void Reactor::run() {
    enableVT();
    string choice;
    while (true) {
        cls(); hideCur();
        cout << GRN
            << hline("╔", "╗") << "\n"
            << row("   >> R E A C T O R   C O R E <<") << "\n"
            << hline("╠", "╣") << "\n"
            << row("   [1] SIMPLE CORE    (klasyczny reaktor)") << "\n"
            << row("   [2] EXTENDED CORE (cisnienie, chlodziwo, zdarzenia)") << "\n"
            << row("   [3] POWROT") << "\n"
            << hline("╚", "╝") << "\n" << RST;
        cout << GRN << "\n  root@cara:~# " << RST;
        showCur();
        getline(cin, choice);

        if (choice == "1") playSimple();
        else if (choice == "2") playExtended();
        else if (choice == "3") break;
        else { cout << RED << "  nieznana opcja.\x1b[0m"; Sleep(900); }
    }
    showCur();
}

}
