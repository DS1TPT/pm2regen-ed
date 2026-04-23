/*
 * File Name: ui.h
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

#ifndef UI_H
#define UI_H

#include "main.h"
#include "file.h"
#include "save.h"

#define BORDER_WIDTH 78
#define BORDER_HEIGHT 20
#define BORDER_VERT_SECOND_X 27
#define BORDER_VERT_THIRD_X 52
#define BORDER_HOR_SECOND_Y 12
#define BORDER_HOR_THIRD_Y 18

#define CURSOR_OFFSET_LIST_1L 2
#define CURSOR_OFFSET_LIST_2L 3
#define CURSOR_OFFSET_LIST_3L 4
#define CURSOR_OFFSET_LIST_1M 2
#define CURSOR_OFFSET_ADDITIONAL_1M 5
#define CURSOR_OFFSET_GAP_1_2M 1
#define CURSOR_OFFSET_LIST_2M (CURSOR_OFFSET_LIST_1M + CURSOR_OFFSET_ADDITIONAL_1M)
#define CURSOR_OFFSET_LIST_3M 5
#define CURSOR_OFFSET_LIST_1R (CURSOR_OFFSET_LIST_1M)
#define CURSOR_OFFSET_ADDITIONAL_1R 5
#define CURSOR_OFFSET_GAP_1_2R 1
#define CURSOR_OFFSET_LIST_2R (CURSOR_OFFSET_LIST_1R + CURSOR_OFFSET_ADDITIONAL_1R)
#define CURSOR_OFFSET_LIST_3R 5

typedef enum {
    EDITOR_CMD_EDIT = 0,
    EDITOR_CMD_SAVE = 1,
    EDITOR_CMD_QUIT = 2
} ui_editorCmdTypedef;

typedef enum {
    EDITOR_MODE_SEL = 0,
    EDITOR_MODE_EDIT = 1
} ui_editorModeTypedef;

typedef enum {
    EDITOR_HINT_INT_MINVAL = 0,
    EDITOR_HINT_INT_MAXVAL = 1,
    EDITOR_HINT_FXP_MINVAL = 2,
    EDITOR_HINT_FXP_MAXVAL = 3
} ui_editorHintTypedef;

struct ui_EditorInput {
    BOOL flagWrite;
    int32_t val;
};

 /* if type is POPUP_YN, return will be 0(No) or 1(Yes).
  * if type is POPUP_OK, return will be always 0.
  */
int ui_popup(popupTypedef type, unsigned sizeX, unsigned sizeY, const char *msg, BOOL isDefaultYes);
void ui_editorDrawBorder(); /* Draw editor border. this function implies clearScreen */
void ui_editorPrintGuide(ui_editorModeTypedef mode);
void ui_editorPrintHint(ui_editorHintTypedef hintType, int value);
ui_editorCmdTypedef ui_editorSel(struct save_SavDat *psSave, int *pSelCoord);
struct ui_EditorInput ui_editorGetInput(struct save_SavDat *psSave, int *pSelCoord);
int ui_selectorSelFile(struct file_FileList *psList); /* Returns selected file number or -1 on quit command. Implies clearScreen */
void ui_selectorDrawBorder(); /* Draw file selector border. This function implies clearScreen */

#endif /* UI_H */