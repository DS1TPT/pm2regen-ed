/*
 * File Name: save.c
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

#include "main.h"
#include "offset.h"
#include "save.h"
#include "vt.h"
#include "ui.h"

const char refBytesHiddenStats1[] = { 0x1B, 0xE3, 0x81, 0xA8, 0xE3, 0x81, 0xAB, 0xE3, 0x81, 0x8B, 
                                      0xE3, 0x81, 0x8F, 0xE4, 0xB8, 0x88, 0xE5, 0xA4, 0xAB, 0xE3,
                                      0x81, 0xAA, 0xE5, 0xAD, 0x90, 0xE3, 0x81, 0xAB };
const char refBytesHiddenStats2[] = { 0x18, 0xE3, 0x83, 0x80, 0xE3, 0x82, 0xA4, 0xE3, 0x82, 0xA8, 
                                      0xE3, 0x83, 0x83, 0xE3, 0x83, 0x88, 0xE3, 0x81, 0x95, 0xE3,
                                      0x81, 0x9B, 0xE3, 0x82, 0x8B };
const char refBytesHiddenStats3[] = { 0x18, 0xE3, 0x81, 0x8A, 0xE3, 0x81, 0x97, 0xE3, 0x81, 0xA8, 
                                      0xE3, 0x82, 0x84, 0xE3, 0x81, 0x8B, 0xE3, 0x81, 0xAA, 0xE5,
                                      0xAD, 0x90, 0xE3, 0x81, 0xAB };
const char refBytesHiddenStats4[] = { 0x15, 0xE7, 0x84, 0xA1, 0xE7, 0x90, 0x86, 0xE3, 0x81, 0xAF,
                                      0xE3, 0x81, 0x95, 0xE3, 0x81, 0x9B, 0xE3, 0x81, 0xAA, 0xE3,
                                      0x81, 0x84 };

const char * const parrRefBytesHiddenStats[4] = { refBytesHiddenStats1, refBytesHiddenStats2,
                                                  refBytesHiddenStats3, refBytesHiddenStats4 };

int g_variableOffsetHiddenStats = 0;
int g_variableOffsetPersonalStats = 0;

static void printU16fxp2dp(u16fxp2dp_t fxp)
{
    char sz[7];
    sz[0] = fxp / 10000 + 0x30;
    sz[1] = (fxp % 10000) / 1000 + 0x30;
    sz[2] = (fxp % 1000) / 100 + 0x30;
    sz[3] = '.';
    sz[4] = (fxp % 100) / 10 + 0x30;
    sz[5] = fxp % 10 + 0x30;
    sz[6] = 0;
    printf("%s", sz);
}

void save_printStat(struct save_SavDat *psSave)
{
    vt_cursor(2, CURSOR_OFFSET_LIST_1L);
    printf(Langs[g_lang].stamina);
    vt_cursor(2, CURSOR_OFFSET_LIST_1L + 1);
    printf(Langs[g_lang].strength);
    vt_cursor(2, CURSOR_OFFSET_LIST_1L + 2);
    printf(Langs[g_lang].intelligence);
    vt_cursor(2, CURSOR_OFFSET_LIST_1L + 3);
    printf(Langs[g_lang].refinement);
    vt_cursor(2, CURSOR_OFFSET_LIST_1L + 4);
    printf(Langs[g_lang].glamour);
    vt_cursor(2, CURSOR_OFFSET_LIST_1L + 5);
    printf(Langs[g_lang].morality);
    vt_cursor(2, CURSOR_OFFSET_LIST_1L + 6);
    printf(Langs[g_lang].faith);
    vt_cursor(2, CURSOR_OFFSET_LIST_1L + 7);
    printf(Langs[g_lang].sin);
    vt_cursor(2, CURSOR_OFFSET_LIST_1L + 8);
    printf(Langs[g_lang].sensitivity);
    vt_cursor(2, CURSOR_OFFSET_LIST_1L + 9);
    printf(Langs[g_lang].stress);
    
    vt_cursor(BORDER_VERT_SECOND_X - 4, CURSOR_OFFSET_LIST_1L);
    printf("%03u", psSave->stamina);
    vt_cursor(BORDER_VERT_SECOND_X - 4, CURSOR_OFFSET_LIST_1L + 1);
    printf("%03u", psSave->strength);
    vt_cursor(BORDER_VERT_SECOND_X - 4, CURSOR_OFFSET_LIST_1L + 2);
    printf("%03u", psSave->intelligence);
    vt_cursor(BORDER_VERT_SECOND_X - 4, CURSOR_OFFSET_LIST_1L + 3);
    printf("%03u", psSave->refinement);
    vt_cursor(BORDER_VERT_SECOND_X - 4, CURSOR_OFFSET_LIST_1L + 4);
    printf("%03u", psSave->glamour);
    vt_cursor(BORDER_VERT_SECOND_X - 4, CURSOR_OFFSET_LIST_1L + 5);
    printf("%03u", psSave->morality);
    vt_cursor(BORDER_VERT_SECOND_X - 4, CURSOR_OFFSET_LIST_1L + 6);
    printf("%03u", psSave->faith);
    vt_cursor(BORDER_VERT_SECOND_X - 4, CURSOR_OFFSET_LIST_1L + 7);
    printf("%03u", psSave->sin);
    vt_cursor(BORDER_VERT_SECOND_X - 4, CURSOR_OFFSET_LIST_1L + 8);
    printf("%03u", psSave->sensitivity);
    vt_cursor(BORDER_VERT_SECOND_X - 4, CURSOR_OFFSET_LIST_1L + 9);
    printf("%03u", psSave->stress);

    vt_cursor(2, BORDER_HOR_SECOND_Y + 1);
    printf(Langs[g_lang].money);
    vt_cursor(2, BORDER_HOR_SECOND_Y + 2);
    printf(Langs[g_lang].maternalInstinct);
    vt_cursor(2, BORDER_HOR_SECOND_Y + 3);
    printf(Langs[g_lang].renown);
    vt_cursor(2, BORDER_HOR_SECOND_Y + 4);
    printf(Langs[g_lang].monstersKilled);

    vt_cursor(BORDER_VERT_SECOND_X - 7, BORDER_HOR_SECOND_Y + 1);
    printf("%06d", psSave->money);
    vt_cursor(BORDER_VERT_SECOND_X - 4, BORDER_HOR_SECOND_Y + 2);
    printf("%03u", psSave->maternalInstinct);
    vt_cursor(BORDER_VERT_SECOND_X - 4, BORDER_HOR_SECOND_Y + 3);
    printf("\b%04u", psSave->renown);
    vt_cursor(BORDER_VERT_SECOND_X - 4, BORDER_HOR_SECOND_Y + 4);
    printf("%03u", psSave->monstersKilled);
    
    vt_cursor(BORDER_VERT_SECOND_X + 1, CURSOR_OFFSET_LIST_1M);
    printf(Langs[g_lang].fightReputation);
    vt_cursor(BORDER_VERT_SECOND_X + 1, CURSOR_OFFSET_LIST_1M + 1);
    printf(Langs[g_lang].combatSkill);
    vt_cursor(BORDER_VERT_SECOND_X + 1, CURSOR_OFFSET_LIST_1M + 2);
    printf(Langs[g_lang].attack);
    vt_cursor(BORDER_VERT_SECOND_X + 1, CURSOR_OFFSET_LIST_1M + 3);
    printf(Langs[g_lang].defense);
    
    vt_cursor(BORDER_VERT_SECOND_X + 1, CURSOR_OFFSET_LIST_2M);
    printf(Langs[g_lang].magicReputation);
    vt_cursor(BORDER_VERT_SECOND_X + 1, CURSOR_OFFSET_LIST_2M + 1);
    printf(Langs[g_lang].magicSkill);
    vt_cursor(BORDER_VERT_SECOND_X + 1, CURSOR_OFFSET_LIST_2M + 2);
    printf(Langs[g_lang].magicAttack);
    vt_cursor(BORDER_VERT_SECOND_X + 1, CURSOR_OFFSET_LIST_2M + 3);
    printf(Langs[g_lang].magicDefense);
    
    vt_cursor(BORDER_VERT_THIRD_X - 4, CURSOR_OFFSET_LIST_1M);
    printf("%03u", psSave->fightReputation);
    vt_cursor(BORDER_VERT_THIRD_X - 4, CURSOR_OFFSET_LIST_1M + 1);
    printf("%03u", psSave->combatSkill);
    vt_cursor(BORDER_VERT_THIRD_X - 4, CURSOR_OFFSET_LIST_1M + 2);
    printf("%03u", psSave->attack);
    vt_cursor(BORDER_VERT_THIRD_X - 4, CURSOR_OFFSET_LIST_1M + 3);
    printf("%03u", psSave->defense);
    
    vt_cursor(BORDER_VERT_THIRD_X - 4, CURSOR_OFFSET_LIST_2M);
    printf("%03u", psSave->magicReputation);
    vt_cursor(BORDER_VERT_THIRD_X - 4, CURSOR_OFFSET_LIST_2M + 1);
    printf("%03u", psSave->magicSkill);
    vt_cursor(BORDER_VERT_THIRD_X - 4, CURSOR_OFFSET_LIST_2M + 2);
    printf("%03u", psSave->magicAttack);
    vt_cursor(BORDER_VERT_THIRD_X - 4, CURSOR_OFFSET_LIST_2M + 3);
    printf("%03u", psSave->magicDefense);

    vt_cursor(BORDER_VERT_SECOND_X + 1, BORDER_HOR_SECOND_Y + 1);
    printf(Langs[g_lang].relationshipPrince);
    vt_cursor(BORDER_VERT_SECOND_X + 1, BORDER_HOR_SECOND_Y + 2);
    printf(Langs[g_lang].relationshipFather);
    vt_cursor(BORDER_VERT_SECOND_X + 1, BORDER_HOR_SECOND_Y + 3);
    printf(Langs[g_lang].relationshipButler);

    vt_cursor(BORDER_VERT_THIRD_X - 4, BORDER_HOR_SECOND_Y + 1);
    printf("%03u", psSave->relationshipPrince);
    vt_cursor(BORDER_VERT_THIRD_X - 4, BORDER_HOR_SECOND_Y + 2);
    printf("%03u", psSave->relationshipFather);
    vt_cursor(BORDER_VERT_THIRD_X - 4, BORDER_HOR_SECOND_Y + 3);
    printf("%03u", psSave->relationshipButler);
    
    vt_cursor(BORDER_VERT_THIRD_X + 1, CURSOR_OFFSET_LIST_1R);
    printf(Langs[g_lang].socialReputation);
    vt_cursor(BORDER_VERT_THIRD_X + 1, CURSOR_OFFSET_LIST_1R + 1);
    printf(Langs[g_lang].decorum);
    vt_cursor(BORDER_VERT_THIRD_X + 1, CURSOR_OFFSET_LIST_1R + 2);
    printf(Langs[g_lang].artistry);
    vt_cursor(BORDER_VERT_THIRD_X + 1, CURSOR_OFFSET_LIST_1R + 3);
    printf(Langs[g_lang].eloquence);
    
    vt_cursor(BORDER_WIDTH - 4, CURSOR_OFFSET_LIST_1R);
    printf("%03u", psSave->socialReputation);
    vt_cursor(BORDER_WIDTH - 4, CURSOR_OFFSET_LIST_1R + 1);
    printf("%03u", psSave->decorum);
    vt_cursor(BORDER_WIDTH - 4, CURSOR_OFFSET_LIST_1R + 2);
    printf("%03u", psSave->artistry);
    vt_cursor(BORDER_WIDTH - 4, CURSOR_OFFSET_LIST_1R + 3);
    printf("%03u", psSave->eloquence);
    
    vt_cursor(BORDER_VERT_THIRD_X + 1, CURSOR_OFFSET_LIST_2R);
    printf(Langs[g_lang].houseReputation);
    vt_cursor(BORDER_VERT_THIRD_X + 1, CURSOR_OFFSET_LIST_2R + 1);
    printf(Langs[g_lang].cooking);
    vt_cursor(BORDER_VERT_THIRD_X + 1, CURSOR_OFFSET_LIST_2R + 2);
    printf(Langs[g_lang].cleaning);
    vt_cursor(BORDER_VERT_THIRD_X + 1, CURSOR_OFFSET_LIST_2R + 3);
    printf(Langs[g_lang].temper);
    
    vt_cursor(BORDER_WIDTH - 4, CURSOR_OFFSET_LIST_2R);
    printf("%03u", psSave->houseReputation);
    vt_cursor(BORDER_WIDTH - 4, CURSOR_OFFSET_LIST_2R + 1);
    printf("%03u", psSave->cooking);
    vt_cursor(BORDER_WIDTH - 4, CURSOR_OFFSET_LIST_2R + 2);
    printf("%03u", psSave->cleaning);
    vt_cursor(BORDER_WIDTH - 4, CURSOR_OFFSET_LIST_2R + 3);
    printf("%03u", psSave->temper);

    vt_cursor(BORDER_VERT_THIRD_X + 1, BORDER_HOR_SECOND_Y + 1);
    printf(Langs[g_lang].height);
    vt_cursor(BORDER_VERT_THIRD_X + 1, BORDER_HOR_SECOND_Y + 2);
    printf(Langs[g_lang].weight);
    vt_cursor(BORDER_VERT_THIRD_X + 1, BORDER_HOR_SECOND_Y + 3);
    printf(Langs[g_lang].bust);
    vt_cursor(BORDER_VERT_THIRD_X + 1, BORDER_HOR_SECOND_Y + 4);
    printf(Langs[g_lang].waist);
    vt_cursor(BORDER_VERT_THIRD_X + 1, BORDER_HOR_SECOND_Y + 5);
    printf(Langs[g_lang].hips);

    vt_cursor(BORDER_WIDTH - 7, BORDER_HOR_SECOND_Y + 1);
    printU16fxp2dp(psSave->height);
    vt_cursor(BORDER_WIDTH - 7, BORDER_HOR_SECOND_Y + 2);
    printU16fxp2dp(psSave->weight);
    vt_cursor(BORDER_WIDTH - 7, BORDER_HOR_SECOND_Y + 3);
    printU16fxp2dp(psSave->bust);
    vt_cursor(BORDER_WIDTH - 7, BORDER_HOR_SECOND_Y + 4);
    printU16fxp2dp(psSave->waist);
    vt_cursor(BORDER_WIDTH - 7, BORDER_HOR_SECOND_Y + 5);
    printU16fxp2dp(psSave->hips);
}

void save_highlightStat(struct save_SavDat *psSave, int coord, BOOL isOn) /* coord format: 0x<X><Y>(equivalent to selectorCoord) */
{
    if (coord <= COORD_STRESS) {
        vt_cursor(BORDER_VERT_SECOND_X - 4, CURSOR_OFFSET_LIST_1L + coord);
        if (isOn) {
            printf("\033[7m");
        }
        switch (coord) {
        case COORD_STAMINA:
            printf("%03u\033[0m", psSave->stamina);
            break;
        case COORD_STRENGTH:
            printf("%03u\033[0m", psSave->strength);
            break;
        case COORD_INTELLIGENCE:
            printf("%03u\033[0m", psSave->intelligence);
            break;
        case COORD_REFINEMENT:
            printf("%03u\033[0m", psSave->refinement);
            break;
        case COORD_GLAMOUR:
            printf("%03u\033[0m", psSave->glamour);
            break;
        case COORD_MORALITY:
            printf("%03u\033[0m", psSave->morality);
            break;
        case COORD_FAITH:
            printf("%03u\033[0m", psSave->faith);
            break;
        case COORD_SIN:
            printf("%03u\033[0m", psSave->sin);
            break;
        case COORD_SENSITIVITY:
            printf("%03u\033[0m", psSave->sensitivity);
            break;
        case COORD_STRESS:
            printf("%03u\033[0m", psSave->stress);
            break;
        }
    } else if (COORD_MONEY <= coord && coord <= COORD_MONSTERS_KILLED) {
        vt_cursor(BORDER_VERT_SECOND_X - 4, CURSOR_OFFSET_LIST_2L + coord);
        if (isOn) {
            printf("\033[7m");
        }
        switch (coord) {
        case COORD_MONEY:
            printf("\b\b\b%06d\033[0m", psSave->money);
            break;
        case COORD_MATERNAL_INSTINCT:
            printf("%03u\033[0m", psSave->maternalInstinct);
            break;
        case COORD_RENOWN:
            printf("\b%04u\033[0m", psSave->renown);
            break;
        case COORD_MONSTERS_KILLED:
            printf("%03u\033[0m", psSave->monstersKilled);
            break;
        }
    } else if (COORD_FIGHT_REPUTATION <= coord && coord <= COORD_DEFENSE) {
        vt_cursor(BORDER_VERT_THIRD_X - 4, CURSOR_OFFSET_LIST_1M + coord - 0x10);
        if (isOn) {
            printf("\033[7m");
        }
        switch (coord) {
        case COORD_FIGHT_REPUTATION:
            printf("%03u\033[0m", psSave->fightReputation);
            break;
        case COORD_COMBAT_SKILL:
            printf("%03u\033[0m", psSave->combatSkill);
            break;
        case COORD_ATTACK:
            printf("%03u\033[0m", psSave->attack);
            break;
        case COORD_DEFENSE:
            printf("%03u\033[0m", psSave->defense);
            break;
        }
    } else if (COORD_MAGIC_REPUTATION <= coord && coord <= COORD_MAGIC_DEFENSE) {
        vt_cursor(BORDER_VERT_THIRD_X - 4, CURSOR_OFFSET_LIST_1M + CURSOR_OFFSET_GAP_1_2M + coord - 0x10);
        if (isOn) {
            printf("\033[7m");
        }
        switch (coord) {
        case COORD_MAGIC_REPUTATION:
            printf("%03u\033[0m", psSave->magicReputation);
            break;
        case COORD_MAGIC_SKILL:
            printf("%03u\033[0m", psSave->magicSkill);
            break;
        case COORD_MAGIC_ATTACK:
            printf("%03u\033[0m", psSave->magicAttack);
            break;
        case COORD_MAGIC_DEFENSE:
            printf("%03u\033[0m", psSave->magicDefense);
            break;
        }
    } else if (COORD_RELATIONSHIP_PRINCE <= coord && coord <= COORD_RELATIONSHIP_BUTLER) {
        vt_cursor(BORDER_VERT_THIRD_X - 4, CURSOR_OFFSET_LIST_3M + coord - 0x10);
        if (isOn) {
            printf("\033[7m");
        }
        switch (coord) {
        case COORD_RELATIONSHIP_PRINCE:
            printf("%03u\033[0m", psSave->relationshipPrince);
            break;
        case COORD_RELATIONSHIP_FATHER:
            printf("%03u\033[0m", psSave->relationshipFather);
            break;
        case COORD_RELATIONSHIP_BUTLER:
            printf("%03u\033[0m", psSave->relationshipButler);
            break;
        }
    } else if (COORD_SOCIAL_REPUTATION <= coord && coord <= COORD_ELOQUENCE) {
        vt_cursor(BORDER_WIDTH - 4, CURSOR_OFFSET_LIST_1R + coord - 0x20);
        if (isOn) {
            printf("\033[7m");
        }
        switch (coord) {
        case COORD_SOCIAL_REPUTATION:
            printf("%03u\033[0m", psSave->socialReputation);
            break;
        case COORD_DECORUM:
            printf("%03u\033[0m", psSave->decorum);
            break;
        case COORD_ARTISTRY:
            printf("%03u\033[0m", psSave->artistry);
            break;
        case COORD_ELOQUENCE:
            printf("%03u\033[0m", psSave->eloquence);
            break;
        }
    } else if (COORD_HOUSEWORK_REPUTATION <= coord && coord <= COORD_TEMPER) {
        vt_cursor(BORDER_WIDTH - 4, CURSOR_OFFSET_LIST_1R + CURSOR_OFFSET_GAP_1_2R + coord - 0x20);
        if (isOn) {
            printf("\033[7m");
        }
        switch (coord) {
        case COORD_HOUSEWORK_REPUTATION:
            printf("%03u\033[0m", psSave->houseReputation);
            break;
        case COORD_COOKING:
            printf("%03u\033[0m", psSave->cooking);
            break;
        case COORD_CLEANING:
            printf("%03u\033[0m", psSave->cleaning);
            break;
        case COORD_TEMPER:
            printf("%03u\033[0m", psSave->temper);
            break;
        }
    } else if (COORD_HEIGHT <= coord && coord <= COORD_HIPS) {
        vt_cursor(BORDER_WIDTH - 7, CURSOR_OFFSET_LIST_3R + coord - 0x20);
        if (isOn) {
            printf("\033[7m");
        }
        switch (coord) {
        case COORD_HEIGHT:
            printU16fxp2dp(psSave->height);
            break;
        case COORD_WEIGHT:
            printU16fxp2dp(psSave->weight);
            break;
        case COORD_BUST:
            printU16fxp2dp(psSave->bust);
            break;
        case COORD_WAIST:
            printU16fxp2dp(psSave->waist);
            break;
        case COORD_HIPS:
            printU16fxp2dp(psSave->hips);
            break;
        }
        printf("\033[0m");
    }
}

int save_getStatByCoord(struct save_SavDat *psSave, selectorCoord coord)
{
    switch (coord) {
    case COORD_STAMINA:
        return psSave->stamina;
    case COORD_STRENGTH:
        return psSave->strength;
    case COORD_INTELLIGENCE:
        return psSave->intelligence;
    case COORD_REFINEMENT:
        return psSave->refinement;
    case COORD_GLAMOUR:
        return psSave->glamour;
    case COORD_MORALITY:
        return psSave->morality;
    case COORD_FAITH:
        return psSave->faith;
    case COORD_SIN:
        return psSave->sin;
    case COORD_SENSITIVITY:
        return psSave->sensitivity;
    case COORD_STRESS:
        return psSave->stress;

    case COORD_MONEY:
        return psSave->money;
    case COORD_MATERNAL_INSTINCT:
        return psSave->maternalInstinct;
    case COORD_RENOWN:
        return psSave->renown;
    case COORD_MONSTERS_KILLED:
        return psSave->monstersKilled;

    case COORD_FIGHT_REPUTATION:
        return psSave->fightReputation;
    case COORD_MAGIC_REPUTATION:
        return psSave->magicReputation;
    case COORD_SOCIAL_REPUTATION:
        return psSave->socialReputation;
    case COORD_HOUSEWORK_REPUTATION:
        return psSave->houseReputation;

    case COORD_COMBAT_SKILL:
        return psSave->combatSkill;
    case COORD_ATTACK:
        return psSave->attack;
    case COORD_DEFENSE:
        return psSave->defense;

    case COORD_MAGIC_SKILL:
        return psSave->magicSkill;
    case COORD_MAGIC_ATTACK:
        return psSave->magicAttack;
    case COORD_MAGIC_DEFENSE:
        return psSave->magicDefense;

    case COORD_DECORUM:
        return psSave->decorum;
    case COORD_ARTISTRY:
        return psSave->artistry;
    case COORD_ELOQUENCE:
        return psSave->eloquence;

    case COORD_COOKING:
        return psSave->cooking;
    case COORD_CLEANING:
        return psSave->cleaning;
    case COORD_TEMPER:
        return psSave->temper;

    case COORD_RELATIONSHIP_PRINCE:
        return psSave->relationshipPrince;
    case COORD_RELATIONSHIP_FATHER:
        return psSave->relationshipFather;
    case COORD_RELATIONSHIP_BUTLER:
        return psSave->relationshipButler;

    case COORD_HEIGHT:
        return psSave->height;
    case COORD_WEIGHT:
        return psSave->weight;
    case COORD_BUST:
        return psSave->bust;
    case COORD_WAIST:
        return psSave->waist;
    case COORD_HIPS:
        return psSave->hips;
    }
    return 0; /* this line is written just to avoid compiler warning and will not be executed */
}

void save_writeToStructByCoord(struct save_SavDat *psSave, selectorCoord coord, int *pData)
{
    int data = *pData;

    if (COORD_RELATIONSHIP_PRINCE <= coord && coord <= COORD_RELATIONSHIP_BUTLER) {
        if (data > RELATIONSHIP_MAX) {
            data = RELATIONSHIP_MAX;
            ui_editorPrintHint(EDITOR_HINT_INT_MAXVAL, RELATIONSHIP_MAX);
        }
    } else if (coord == COORD_MATERNAL_INSTINCT) {
        if (data > MATERNAL_INSTINCT_MAX) {
            data = MATERNAL_INSTINCT_MAX;
            ui_editorPrintHint(EDITOR_HINT_INT_MAXVAL, MATERNAL_INSTINCT_MAX);
        }
    } else if (coord == COORD_RENOWN) {
        if (data > 1000) {
            data = 1000;
            ui_editorPrintHint(EDITOR_HINT_INT_MAXVAL, 1000);
        }
    } else if (coord == COORD_HEIGHT) {
        if (data < HEIGHT_MIN) {
            data = HEIGHT_MIN;
            ui_editorPrintHint(EDITOR_HINT_FXP_MINVAL, HEIGHT_MIN);
        } else if (data > HEIGHT_MAX) {
            data = HEIGHT_MAX;
            ui_editorPrintHint(EDITOR_HINT_FXP_MAXVAL, HEIGHT_MAX);
        }
    } else if (coord == COORD_WEIGHT) {
        if (data < WEIGHT_MIN) {
            data = WEIGHT_MIN;
            ui_editorPrintHint(EDITOR_HINT_FXP_MINVAL, WEIGHT_MIN);
        } else if (data > WEIGHT_MAX) {
            data = WEIGHT_MAX;
            ui_editorPrintHint(EDITOR_HINT_FXP_MAXVAL, WEIGHT_MAX);
        }
    } else if (COORD_BUST <= coord && coord <= COORD_HIPS) {
        if (data < BWH_MIN) {
            data = BWH_MIN;
            ui_editorPrintHint(EDITOR_HINT_FXP_MINVAL, BWH_MIN);
        } else if (data > BWH_MAX) {
            data = BWH_MAX;
            ui_editorPrintHint(EDITOR_HINT_FXP_MAXVAL, BWH_MAX);
        }
    }

    switch (coord) {
    case COORD_STAMINA:
        psSave->stamina = data;
        break;
    case COORD_STRENGTH:
        psSave->strength = data;
        break;
    case COORD_INTELLIGENCE:
        psSave->intelligence = data;
        break;
    case COORD_REFINEMENT:
        psSave->refinement = data;
        break;
    case COORD_GLAMOUR:
        psSave->glamour = data;
        break;
    case COORD_MORALITY:
        psSave->morality = data;
        break;
    case COORD_FAITH:
        psSave->faith = data;
        break;
    case COORD_SIN:
        psSave->sin = data;
        break;
    case COORD_SENSITIVITY:
        psSave->sensitivity = data;
        break;
    case COORD_STRESS:
        psSave->stress = data;
        break;

    case COORD_MONEY:
        psSave->money = data;
        break;
    case COORD_MATERNAL_INSTINCT:
        psSave->maternalInstinct = data;
        break;
    case COORD_RENOWN:
        psSave->renown = data;
        break;
    case COORD_MONSTERS_KILLED:
        psSave->monstersKilled = data;
        break;

    case COORD_FIGHT_REPUTATION:
        psSave->fightReputation = data;
        break;
    case COORD_MAGIC_REPUTATION:
        psSave->magicReputation = data;
        break;
    case COORD_SOCIAL_REPUTATION:
        psSave->socialReputation = data;
        break;
    case COORD_HOUSEWORK_REPUTATION:
        psSave->houseReputation = data;
        break;

    case COORD_COMBAT_SKILL:
        psSave->combatSkill = data;
        break;
    case COORD_ATTACK:
        psSave->attack = data;
        break;
    case COORD_DEFENSE:
        psSave->defense = data;
        break;

    case COORD_MAGIC_SKILL:
        psSave->magicSkill = data;
        break;
    case COORD_MAGIC_ATTACK:
        psSave->magicAttack = data;
        break;
    case COORD_MAGIC_DEFENSE:
        psSave->magicDefense = data;
        break;

    case COORD_DECORUM:
        psSave->decorum = data;
        break;
    case COORD_ARTISTRY:
        psSave->artistry = data;
        break;
    case COORD_ELOQUENCE:
        psSave->eloquence = data;
        break;

    case COORD_COOKING:
        psSave->cooking = data;
        break;
    case COORD_CLEANING:
        psSave->cleaning = data;
        break;
    case COORD_TEMPER:
        psSave->temper = data;
        break;

    case COORD_RELATIONSHIP_PRINCE:
        psSave->relationshipPrince = data;
        break;
    case COORD_RELATIONSHIP_FATHER:
        psSave->relationshipFather = data;
        break;
    case COORD_RELATIONSHIP_BUTLER:
        psSave->relationshipButler = data;
        break;

    case COORD_HEIGHT:
        psSave->height = data;
        break;
    case COORD_WEIGHT:
        psSave->weight = data;
        break;
    case COORD_BUST:
        psSave->bust = data;
        break;
    case COORD_WAIST:
        psSave->waist = data;
        break;
    case COORD_HIPS:
        psSave->hips = data;
        break;
    }
}

resRetTypedef save_structToBuf(struct file_Buffer *psBuf, struct save_SavDat *Src) /* write edited structure to buffer */
{
    if (psBuf->data == NULL || g_variableOffsetHiddenStats == 0 || g_variableOffsetPersonalStats == 0) {
        return FAIL_MEMORY;
    }

    *((uint16_t*)(psBuf->data + OFFSET_STAMINA)) = Src->stamina;
    *((uint16_t*)(psBuf->data + OFFSET_STRENGTH)) = Src->strength;
    *((uint16_t*)(psBuf->data + OFFSET_INTELLIGENCE)) = Src->intelligence;
    *((uint16_t*)(psBuf->data + OFFSET_REFINEMENT)) = Src->refinement;
    *((uint16_t*)(psBuf->data + OFFSET_GLAMOUR)) = Src->glamour;
    *((uint16_t*)(psBuf->data + OFFSET_MORALITY)) = Src->morality;
    *((uint16_t*)(psBuf->data + OFFSET_FAITH)) = Src->faith;
    *((uint16_t*)(psBuf->data + OFFSET_SIN)) = Src->sin;
    *((uint16_t*)(psBuf->data + OFFSET_SENSITIVITY)) = Src->sensitivity;
    *((uint16_t*)(psBuf->data + OFFSET_STRESS)) = Src->stress;

    *((uint16_t*)(psBuf->data + OFFSET_FIGHT_REP)) = Src->fightReputation;
    *((uint16_t*)(psBuf->data + OFFSET_MAGIC_REP)) = Src->magicReputation;
    *((uint16_t*)(psBuf->data + OFFSET_SOCIAL_REP)) = Src->socialReputation;
    *((uint16_t*)(psBuf->data + OFFSET_HOUSE_REP)) = Src->houseReputation;

    *((uint16_t*)(psBuf->data + OFFSET_COMBAT_SKILL)) = Src->combatSkill;
    *((uint16_t*)(psBuf->data + OFFSET_ATTACK)) = Src->attack;
    *((uint16_t*)(psBuf->data + OFFSET_DEFENSE)) = Src->defense;

    *((uint16_t*)(psBuf->data + OFFSET_MAGIC_SKILL)) = Src->magicSkill;
    *((uint16_t*)(psBuf->data + OFFSET_MAGIC_ATTACK)) = Src->magicAttack;
    *((uint16_t*)(psBuf->data + OFFSET_MAGIC_DEFENSE)) = Src->magicDefense;

    *((uint16_t*)(psBuf->data + OFFSET_DECORUM)) = Src->decorum;
    *((uint16_t*)(psBuf->data + OFFSET_ARTISTRY)) = Src->artistry;
    *((uint16_t*)(psBuf->data + OFFSET_ELOQUENCE)) = Src->eloquence;

    *((uint16_t*)(psBuf->data + OFFSET_COOKING)) = Src->cooking;
    *((uint16_t*)(psBuf->data + OFFSET_CLEANING)) = Src->cleaning;
    *((uint16_t*)(psBuf->data + OFFSET_TEMPER)) = Src->temper;

    *((int32_t*)(psBuf->data + OFFSET_MONEY)) = Src->money;

    *((u16fxp2dp_t*)(psBuf->data + g_variableOffsetPersonalStats + OFFSET_PATTERN_HEIGHT)) = Src->height;
    *((u16fxp2dp_t*)(psBuf->data + g_variableOffsetPersonalStats + OFFSET_PATTERN_WEIGHT)) = Src->weight;
    *((u16fxp2dp_t*)(psBuf->data + g_variableOffsetPersonalStats + OFFSET_PATTERN_BUST)) = Src->bust;
    *((u16fxp2dp_t*)(psBuf->data + g_variableOffsetPersonalStats + OFFSET_PATTERN_WAIST)) = Src->waist;
    *((u16fxp2dp_t*)(psBuf->data + g_variableOffsetPersonalStats + OFFSET_PATTERN_HIPS)) = Src->hips;
    *((uint16_t*)(psBuf->data + g_variableOffsetPersonalStats + OFFSET_PATTERN_RENOWN)) = Src->renown;

    *((uint16_t*)(psBuf->data + g_variableOffsetHiddenStats + OFFSET_PATTERN_R_PRINCE)) = Src->relationshipPrince;
    *((uint16_t*)(psBuf->data + g_variableOffsetHiddenStats + OFFSET_PATTERN_R_FATHER)) = Src->relationshipFather;
    *((uint16_t*)(psBuf->data + g_variableOffsetHiddenStats + OFFSET_PATTERN_R_BUTLER)) = Src->relationshipButler;
    *((uint16_t*)(psBuf->data + g_variableOffsetHiddenStats + OFFSET_PATTERN_MATERNAL_INSTINCT)) = Src->maternalInstinct;
    *((uint16_t*)(psBuf->data + g_variableOffsetHiddenStats + OFFSET_PATTERN_MONSTERS_KILLED)) = Src->monstersKilled;

    return SUCCESS;
}

static resRetTypedef getVariableOffset(struct file_Buffer *psBuf)
{
    if (psBuf->data == NULL) {
        return FAIL_MEMORY;
    }
    int refPos = 0;
    int i = 0;
    while (1) {
        if (refPos + OFFSET_HID_TO_REF + sizeof(uint16_t) * 6 >= psBuf->size && i == 3) {
            return FAIL_INVALID_FILE;
        } else if (refPos + OFFSET_HID_TO_REF + sizeof(uint16_t) * 6 >= psBuf->size && i < 3) {
            refPos = 0;
            i++;
        } else if (memcmp((psBuf->data + refPos), parrRefBytesHiddenStats[i], sizeof(parrRefBytesHiddenStats[i])) == 0) {
            break;
        } else {
            refPos++;
        }
    }
    g_variableOffsetHiddenStats = refPos - OFFSET_HID_TO_REF;

    refPos = OFFSET_NAME_START;
    refPos += *(psBuf->data + refPos) + 1; /* next length descriptor */
    refPos += *(psBuf->data + refPos); /* goto last byte of last name */
    refPos += OFFSET_PERSONAL_FROM_REF;
    g_variableOffsetPersonalStats = refPos;

    return SUCCESS;
}

resRetTypedef save_bufToStruct(struct file_Buffer *psBuf, struct save_SavDat *Dest)
{
    if (psBuf->data == NULL) {
        return FAIL_MEMORY;
    }
    resRetTypedef ret = getVariableOffset(psBuf);
    if (ret) {
        return ret;
    }

    Dest->stamina = *((uint16_t*)(psBuf->data + OFFSET_STAMINA));
    Dest->strength = *((uint16_t*)(psBuf->data + OFFSET_STRENGTH));
    Dest->intelligence = *((uint16_t*)(psBuf->data + OFFSET_INTELLIGENCE));
    Dest->refinement = *((uint16_t*)(psBuf->data + OFFSET_REFINEMENT));
    Dest->glamour = *((uint16_t*)(psBuf->data + OFFSET_GLAMOUR));
    Dest->morality = *((uint16_t*)(psBuf->data + OFFSET_MORALITY));
    Dest->faith = *((uint16_t*)(psBuf->data + OFFSET_FAITH));
    Dest->sin = *((uint16_t*)(psBuf->data + OFFSET_SIN));
    Dest->sensitivity = *((uint16_t*)(psBuf->data + OFFSET_SENSITIVITY));
    Dest->stress = *((uint16_t*)(psBuf->data + OFFSET_STRESS));

    Dest->fightReputation = *((uint16_t*)(psBuf->data + OFFSET_FIGHT_REP));
    Dest->magicReputation = *((uint16_t*)(psBuf->data + OFFSET_MAGIC_REP));
    Dest->socialReputation = *((uint16_t*)(psBuf->data + OFFSET_SOCIAL_REP));
    Dest->houseReputation = *((uint16_t*)(psBuf->data + OFFSET_HOUSE_REP));
    
    Dest->combatSkill = *((uint16_t*)(psBuf->data + OFFSET_COMBAT_SKILL));
    Dest->attack = *((uint16_t*)(psBuf->data + OFFSET_ATTACK));
    Dest->defense = *((uint16_t*)(psBuf->data + OFFSET_DEFENSE));
    
    Dest->magicSkill = *((uint16_t*)(psBuf->data + OFFSET_MAGIC_SKILL));
    Dest->magicAttack = *((uint16_t*)(psBuf->data + OFFSET_MAGIC_ATTACK));
    Dest->magicDefense = *((uint16_t*)(psBuf->data + OFFSET_MAGIC_DEFENSE));
    
    Dest->decorum = *((uint16_t*)(psBuf->data + OFFSET_DECORUM));
    Dest->artistry = *((uint16_t*)(psBuf->data + OFFSET_ARTISTRY));
    Dest->eloquence = *((uint16_t*)(psBuf->data + OFFSET_ELOQUENCE));

    Dest->cooking = *((uint16_t*)(psBuf->data + OFFSET_COOKING));
    Dest->cleaning = *((uint16_t*)(psBuf->data + OFFSET_CLEANING));
    Dest->temper = *((uint16_t*)(psBuf->data + OFFSET_TEMPER));

    Dest->money = *((int32_t*)(psBuf->data + OFFSET_MONEY));

    Dest->height = *((u16fxp2dp_t*)(psBuf->data + g_variableOffsetPersonalStats + OFFSET_PATTERN_HEIGHT));
    Dest->weight = *((u16fxp2dp_t*)(psBuf->data + g_variableOffsetPersonalStats + OFFSET_PATTERN_WEIGHT));
    Dest->bust = *((u16fxp2dp_t*)(psBuf->data + g_variableOffsetPersonalStats + OFFSET_PATTERN_BUST));
    Dest->waist = *((u16fxp2dp_t*)(psBuf->data + g_variableOffsetPersonalStats + OFFSET_PATTERN_WAIST));
    Dest->hips = *((u16fxp2dp_t*)(psBuf->data + g_variableOffsetPersonalStats + OFFSET_PATTERN_HIPS));
    Dest->renown = *((uint16_t*)(psBuf->data + g_variableOffsetPersonalStats + OFFSET_PATTERN_RENOWN));


    Dest->relationshipPrince = *((uint16_t*)(psBuf->data + g_variableOffsetHiddenStats + OFFSET_PATTERN_R_PRINCE));
    Dest->relationshipFather = *((uint16_t*)(psBuf->data + g_variableOffsetHiddenStats + OFFSET_PATTERN_R_FATHER));
    Dest->relationshipButler = *((uint16_t*)(psBuf->data + g_variableOffsetHiddenStats + OFFSET_PATTERN_R_BUTLER));
    Dest->maternalInstinct = *((uint16_t*)(psBuf->data + g_variableOffsetHiddenStats + OFFSET_PATTERN_MATERNAL_INSTINCT));
    Dest->monstersKilled = *((uint16_t*)(psBuf->data + g_variableOffsetHiddenStats + OFFSET_PATTERN_MONSTERS_KILLED));

    return SUCCESS;
}

void save_printLastName(struct file_Buffer *psBuf)
{
    char *p = (psBuf->data + OFFSET_NAME_START);
    p += (*p + 1);
    int len = *p++;
    for (len; len > 0; len--) {
        printf("%c", *p++);
    }
}

void save_printFirstName(struct file_Buffer *psBuf)
{
    char *p = (psBuf->data + OFFSET_NAME_START);
    int len = *p++;
    for (len; len > 0; len--) {
        printf("%c", *p++);
    }
}

void save_printDate(struct file_Buffer *psBuf)
{
    printf("%04u/%02u/%02u     ", *(uint16_t*)(psBuf->data + OFFSET_YEAR), *(uint16_t*)(psBuf->data + OFFSET_MONTH), *(uint16_t*)(psBuf->data + OFFSET_DAY)); 
}


resRetTypedef save_checkVaildity(struct file_Buffer *psBuf)
{
    int refPos = 0;
    int i = 0;
    if (psBuf->size < SAVE_SIZE_MIN) {
        return FAIL_FILESIZE;
    }
    if (psBuf->data == NULL) {
        return FAIL_MEMORY;
    }
    while (1) {
        if (refPos + OFFSET_HID_TO_REF + sizeof(uint16_t) * 6 >= psBuf->size && i == 3) {
            return FAIL_INVALID_FILE;
        } else if (refPos + OFFSET_HID_TO_REF + sizeof(uint16_t) * 6 >= psBuf->size && i < 3) {
            refPos = 0;
            i++;
        } else if (memcmp((psBuf->data + refPos), parrRefBytesHiddenStats[i], sizeof(parrRefBytesHiddenStats[i])) == 0) {
            break;
        } else {
            refPos++;
        }
    }
    char *p = (psBuf->data + OFFSET_NAME_START);
    if (*p > NAME_MAX_BYTES || *(p + (*p + 1)) > NAME_MAX_BYTES) {
        return FAIL_INVALID_FILE;
    }
    return SUCCESS;
}