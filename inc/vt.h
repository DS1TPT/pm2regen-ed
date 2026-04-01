/*
 * File Name: vt.h
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

#ifndef VT_H
#define VT_H

#include "main.h"

#define VT_COLS 80

#define KEY_BS 8
#define KEY_DEL 127
#define KEY_CR 13
#define KEY_LF 10
#define KEY_UP 'A'
#define KEY_DOWN 'B'
#define KEY_RIGHT 'C'
#define KEY_LEFT 'D'

void vt_cursor(unsigned x, unsigned y);
void vt_clearScreen();
void vt_clearLine(unsigned lineNum);
int vt_getKeypress(); /* get single keypress or 3 Byte escape sequence */
void vt_enableAnsi(BOOL state); /* enable/disable ANSI VT support */
void vt_setEchoCanonical(BOOL state); /* enable/disable echo and canonical input mode */

#endif /* VT_H */