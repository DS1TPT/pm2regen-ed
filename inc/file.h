/*
 * File Name: file.h
 * Description: file related stuff for pm2regen-ed
 * Notice: This file is a part of "pm2regen-ed".
 *         Please check main.c or README.md for more information.
 *
 * Copyright (C) 2026 Lee Geon-goo <github.com/DS1TPT>
 *
 * This work is provided "AS IS", WITHOUT WARRANTY OF ANY KIND. You can 
 * redistribute it and/or modify it under the terms of the Do What The Fuck
 * You Want To Greater Public License, as published by Lee Geon-goo 
 * <github.com/DS1TPT>. You should have received a copy of the Do What The
 * Fuck You Want To Greater Public License. If not, see
 * <https://github.com/DS1TPT/wtfgpl> for more details.
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
