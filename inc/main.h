/*
 * File Name: main.h
 * Description: main header for global macros and includes of pm2regen-ed
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

#ifndef MAIN_H
#define MAIN_H

/* Build-time configurations */
#define DEFAULT_LANG LANG_EN
#define SLEEP_DURATION 3 /* how many seconds to sleep before exit, if file selector has been launched */

/* Includes */
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include "langPack.h"

/* Definitions */
#ifndef FALSE
#define FALSE 0
#endif
#ifndef TRUE
#define TRUE 1
#endif

#define PM2REGEN_ED_VERSION "v1.0"

#define SAVE_NUM_NOT_SET -1
#define SAVE_NUM_MAX 30

/* OS-dependent includes and defines */
#ifdef _WIN32

#include <windows.h>
#include <conio.h>
#include <fcntl.h>

#define PATH_MAX_LEN MAX_PATH

#else

#include <termios.h>
#include <unistd.h>
#include <dirent.h>
#include <limits.h>
#define PATH_MAX_LEN PATH_MAX

#endif

/* Typedef and Struct */
typedef int BOOL;

typedef enum {
    SUCCESS = 0x00,
    FAIL_WRITE = 0x01,
    FAIL_READ = 0x02,
    FAIL_OPEN = 0x03,
    FAIL_MEMORY = 0x04,
    FAIL_FILESIZE = 0x05,
    FAIL_BAK = 0x06,
    FAIL_INVALID_FILE = 0x07,
    CANCELLED = 0x10
} resRetTypedef;

typedef enum {
    POPUP_OK = 0,
    POPUP_YN = 1
} popupTypedef;

typedef enum { /* 0x<X><Y> */
    COORD_COL_COUNT = 2,
    COORD_LIMIT_COL0 = 15,
    COORD_LIMIT_COL1 = 12,
    
    COORD_STAMINA = 0x00,
    COORD_STRENGTH = 0x01,
    COORD_INTELLIGENCE = 0x02,
    COORD_REFINEMENT = 0x03,
    COORD_GLAMOUR = 0x04,
    COORD_MORALITY = 0x05,
    COORD_FAITH = 0x06,
    COORD_SIN = 0x07,
    COORD_SENSITIVITY = 0x08,
    COORD_STRESS = 0x09,

    COORD_MONEY = 0x0A,
    COORD_MATERNAL_INSTINCT = 0x0B,
    COORD_RENOWN = 0x0C,
    COORD_MONSTERS_KILLED = 0x0D,

    COORD_FIGHT_REPUTATION = 0x10,
    COORD_COMBAT_SKILL = 0x11,
    COORD_ATTACK = 0x12,
    COORD_DEFENSE = 0x13,
    COORD_MAGIC_REPUTATION = 0x14,
    COORD_MAGIC_SKILL = 0x15,
    COORD_MAGIC_ATTACK = 0x16,
    COORD_MAGIC_DEFENSE = 0x17,

    COORD_RELATIONSHIP_PRINCE = 0x18,
    COORD_RELATIONSHIP_FATHER = 0x19,
    COORD_RELATIONSHIP_BUTLER = 0x1A,
    
    COORD_SOCIAL_REPUTATION = 0x20,
    COORD_DECORUM = 0x21,
    COORD_ARTISTRY = 0x22,
    COORD_ELOQUENCE = 0x23,
    COORD_HOUSEWORK_REPUTATION = 0x24,
    COORD_COOKING = 0x25,
    COORD_CLEANING = 0x26,
    COORD_TEMPER = 0x27,

    COORD_HEIGHT = 0x28,
    COORD_WEIGHT = 0x29,
    COORD_BUST = 0x2A,
    COORD_WAIST = 0x2B,
    COORD_HIPS = 0x2C
} selectorCoord;

/* exported global variables */
extern int g_lang;

#endif /* MAIN_H */