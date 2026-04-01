/*
 * File Name: save.h
 * Description: save data handling for pm2regen-ed
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

#ifndef SAVE_H
#define SAVE_H

#include "main.h"
#include "file.h"

typedef uint16_t u16fxp2dp_t; /* 16 bit fixed point (2 decimal places) 
                                 example: 15944(10) is 159.44(10)     */
#define NAME_MAX_BYTES 12 /* CJK; Maximum for English name is 8 Bytes */
#define SAVE_SIZE_MIN 1700 /* Save size right after opening, with 8 characters each for first and last name, is 1712 Bytes */

/* These values are arbitraty unless commented.
 * U16FXP2DP_T_LIMIT defines maximum value the editor ui will accept. 
 * Any value between 0 and U16FXP2DP_T_LIMIT can be input at editing mode.
 * The other values define each stats' minimum and maximum.
 * If input value exceeds the limit and the user press enter/space key to confirm,
 * the program will set the value to be in the range automatically before saving it to SavDat structure.
 * Note: U16FXP2DP_T_LIMIT will be used by ui.c, and the other macros will be used in function save_writeToStructByCoord.
 */
#define U16FXP2DP_T_LIMIT 22000
#define HEIGHT_MAX 22000
#define HEIGHT_MIN 13000 
#define BWH_MIN 3500
#define BWH_MAX 13000
#define WEIGHT_MIN 2500 /* In-game Limit */
#define WEIGHT_MAX 8000 /* In-game Limit */


struct save_SavDat { /* Data to be edited */
    uint16_t stamina;
    uint16_t strength;
    uint16_t intelligence;
    uint16_t refinement;
    uint16_t glamour;
    uint16_t morality;
    uint16_t faith;
    uint16_t sin;
    uint16_t sensitivity;
    uint16_t stress;
    
    uint16_t fightReputation;
    uint16_t magicReputation;
    uint16_t socialReputation;
    uint16_t houseReputation;
    
    uint16_t combatSkill;
    uint16_t attack;
    uint16_t defense;
    
    uint16_t magicSkill;
    uint16_t magicAttack;
    uint16_t magicDefense;
    
    uint16_t decorum;
    uint16_t artistry;
    uint16_t eloquence;
    
    uint16_t cooking;
    uint16_t cleaning;
    uint16_t temper;
    
    int32_t money;
    uint16_t renown;

    u16fxp2dp_t height;
    u16fxp2dp_t weight;
    u16fxp2dp_t bust;
    u16fxp2dp_t waist;
    u16fxp2dp_t hips;

    uint16_t relationshipPrince;
    uint16_t relationshipFather;
    uint16_t relationshipButler;
    uint16_t maternalInstinct;
    uint16_t monstersKilled;
};

void save_printStat(struct save_SavDat *psSave);
void save_highlightStat(struct save_SavDat *psSave, int coord, BOOL isOn); /* coord format: 0x<X><Y>(equivalent to selectorCoord) */
int save_getStatByCoord(struct save_SavDat *psSave, selectorCoord coord);
void save_writeToStructByCoord(struct save_SavDat *psSave, selectorCoord coord, int data);
resRetTypedef save_structToBuf(struct file_Buffer *psBuf, struct save_SavDat *Src);
resRetTypedef save_bufToStruct(struct file_Buffer *psBuf, struct save_SavDat *Dest);
void save_printLastName(struct file_Buffer *psBuf);
void save_printFirstName(struct file_Buffer *psBuf);
resRetTypedef save_checkVaildity(struct file_Buffer *psBuf);

#endif /* SAVE_H */