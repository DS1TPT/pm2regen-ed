/*
 * File Name: main.c
 * Description: Main source code of pm2regen-ed, a tiny cross-platform TUI save editor for Princess Maker 2 Regeneration
 * Notice: 1. "pm2regen-ed" is a free software to allow players to edit statistics
 *         of PM2 Regeneration to collect endings faster or play it in unusual ways, just like the
 *         editors we had for DOS, Win3.1/DOS and Refine versions of Princess Maker 2.
 *         2. This software contains tiny-AES-c by kokke @ Github. You can obtain
 *         source code and information from: https://github.com/kokke/tiny-AES-c/
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
 *
 * DISCLAIMER
 *  
 * 1. NO ORIGINAL ASSETS & RESOURCES
 * THIS SOFTWARE DOES NOT INCLUDE, DISTRIBUTE, OR MODIFY ANY ORIGINAL GAME ASSETS, 
 * INCLUDING BUT NOT LIMITED TO EXECUTABLE FILES (.EXE, .DLL), IMAGES, OR AUDIO.
 * 
 * 2. DATA ACCESS INTENT
 * This Software provides only the minimum necessary functions for modifying save data. 
 * This Software does NOT include any features for dynamically or intelligently analyzing/probing 
 * file structures. This Software can only read and modify data at fixed offsets according to 
 * pre-defined specifications. This Software EXCLUSIVELY modifies data files associated with the user 
 * that contain in-game progress data, specifically matching the pattern 'userData.bin' or 
 * 'userData[number].bin' (e.g., 'userData2.bin', 'userData10.bin'). This Software does NOT access any
 * copyrightable game assets, including but not limited to executable files and resource container files.
 * 
 * 3. NO COPYRIGHT INFRINGEMENT INTENT
 * THE ENCRYPTION / DECRYPTION LOGIC IS INTENDED SOLELY FOR ALLOWING USERS TO ACCESS THEIR OWN
 * PROGRESS DATA, SPECIFICALLY 'userData.bin' AND ANY NUMBERED VARIATIONS THEREOF, AS DEFINED IN THE 
 * 'DATA ACCESS INTENT' SECTION OF THE DISCLAIMER. IT IS NOT DESIGNED TO, NOR DOES IT FACILITATE, 
 * COPYRIGHT INFRINGEMENT OR SOFTWARE PIRACY.
 */

/* Includes */
#include "main.h"
#include "ui.h"
#include "vt.h"
#include "file.h"
#include "save.h"
#include "offset.h"

/* global variables */
int g_lang = DEFAULT_LANG;

/* function bodies */

#ifdef _WIN32
void sleep_s(int seconds) { Sleep(seconds * 1000); }
#else
void sleep_s(int seconds) { sleep(seconds); }
#endif

resRetTypedef readData(FILE *fSav, struct file_Buffer *psBufDest, struct save_SavDat *psSaveDest)
{
    resRetTypedef ret;
    do {
        *psBufDest = file_fileToBuf(fSav);
        if (psBufDest->data == NULL || psBufDest->size == 0) {
            ret = FAIL_READ;
            break;
        } else if (psBufDest->size < OFFSET_MONEY + 4) {
            ret = FAIL_FILESIZE;
            break;
        }
        ret = file_decrypt(psBufDest);
        if (ret != SUCCESS) {
            break;
        }
        ret = save_checkVaildity(psBufDest);
        if (ret != SUCCESS) {
            break;
        }
        ret = save_bufToStruct(psBufDest, psSaveDest);
    } while (0);

    if (ret != SUCCESS) {
        free(psBufDest->data);
        psBufDest->data = NULL;
        psBufDest->size = 0;
    }
    return ret;
}

resRetTypedef writeData(FILE *fSav, struct file_Buffer *psBufDest, struct save_SavDat *psSaveDest)
{
    resRetTypedef ret;
    do {
        ret = save_structToBuf(psBufDest, psSaveDest);
        if (ret != SUCCESS) {
            break;
        }
        ret = file_encrypt(psBufDest);
        if (ret != SUCCESS) {
            break;
        }
        ret = file_bufToFile(fSav, psBufDest);
    } while (0);

    /* clean-up is not needed */
    return ret;
}

resRetTypedef editor(FILE *fSav)
{
    resRetTypedef ret;
    struct file_Buffer Buf;
    struct save_SavDat Save;
    int selCoord = 0x00;
    ui_editorCmdTypedef cmd;
    struct ui_EditorInputI32 InputI32;
    struct ui_EditorInputU16 InputU16;
    struct ui_EditorInputU16fxp2dp InputU16fxp2dp;
    BOOL flagDiscardChanges = FALSE;

    ret = readData(fSav, &Buf, &Save);
    if (ret) {
        return ret;
    }
    ui_editorDrawBorder();
    save_printStat(&Save);
    save_highlightStat(&Save, selCoord, TRUE);

    while (1) {
        ui_editorPrintGuide(EDITOR_MODE_SEL);
        cmd = ui_editorSel(&Save, &selCoord);
        if (cmd == EDITOR_CMD_EDIT) {
            ui_editorPrintGuide(EDITOR_MODE_EDIT);
            if (selCoord == COORD_MONEY) {
                InputI32 = ui_editorGetInputI32(&Save, &selCoord);
                if (InputI32.flagWrite) {
                    InputI32.flagWrite = FALSE;
                    save_writeToStructByCoord(&Save, selCoord, InputI32.val);
                }
            } else if (COORD_HEIGHT <= selCoord && selCoord <= COORD_HIPS) {
                InputU16fxp2dp = ui_editorGetInputU16fxp2dp(&Save, &selCoord);
                if (InputU16fxp2dp.flagWrite) {
                    InputU16fxp2dp.flagWrite = FALSE;
                    save_writeToStructByCoord(&Save, selCoord, InputU16fxp2dp.val);
                }
            } else { 
                InputU16 = ui_editorGetInputU16(&Save, &selCoord);
                if (InputU16.flagWrite) {
                    InputU16.flagWrite = FALSE;
                    save_writeToStructByCoord(&Save, selCoord, InputU16.val);
                }
            }
            save_printStat(&Save);
            save_highlightStat(&Save, selCoord, TRUE);
        } else if (cmd == EDITOR_CMD_SAVE) {
            break;
        } else if (cmd == EDITOR_CMD_QUIT) {
            flagDiscardChanges = TRUE;
            break;
        }
    }

    if (flagDiscardChanges) {
        ret = CANCELLED;
    } else {
        ret = writeData(fSav, &Buf, &Save);
    }

    free(Buf.data);
    Buf.data = NULL;
    Buf.size = 0;

    ui_editorDrawBorder();
    save_printStat(&Save);

    return ret;
}

unsigned fileSelector()
{
    struct file_FileList List = file_getFileList();
    if (List.count <= 0) {
        printf("\033[7;1;31m");
        printf(Langs[g_lang].errNoFile);
        sleep_s(SLEEP_DURATION);
        return SAVE_NUM_NOT_SET; /* return immediately when no file is found */
    }
    ui_selectorDrawBorder();
    return ui_selectorSelFile(&List);
}

int main(int argc, char **argv)
{
    resRetTypedef result;
    char fnameSav[PATH_MAX_LEN - 4] = { 0, }; /* buffer to save original file name */
    FILE *fSav = NULL;
    BOOL flagFileSelectorRequired = FALSE;
    BOOL flagHelp = FALSE;
    BOOL flagInvalidArg = FALSE;
    BOOL flagTooManyArg = FALSE;
    BOOL flagFailOpen = FALSE;
    BOOL flagFailBak = FALSE;
    BOOL flagLicense = FALSE;
    int saveNum = SAVE_NUM_NOT_SET;

    vt_enableAnsi(TRUE);
    vt_setEchoCanonical(FALSE);

    switch (argc) {
    case 1: /* no argument -> set selector flag */
        flagFileSelectorRequired = TRUE;
        break;
    case 2: /* check if help, language, or number argument */
        if (!strcmp(argv[1], "-h") || !strcmp(argv[1], "--help")) {
            flagHelp = TRUE;
        } else if (!strcmp(argv[1], "en")) { /* language argument only -> set file selector flag */
            g_lang = LANG_EN;
            flagFileSelectorRequired = TRUE;
        } else if (!strcmp(argv[1], "kr")) {
            g_lang = LANG_KR;
            flagFileSelectorRequired = TRUE;
        } else if (!strcmp(argv[1], "jp")) {
            g_lang = LANG_JP;
            flagFileSelectorRequired = TRUE;
        } else if (!strcmp(argv[1], "-l") || !strcmp(argv[1], "--license")) {
            flagLicense = TRUE;
        } else if (atoi(argv[1])) {
            saveNum = atoi(argv[1]);
            if (saveNum < 1 || saveNum > SAVE_NUM_MAX) {
                flagInvalidArg = TRUE; 
                saveNum = SAVE_NUM_NOT_SET;
            }
        } else {
            flagInvalidArg = TRUE;
        }
        break;
    default:
        /* Check language first */
        if (!strcmp(argv[1], "en")) {
            g_lang = LANG_EN;
        } else if (!strcmp(argv[1], "kr")) {
            g_lang = LANG_KR;
        } else if (!strcmp(argv[1], "jp")) {
            g_lang = LANG_JP;
        } else { /* invalid first argument */
            flagInvalidArg = TRUE;
        }

        if (argc > 3) {
            flagTooManyArg = TRUE;
        }

        if (atoi(argv[2])) { /* numeric argument is given */
            saveNum = atoi(argv[2]);
            if (saveNum < 1 || saveNum > SAVE_NUM_MAX) {
                flagInvalidArg = TRUE;
                saveNum = SAVE_NUM_NOT_SET;
            }
        } else if (!strcmp(argv[2], "-h") || !strcmp(argv[2], "--help")) {
            flagHelp = TRUE;
        } else {
            flagInvalidArg = TRUE;
        }
        break;
    }

    /* Check flags set by argument(s) */
    if (flagFileSelectorRequired) {
        saveNum = fileSelector();
        if (saveNum == SAVE_NUM_NOT_SET) {
            flagFileSelectorRequired = FALSE; /* setting to false to avoid triggering sleep function */
            result = CANCELLED;
        }
    } else if (flagTooManyArg) {
        printf("\033[7;1;31m");
        printf(Langs[g_lang].errTooManyArg);
    } else if (flagInvalidArg) {
        printf("\033[7;1;31m");
        printf(Langs[g_lang].errArg);
    }
    if (flagHelp || flagInvalidArg || flagTooManyArg) {
        printf("\033[0m");
        printf("Version %s\n", PM2REGEN_ED_VERSION);
        printf(Langs[g_lang].help);
        result = CANCELLED; /* to avoid duplicate messages */
    } else if (flagLicense) {
        printf(license);
        printf(Langs[g_lang].anykey);
        (void) vt_getKeypress();
        printf(disclaimer);
        result = CANCELLED;
    }
    if (saveNum != SAVE_NUM_NOT_SET) {
        if (saveNum == 1) {
            fSav = fopen("userData.bin", "rb+"); /* first save does not have number in its name */
        } else {
            snprintf(fnameSav, sizeof(fnameSav), "userData%d.bin", saveNum);
            fSav = fopen(fnameSav, "rb+");
        }
        if (fSav == NULL) {
            flagFailOpen = TRUE;
            result = FAIL_OPEN;
        } else {
            result = file_createBak(fSav, saveNum);
            if (result != SUCCESS) {
                flagFailBak = TRUE;
                fclose(fSav);
                fSav = NULL;
            } else {
                result = editor(fSav);
                vt_clearLine(BORDER_HEIGHT + 1);
                vt_clearLine(BORDER_HEIGHT + 2);
                vt_clearLine(BORDER_HEIGHT + 3);
                vt_cursor(1, BORDER_HEIGHT + 1);
                if (result != SUCCESS && result != CANCELLED) {
                    printf("\033[7;1;31m");
                }
            }
        }
    }

    switch (result) {
    case SUCCESS:
        printf(Langs[g_lang].success);
        break;
    case FAIL_WRITE:
        printf(Langs[g_lang].errFileWrite);
        break;
    case FAIL_OPEN:
        printf(Langs[g_lang].errFileOpen);
        break;
    case FAIL_READ:
        printf(Langs[g_lang].errFileRead);
        break;
    case FAIL_MEMORY:
        printf(Langs[g_lang].errMemory);
        break;
    case FAIL_FILESIZE:
        printf(Langs[g_lang].errFileSize);
        break;
    case FAIL_INVALID_FILE:
        printf(Langs[g_lang].errFileInvalid);
        break;
    case CANCELLED:
        if (saveNum != SAVE_NUM_NOT_SET) {
            printf(Langs[g_lang].cancelled);
        }
        break;
    }

    if (flagFailBak) {
        printf(Langs[g_lang].errFileBak);
    }
    
    /* clean up */
    if (fSav != NULL) {
        fclose(fSav);
        fSav = NULL;
    }

    printf("\033[0m");
    vt_setEchoCanonical(TRUE);
    vt_enableAnsi(FALSE);

    if (flagFileSelectorRequired) {
        sleep_s(SLEEP_DURATION);
    }

    if (result == SUCCESS || result == CANCELLED) {
        return 0;
    } else {
        return 1;
    }
}
