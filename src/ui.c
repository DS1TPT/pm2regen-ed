/*
 * File Name: ui.c
 * Description: tiny tui for pm2regen-ed
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

#include "ui.h"
#include "vt.h"

static void popup_drawBorder(popupTypedef type, unsigned sizeX, unsigned sizeY) /* helper function for ui_popup */
{
    vt_cursor(BORDER_WIDTH / 2 - sizeX / 2, BORDER_HEIGHT / 2 - sizeY / 2);
    printf("┏");
    for (int i = 0; i < sizeX - 2; i++) {
        printf("━");
    }
    printf("┓");
    for (int i = 0; i < sizeY - 1; i++) {
        vt_cursor(BORDER_WIDTH / 2 - sizeX / 2, BORDER_HEIGHT / 2 - sizeY / 2 + 1 + i);
        printf("┃");
        for (int j = 0; j < sizeX - 2; j++) {
            printf(" ");
        }
        printf("┃");
    }
    vt_cursor(BORDER_WIDTH / 2 - sizeX / 2, BORDER_HEIGHT / 2 + sizeY / 2);
    printf("┗");
    for (int i = 0; i < sizeX - 2; i++) {
        printf("━");
    }
    printf("┛");    

    switch (type) {
    case POPUP_OK:
        vt_cursor(BORDER_WIDTH / 2 - 3, BORDER_HEIGHT / 2 + sizeY / 2 - 3);
        printf("┌────┐");
        vt_cursor(BORDER_WIDTH / 2 - 3, BORDER_HEIGHT / 2 + sizeY / 2 - 2);
        printf(Langs[g_lang].popupOk);
        vt_cursor(BORDER_WIDTH / 2 - 3, BORDER_HEIGHT / 2 + sizeY / 2 - 1);
        printf("└────┘");
        break;
    case POPUP_YN:
        vt_cursor(BORDER_WIDTH / 2 - 9, BORDER_HEIGHT / 2 + sizeY / 2 - 3);
        printf("┌─────┐  ┌──────┐");
        vt_cursor(BORDER_WIDTH / 2 - 9, BORDER_HEIGHT / 2 + sizeY / 2 - 1);
        printf("└─────┘  └──────┘");
        break;
    }
}

int ui_popup(popupTypedef type, unsigned sizeX, unsigned sizeY, const char *msg, BOOL isDefaultYes)
{	
    popup_drawBorder(type, sizeX, sizeY);

    if (g_lang == LANG_EN) {
        vt_cursor(BORDER_WIDTH / 2 - strlen(msg) / 2, BORDER_HEIGHT / 2 - 1);
    } else {
        vt_cursor(BORDER_WIDTH / 2 - strlen(msg) / 3, BORDER_HEIGHT / 2 - 1);
    }
    printf("%s", msg);

    switch (type) {
    case POPUP_OK:
        while(1) {
            int ch = vt_getKeypress();
            if (ch == KEY_CR || ch == KEY_LF || ch == ' ') {
                break;
            }
        }
        return 0;
        break;
    case POPUP_YN:
        BOOL isYes = isDefaultYes;
        vt_cursor(BORDER_WIDTH / 2 - 9, BORDER_HEIGHT / 2 + sizeY / 2 - 2);
        if (isDefaultYes) {
            printf(Langs[g_lang].popupYN_Y);
        } else {
            printf(Langs[g_lang].popupYN_N);
        }

        while(1) {
            int ch = vt_getKeypress();
            if (ch == KEY_CR || ch == KEY_LF || ch == ' ') {
                break;
            } else if (isYes && ch == KEY_RIGHT) {
                vt_cursor(BORDER_WIDTH / 2 - 9, BORDER_HEIGHT / 2 + sizeY / 2 - 2);
                printf(Langs[g_lang].popupYN_N);
                isYes = FALSE;
            } else if (!isYes && ch == KEY_LEFT) {
                vt_cursor(BORDER_WIDTH / 2 - 9, BORDER_HEIGHT / 2 + sizeY / 2 - 2);
                printf(Langs[g_lang].popupYN_Y);
                isYes = TRUE;
            }
        }
        return isYes;
        break;
    default:
        /* undefined call */
        return -1;
        break;
    }
}

void ui_editorDrawBorder()
{
    vt_clearScreen();
    vt_cursor(1,1);
    printf("┏");
    vt_cursor(2,1);
    for (int i = 2; i < BORDER_WIDTH; i++) {
        if (i == BORDER_VERT_SECOND_X || i == BORDER_VERT_THIRD_X) {
            printf("┯");
        } else {
            printf("━");
        }
    }
    vt_cursor(BORDER_WIDTH, 1);
    printf("┓");
    for (int i = 2; i < BORDER_HEIGHT; i++) {
        if (i == BORDER_HOR_SECOND_Y || i == BORDER_HOR_THIRD_Y) {
            vt_cursor(1, i);
            printf("┣");
            for (int j = 2; j < BORDER_WIDTH; j++) {
                if (j == BORDER_VERT_SECOND_X || j == BORDER_VERT_THIRD_X) {
                    if (i < BORDER_HOR_THIRD_Y) {
                        printf("┼");
                    } else { 
                        printf("┴");
                    }
                } else {
                    printf("─");
                }
            }
            vt_cursor(BORDER_WIDTH, i);
            printf("┫");
        } else {
            vt_cursor(1, i);
            printf("┃");
            if (i < BORDER_HOR_THIRD_Y) {
                vt_cursor(BORDER_VERT_SECOND_X, i);
                printf("│");
                vt_cursor(BORDER_VERT_THIRD_X, i);
                printf("│");
            }
            vt_cursor(BORDER_WIDTH, i);
            printf("┃");
        }
    }
    vt_cursor(1, BORDER_HEIGHT);
    printf("┗");
    for (int i = 2; i < BORDER_WIDTH; i++) {
        printf("━");
    }
    printf("┛");
}

void ui_editorPrintGuide(ui_editorModeTypedef mode)
{
    if (mode == EDITOR_MODE_SEL) {
        vt_cursor(2, BORDER_HOR_THIRD_Y + 1);
        printf(Langs[g_lang].guideNav);
    } else if (mode == EDITOR_MODE_EDIT) {
        vt_cursor(2, BORDER_HOR_THIRD_Y + 1);
        printf(Langs[g_lang].guideEdit);
    }
}

ui_editorCmdTypedef ui_editorSel(struct save_SavDat *psSave, int *pSelCoord)
{
    while (1) {
        int key = vt_getKeypress();
        if (key == KEY_UP && (*pSelCoord & 0x0f)) {
            save_highlightStat(psSave, *pSelCoord, FALSE);
            save_highlightStat(psSave, --*pSelCoord, TRUE);
        } else if (key == KEY_DOWN) {
            if (0x20 <= *pSelCoord && *pSelCoord < COORD_HIPS) {
                save_highlightStat(psSave, *pSelCoord, FALSE);
                save_highlightStat(psSave, ++*pSelCoord, TRUE);
            } else if (0x10 <= *pSelCoord && *pSelCoord < 0x20 && *pSelCoord < COORD_RELATIONSHIP_BUTLER) {
                save_highlightStat(psSave, *pSelCoord, FALSE);
                save_highlightStat(psSave, ++*pSelCoord, TRUE);
            } else if (*pSelCoord < 0x10 && *pSelCoord < COORD_MONSTERS_KILLED) {
                save_highlightStat(psSave, *pSelCoord, FALSE);
                save_highlightStat(psSave, ++*pSelCoord, TRUE);
            } else {
                printf("\a");
            }
        } else if (key == KEY_RIGHT && *pSelCoord < 0x20) {
            save_highlightStat(psSave, *pSelCoord, FALSE);
            if (*pSelCoord < 0x10) {
                if (*pSelCoord < COORD_GLAMOUR) {
                    *pSelCoord += 0x10;
                } else if (*pSelCoord == COORD_GLAMOUR) {
                    *pSelCoord = COORD_MAGIC_REPUTATION;
                } else if (COORD_MORALITY <= *pSelCoord && *pSelCoord <= COORD_SENSITIVITY) {
                    *pSelCoord += 0x0f;
                } else if (*pSelCoord == COORD_STRESS) {
                    *pSelCoord = COORD_MAGIC_DEFENSE;
                } else if (COORD_MONEY <= *pSelCoord && *pSelCoord <= COORD_RENOWN) {
                    *pSelCoord += 0x0e;
                } else if (*pSelCoord == COORD_MONSTERS_KILLED) {
                    *pSelCoord = COORD_RELATIONSHIP_BUTLER;
                }
            } else {
                *pSelCoord += 0x10;
            }
            save_highlightStat(psSave, *pSelCoord, TRUE);
        } else if (key == KEY_LEFT && *pSelCoord >= 0x10) {
            save_highlightStat(psSave, *pSelCoord, FALSE);
            if (0x10 <= *pSelCoord && *pSelCoord < 0x20) {
                if (*pSelCoord <= COORD_DEFENSE) {
                    *pSelCoord -= 0x10;
                } else if (COORD_MAGIC_REPUTATION <= *pSelCoord && *pSelCoord <= COORD_MAGIC_DEFENSE) {
                    *pSelCoord -= 0x0f;
                } else if (COORD_RELATIONSHIP_PRINCE <= *pSelCoord && *pSelCoord <= COORD_RELATIONSHIP_BUTLER) {
                    *pSelCoord -= 0x0e;
                }
            } else if (*pSelCoord >= COORD_BUST) {
                *pSelCoord = COORD_RELATIONSHIP_BUTLER;
            } else {
                *pSelCoord -= 0x10;
            }
            save_highlightStat(psSave, *pSelCoord, TRUE);
        } else if (key == 's' || key == 'S') {
            int popupRet = ui_popup(POPUP_YN, BORDER_WIDTH / 3 * 2, BORDER_HEIGHT / 2, Langs[g_lang].askSave, FALSE);
            if (popupRet == FALSE) {
                ui_editorDrawBorder();
                ui_editorPrintGuide(EDITOR_MODE_SEL);
                save_printStat(psSave);
                save_highlightStat(psSave, *pSelCoord, TRUE);
                continue;
            } else {
                return EDITOR_CMD_SAVE;
            }
        } else if (key == 'q' || key == 'Q') {
            int popupRet = ui_popup(POPUP_YN, BORDER_WIDTH / 3 * 2, BORDER_HEIGHT / 2, Langs[g_lang].askDiscard, FALSE);
            if (popupRet == FALSE) {
                ui_editorDrawBorder();
                ui_editorPrintGuide(EDITOR_MODE_SEL);
                save_printStat(psSave);
                save_highlightStat(psSave, *pSelCoord, TRUE);
                continue;
            } else {
                return EDITOR_CMD_QUIT;
            }
        } else if (key == KEY_CR || key == KEY_LF || key == ' ') {
            return EDITOR_CMD_EDIT;
        } else {
            printf("\a");
        }
    }
}

static void editorEdSetCursor(int *pSelCoord)
{
    if (COORD_STAMINA <= *pSelCoord && *pSelCoord <= COORD_STRESS) {
        vt_cursor(BORDER_VERT_SECOND_X - 4, CURSOR_OFFSET_LIST_1L + *pSelCoord);
    } else if (*pSelCoord == COORD_MONEY) {
        vt_cursor(BORDER_VERT_SECOND_X - 7, CURSOR_OFFSET_LIST_2L + *pSelCoord);
    } else if (COORD_MATERNAL_INSTINCT <= *pSelCoord && *pSelCoord <= COORD_MONSTERS_KILLED) {
        if (*pSelCoord == COORD_RENOWN) {
            vt_cursor(BORDER_VERT_SECOND_X - 5, CURSOR_OFFSET_LIST_2L + *pSelCoord);
        } else {
            vt_cursor(BORDER_VERT_SECOND_X - 4, CURSOR_OFFSET_LIST_2L + *pSelCoord);
        }
    } else if (COORD_FIGHT_REPUTATION <= *pSelCoord && *pSelCoord <= COORD_DEFENSE) {
        vt_cursor(BORDER_VERT_THIRD_X - 4, CURSOR_OFFSET_LIST_1M + *pSelCoord - 0x10);
    } else if (COORD_MAGIC_REPUTATION <= *pSelCoord && *pSelCoord <= COORD_MAGIC_DEFENSE) {
        vt_cursor(BORDER_VERT_THIRD_X - 4, CURSOR_OFFSET_LIST_1M + CURSOR_OFFSET_GAP_1_2M + *pSelCoord - 0x10);
    } else if (COORD_RELATIONSHIP_PRINCE <= *pSelCoord && *pSelCoord <= COORD_RELATIONSHIP_BUTLER) {
        vt_cursor(BORDER_VERT_THIRD_X - 4, CURSOR_OFFSET_LIST_3M + *pSelCoord - 0x10);
    } else if (COORD_SOCIAL_REPUTATION <= *pSelCoord && *pSelCoord <= COORD_ELOQUENCE) {
        vt_cursor(BORDER_WIDTH - 4, CURSOR_OFFSET_LIST_1R + *pSelCoord - 0x20);
    } else if (COORD_HOUSEWORK_REPUTATION <= *pSelCoord && *pSelCoord <= COORD_TEMPER) {
        vt_cursor(BORDER_WIDTH - 4, CURSOR_OFFSET_LIST_1R + CURSOR_OFFSET_GAP_1_2R + *pSelCoord - 0x20);
    } else if (COORD_HEIGHT <= *pSelCoord && *pSelCoord <= COORD_HIPS) {
        vt_cursor(BORDER_WIDTH - 7, CURSOR_OFFSET_LIST_3R + *pSelCoord - 0x20);
    }
}

struct ui_EditorInputU16 ui_editorGetInputU16(struct save_SavDat *psSave, int *pSelCoord)
{
    editorEdSetCursor(pSelCoord);

    int ibuf[4] = { 0, };
    int ch;
    int origData = save_getStatByCoord(psSave, *pSelCoord);
    struct ui_EditorInputU16 Input = { FALSE, 0 };
    BOOL flagLimitTo100 = FALSE;
    BOOL flagExpandTo1000 = FALSE;

    if (*pSelCoord == COORD_MATERNAL_INSTINCT || (COORD_RELATIONSHIP_PRINCE <= *pSelCoord && *pSelCoord <= COORD_RELATIONSHIP_BUTLER)) {
        flagLimitTo100 = TRUE;
    } else if (*pSelCoord == COORD_RENOWN) {
        flagExpandTo1000 = TRUE;
    }

    if (flagExpandTo1000) {
        ibuf[3] = origData / 1000;
        ibuf[2] = (origData % 1000) / 100; 
    } else {
        ibuf[2] = origData / 100;
    }
    ibuf[1] = (origData % 100) / 10;
    ibuf[0] = origData % 10;

    while (1) {
        if (flagExpandTo1000) {
            printf("\033[7m%d%d%d%d\033[0m\b\b\b\b", ibuf[3], ibuf[2], ibuf[1], ibuf[0]);
        } else {
            printf("\033[7m%d%d%d\033[0m\b\b\b", ibuf[2], ibuf[1], ibuf[0]);
        }
        ch = vt_getKeypress();
        if ('0' <= ch && ch <= '9') {
            if (flagExpandTo1000 && ibuf[2] != 0) {
                printf("\a");
                ibuf[3] = 1;
                ibuf[2] = 0;
                ibuf[1] = 0;
                ibuf[0] = 0;
            } else {
                if (flagExpandTo1000) {
                    ibuf[3] = 0;
                }
                ibuf[2] = ibuf[1];
                ibuf[1] = ibuf[0];
                ibuf[0] = ch - 0x30;
                if (ibuf[2] != 0 && (ibuf[1] != 0 || ibuf[0] != 0) && flagLimitTo100) {
                    printf("\a");
                    ibuf[2] = 1;
                    ibuf[1] = 0;
                    ibuf[0] = 0;
                }
            }
        } else if (ch == KEY_CR || ch == KEY_LF || ch == ' ') {
            Input.val = ibuf[2] * 100 + ibuf[1] * 10 + ibuf[0];
            if (flagExpandTo1000) {
                Input.val += ibuf[3] * 1000;
            }
            Input.flagWrite = TRUE;
            break;
        } else if (ch == KEY_BS || ch == KEY_DEL) {
            ibuf[0] = ibuf[1];
            ibuf[1] = ibuf[2];
            ibuf[2] = 0;
        } else if (ch == 'c' || ch == 'C') {
            break;
        }
    }
    return Input;
}

struct ui_EditorInputI32 ui_editorGetInputI32(struct save_SavDat *psSave, int *pSelCoord)
{
    editorEdSetCursor(pSelCoord);

    int ibuf[6] = { 0, };
    int ch;
    int origData = save_getStatByCoord(psSave, *pSelCoord);
    struct ui_EditorInputI32 Input = { FALSE, 0 };

    if (origData < 0) {
        ibuf[5] = '-';
        origData = -origData;
    } else {
        ibuf[5] = origData / 100000;
    }
    ibuf[4] = (origData % 100000) / 10000;
    ibuf[3] = (origData % 10000) / 1000;
    ibuf[2] = (origData % 1000) / 100;
    ibuf[1] = (origData % 100) / 10;
    ibuf[0] = origData % 10;
    if (ibuf[5] == '-') {
        printf("\033[7m-%d%d%d%d%d\033[0m\b\b\b\b\b\b", ibuf[4], ibuf[3], ibuf[2], ibuf[1], ibuf[0]);
    } else {
        printf("\033[7m%d%d%d%d%d%d\033[0m\b\b\b\b\b\b", ibuf[5], ibuf[4], ibuf[3], ibuf[2], ibuf[1], ibuf[0]);
    }

    while (1) {
        ch = vt_getKeypress();
        if (('0' <= ch && ch <= '9')) {
            for (int i = 5; i > 0; i--) {
                if (i == 5 && ibuf[5] == '-') {
                    continue;
                } else { 
                    ibuf[i] = ibuf[i - 1];
                }
            }
            ibuf[0] = ch - 0x30;
        } else if (ch == '-') {
            if (ibuf[5] == '-') {
                ibuf[5] = 0;
            } else {
                if (ibuf[5] == 0) {
                    ibuf[5] = '-';
                } else {
                    /* ibuf is full; shift numbers to right once and write negative sign */
                    for (int i = 0; i < 5; i++) {
                        ibuf[i] = ibuf[i + 1];
                    }
                    ibuf[5] = '-';
                }
                
            }
        } else if (ch == '+') {
            if (ibuf[5] != '-') {
                continue;
            } else {
                ibuf[5] = 0;
            }
        } else if (ch == KEY_CR || ch == KEY_LF || ch == ' ') {
            Input.val = ibuf[4] * 10000 + ibuf[3] * 1000 + ibuf[2] * 100 + ibuf[1] * 10 + ibuf[0];
            if (ibuf[5] == '-') {
                Input.val *= -1;
            } else {
                Input.val += ibuf[5] * 100000;
            }
            Input.flagWrite = TRUE;
            break;
        } else if (ch == KEY_BS || ch == KEY_DEL) {
            if (ibuf[5] == '-' && ibuf[0] == 0 && ibuf[1] == 0 && ibuf[2] == 0 && ibuf[3] == 0 && ibuf[4] == 0) {
                ibuf[5] = 0;
            } else {
                for (int i = 0; i < 4; i++) {
                    ibuf[i] = ibuf[i + 1];
                }
                if (ibuf[5] != '-') {
                    ibuf[4] = ibuf[5];
                    ibuf[5] = 0;
                } else {
                    ibuf[4] = 0;
                }
            }
        } else if (ch == 'c' || ch == 'C') {
            break;
        }
        if (ibuf[5] == '-') {
            printf("\033[7m-%d%d%d%d%d\033[0m\b\b\b\b\b\b", ibuf[4], ibuf[3], ibuf[2], ibuf[1], ibuf[0]);
        } else {
            printf("\033[7m%d%d%d%d%d%d\033[0m\b\b\b\b\b\b", ibuf[5], ibuf[4], ibuf[3], ibuf[2], ibuf[1], ibuf[0]);
        }
    }
    return Input;
}

struct ui_EditorInputU16fxp2dp ui_editorGetInputU16fxp2dp(struct save_SavDat *psSave, int *pSelCoord)
{
    editorEdSetCursor(pSelCoord);

    int ibuf[5] = { 0, };
    int ch;
    int origData = save_getStatByCoord(psSave, *pSelCoord);
    struct ui_EditorInputU16fxp2dp Input = { FALSE, 0 };

    ibuf[4] = (origData % 100000) / 10000;
    ibuf[3] = (origData % 10000) / 1000;
    ibuf[2] = (origData % 1000) / 100;
    ibuf[1] = (origData % 100) / 10;
    ibuf[0] = origData % 10;

    while (1) {
        printf("\033[7m%d%d%d.%d%d\033[0m\b\b\b\b\b\b", ibuf[4], ibuf[3], ibuf[2], ibuf[1], ibuf[0]);
        ch = vt_getKeypress();
        if ('0' <= ch && ch <= '9') {
            if (ibuf[4] * 10000 + ibuf[3] * 1000 + ibuf[2] * 100 + ibuf[1] * 10 + ibuf[0] == U16FXP2DP_T_LIMIT) {
                printf("\a");
                for (int i = 0; i < 5; i++) {
                    ibuf[i] = 0;
                }
                continue;
            } 
            for (int i = 4; i > 0; i--) {
                ibuf[i] = ibuf[i - 1];
            }
            ibuf[0] = ch - 0x30;
            if ((ibuf[4] * 10000 + ibuf[3] * 1000 + ibuf[2] * 100 + ibuf[1] * 10 + ibuf[0]) > U16FXP2DP_T_LIMIT) {
                printf("\a");
                ibuf[4] = (U16FXP2DP_T_LIMIT % 100000) / 10000;
                ibuf[3] = (U16FXP2DP_T_LIMIT % 10000) / 1000;
                ibuf[2] = (U16FXP2DP_T_LIMIT % 1000) / 100;
                ibuf[1] = (U16FXP2DP_T_LIMIT % 100) / 10;
                ibuf[0] = U16FXP2DP_T_LIMIT % 10;
            }
        } else if (ch == KEY_CR || ch == KEY_LF || ch == ' ') {
            Input.val = ibuf[4] * 10000 + ibuf[3] * 1000 + ibuf[2] * 100 + ibuf[1] * 10 + ibuf[0];
            Input.flagWrite = TRUE;
            break;
        } else if (ch == KEY_BS || ch == KEY_DEL) {
            for (int i = 0; i < 4; i++) {
                ibuf[i] = ibuf[i + 1];
            }
            ibuf[4] = 0;
        } else if (ch == 'c' || ch == 'C') {
            break;
        }
    }
    return Input;
}

static void selectorPrintName(int fileNum) /* helper function for ui_selectorSelFile */
{
    resRetTypedef result;
    char fname[PATH_MAX_LEN - 4] = { 0, }; /* buffer to save original file name */
    FILE *fSav = NULL;
    struct file_Buffer Buf;

    if (fileNum == 1) {
        fSav = fopen("userData.bin", "rb+"); /* first save does not have number in its name */
    } else {
        snprintf(fname, sizeof(fname), "userData%d.bin", fileNum);
        fSav = fopen(fname, "rb+");
    }
    if (fSav == NULL) {
        printf(Langs[g_lang].errFileOpen);
        printf("\b\b ");
    } 
    Buf = file_fileToBuf(fSav);
    fclose(fSav);
    fSav = NULL;
    file_decrypt(&Buf);
    result = save_checkVaildity(&Buf);

    if (result != SUCCESS) {
        printf("\b\b\b\b\b\b\b\b\b");
        printf(Langs[g_lang].fileSelectorWarningFileInvalid);
    } else {
        save_printFirstName(&Buf);
        printf(" ");
        save_printLastName(&Buf);
    }

    free(Buf.data);
    Buf.data = NULL;
    Buf.size = 0;
}

int ui_selectorSelFile(struct file_FileList *psList)
{
    int selected = psList->Files[0].number;
    int index = 1;
    int ch;
    
    while (1) {
        vt_cursor(BORDER_WIDTH / 2, BORDER_HEIGHT / 2 - 1);
        if (index != 1) {
            printf("▲");
        } else {
            printf(" ");
        }
        vt_cursor(BORDER_WIDTH / 2 - 1, BORDER_HEIGHT / 2);
        printf("\033[7m %02d \b\033[0m", selected);
        vt_cursor(BORDER_WIDTH / 2, BORDER_HEIGHT / 2 + 1);
        if (index < psList->count) {
            printf("▼");
        } else {
            printf(" ");
        }
        vt_cursor(BORDER_WIDTH / 2 - BORDER_WIDTH / 3 + 1, BORDER_HEIGHT / 2 + 3);
        for (int i = 0; i < BORDER_WIDTH /3 * 2 - 2; i++) {
            printf(" ");
        }
        vt_cursor(BORDER_WIDTH / 2 - 7, BORDER_HEIGHT / 2 + 3);
        selectorPrintName(psList->Files[index - 1].number);
        vt_cursor(BORDER_WIDTH / 2 + 2, BORDER_HEIGHT / 2);

        ch = vt_getKeypress();
        if (ch == KEY_CR || ch == KEY_LF) {
            break;
        } else if (ch == KEY_UP && index > 1) {
            selected = psList->Files[--index - 1].number;
        } else if (ch == KEY_DOWN && index < psList->count) {
            selected = psList->Files[++index - 1].number;
        } else if (ch == 'q' || ch == 'Q') {
            vt_cursor(2, BORDER_HEIGHT / 2 + BORDER_HEIGHT / 3 + 1);
            return SAVE_NUM_NOT_SET;
        }
    }
    return selected;
}

void ui_selectorDrawBorder()
{
    vt_clearScreen();
    vt_cursor(1,1);
    printf("Version %s\n", PM2REGEN_ED_VERSION);
    vt_cursor(BORDER_WIDTH / 2 - BORDER_WIDTH / 3, BORDER_HEIGHT / 2 - BORDER_HEIGHT / 4);
    printf("┏");
    for (int i = 0; i < BORDER_WIDTH /3 * 2 - 2; i++) {
        printf("━");
    }
    printf("┓");
    for (int i = 0; i < BORDER_HEIGHT / 2 - 1; i++) {
        vt_cursor(BORDER_WIDTH / 2 - BORDER_WIDTH / 3, BORDER_HEIGHT / 2 - BORDER_HEIGHT / 4 + 1 + i);
        printf("┃");
        for (int j = 0; j < BORDER_WIDTH / 3 * 2 - 2; j++) {
            printf(" ");
        }
        printf("┃");
    }
    vt_cursor(BORDER_WIDTH / 2 - BORDER_WIDTH / 3, BORDER_HEIGHT / 2 + BORDER_HEIGHT / 4);
    printf("┗");
    for (int i = 0; i < BORDER_WIDTH / 3 * 2 - 2; i++) {
        printf("━");
    }
    printf("┛");
    
    vt_cursor(BORDER_WIDTH / 2 - BORDER_WIDTH / 3 + 10, BORDER_HEIGHT / 2 - BORDER_HEIGHT / 4 + 2);
    printf(Langs[g_lang].msgFileSelector);
    vt_cursor(BORDER_WIDTH / 2 - BORDER_WIDTH / 3 + 5, BORDER_HEIGHT / 2 + BORDER_HEIGHT / 4 + 1);
    printf(Langs[g_lang].guideFileSelector);
}