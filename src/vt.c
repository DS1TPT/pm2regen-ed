/*
 * File Name: vt.c
 * Description: ANSI VT standard escape sequence support for pm2regen-ed
 * Notice: This file is a part of "pm2regen-ed".
 *         Please check main.c or README.md for more information.
 * 
 * Copyright (C) 2026 Lee Geon-goo
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <https://www.gnu.org/licenses/>.
 */

#include "vt.h"

void vt_cursor(unsigned x, unsigned y) { printf("\033[%u;%uH", y, x); }

void vt_clearScreen() { printf("\033[2J"); }

void vt_clearLine(unsigned lineNum)
{
    vt_cursor(1, lineNum);
    for (int i = 0; i < 80; i++) {
        printf(" ");
    }
    vt_cursor(1, lineNum);
}

int vt_getKeypress() 
{
    int ch = getchar();
    if (ch == '\033') { /* escape sequence */
        getchar(); /* drop '[' */
        return getchar();
    } else {
        return ch;
    }
}

#ifdef _WIN32
void vt_enableAnsi(BOOL state)
{
    SetConsoleOutputCP(CP_UTF8); /* not related to ansi but enabling utf-8 code page is necessary */
    _setmode(_fileno(stdin), _O_BINARY); /* also not related to ansi, but this is necessary to handle enter key correctly on windows */

    HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
    HANDLE hIn = GetStdHandle(STD_INPUT_HANDLE);

    DWORD dwOutMode = 0, dwInMode = 0;
    if (state) {
        GetConsoleMode(hOut, &dwOutMode);
        dwOutMode |= ENABLE_VIRTUAL_TERMINAL_PROCESSING;
        SetConsoleMode(hOut, dwOutMode);

        GetConsoleMode(hIn, &dwInMode);
        dwInMode |= ENABLE_VIRTUAL_TERMINAL_INPUT;
        SetConsoleMode(hIn, dwInMode);
    } else {
        GetConsoleMode(hOut, &dwOutMode);
        dwOutMode &= ~ENABLE_VIRTUAL_TERMINAL_PROCESSING;
        SetConsoleMode(hOut, dwOutMode);

        GetConsoleMode(hIn, &dwInMode);
        dwInMode &= ~ENABLE_VIRTUAL_TERMINAL_INPUT;
        SetConsoleMode(hIn, dwInMode);
    }
}

void vt_setEchoCanonical(BOOL state) /* enable/disable echo and canonical input mode */
{
    HANDLE hStdin = GetStdHandle(STD_INPUT_HANDLE);
    DWORD mode;
    GetConsoleMode(hStdin, &mode);
    if (state) {
        mode |= (ENABLE_ECHO_INPUT | ENABLE_LINE_INPUT);
    } else {
        mode &= ~(ENABLE_ECHO_INPUT | ENABLE_LINE_INPUT);
    }

    SetConsoleMode(hStdin, mode);
}
#else
void vt_enableAnsi(BOOL state) {}

void vt_setEchoCanonical(BOOL state)  /* enable/disable echo and canonical input mode */
{
    static struct termios orig, new;
    static BOOL isFirstRun = TRUE;

    if (isFirstRun == TRUE) {
        tcgetattr(STDIN_FILENO, &orig);
        new = orig;
        new.c_lflag &= ~(ICANON | ECHO);
        isFirstRun = FALSE;
    }

    if (state) {
        tcsetattr(STDIN_FILENO, TCSANOW, &orig);
    } else {
        tcsetattr(STDIN_FILENO, TCSANOW, &new);
    }
}
#endif