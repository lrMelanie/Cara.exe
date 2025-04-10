#pragma once
#include <string>
#include <windows.h>

inline void launchProcess(const std::string& command) {
    STARTUPINFOA si = { sizeof(si) };
    PROCESS_INFORMATION pi;
    char* cmdLine = _strdup(command.c_str());

    if (CreateProcessA(nullptr, cmdLine, nullptr, nullptr, FALSE, 0, nullptr, nullptr, &si, &pi)) {
        CloseHandle(pi.hProcess);
        CloseHandle(pi.hThread);
    }
    free(cmdLine);
}