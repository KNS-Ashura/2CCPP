#include "Header/Game.h"

#include <iostream>

#ifdef _WIN32
#include <windows.h>

void enableANSIColors() {
    HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
    if (hOut == INVALID_HANDLE_VALUE) return;

    DWORD dwMode = 0;
    if (!GetConsoleMode(hOut, &dwMode)) return;

    dwMode |= ENABLE_VIRTUAL_TERMINAL_PROCESSING;
    SetConsoleMode(hOut, dwMode);
}
#endif

int main() {
    #ifdef _WIN32
        enableANSIColors();
    #endif

    Game TheDP;
    TheDP.launchGame();
    return 0;

}