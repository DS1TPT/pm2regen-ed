/*
 * File Name: file.h
 * Description: file related stuff for pm2regen-ed
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

#ifndef FILE_H
#define FILE_H

#include "main.h"

struct file_FileInfo {
    char name[PATH_MAX_LEN];
    unsigned number;
};

struct file_FileList {
    struct file_FileInfo Files[SAVE_NUM_MAX];
    unsigned count;
};

struct file_Buffer {
    char *data;
    size_t size;
};

struct file_Buffer file_fileToBuf(FILE *fp);
resRetTypedef file_bufToFile(FILE *fp, struct file_Buffer *pBuf);
resRetTypedef file_encrypt(struct file_Buffer *pBuf);
resRetTypedef file_decrypt(struct file_Buffer *pBuf);
resRetTypedef file_createBak(FILE *fSav, int saveNum);
struct file_FileList file_getFileList();

#endif /* FILE_H */