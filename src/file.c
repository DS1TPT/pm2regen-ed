/*
 * File Name: file.c
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

#include "file.h"
#include "tinyAES/aes.h"

typedef const uint8_t * CBP;
typedef uint8_t * BP;
#define VvvVWvWv static
#define wWWwvWvW void
#define BD uint8_t
#define VX(a,b) (a ^ b)
#define I(a) (a + 1)
#define ll ++
#define AT(a) [a]
#define AL [32]
#define DOO(a) for (int i = 1; i < a; i+=2)
#define DOE(a) for (int i = 0; i < a; i+=2)
#define M(a) memset(a, 0, 16)
#define T(a) if(!a)
#define NO else
#define AG continue

const uint8_t GCD[] = { 0x79, 0x67, 0x26, 0x28, 0x67, 0x49, 0x79, 0x7B, 
                        0x34, 0x6A, 0x12, 0x0B, 0x58, 0x7E, 0x61, 0x11, 
                        0x43, 0x09, 0x29, 0x0B, 0x6E, 0x71, 0x77, 0x65, 
                        0x5F, 0x40, 0x29, 0x5C, 0x1D, 0x1E, 0x50, 0x50 };

BD K[17], V[17];

struct file_Buffer file_fileToBuf(FILE *fp) /* read a file and save its data to buffer */
{
    struct file_Buffer Buf;
    Buf.data = NULL;
    Buf.size = 0;
    
    if (fp == NULL) {
        return Buf;
    }
    
    fseek(fp, 0, SEEK_END); /* save file size */
    Buf.size = ftell(fp);
    rewind(fp);
    
    Buf.data = (char *)malloc(sizeof(char)*Buf.size); /* dynamic allocate mem */
    if (Buf.data == NULL) {
        Buf.size = 0;
        return Buf;
    }
        
    size_t readSize = fread(Buf.data, 1, Buf.size, fp);
    if (readSize != Buf.size) {
        free(Buf.data);
        Buf.data = NULL;
        Buf.size = 0;
        return Buf;
    } else {
        return Buf;
    }
}

VvvVWvWv wWWwvWvW gkv(CBP S,BP D,BP d,BD ISK){BP p=(BP)S,P=(BP)
(CBP)I(S);BD da AL;BD X=0X00;DOE(31){;da[i]=*p ll^X;da 
AT((i+1))=*P++^X;p ll;P ll;{X=da AT(i)^da AT((I(i)));}}T((!ISK)
){DOE(31){*d++=da[(((i)))];}da[17]=0;}NO{DOO(32){*D 
ll=da[i];}da AT(17)=0;}T(((ISK))){DOE(31){*d++=da[(((((i)))))];}
da AT(I(16))=0;}NO{DOO(32){*D ll=da[i];}da AT(I(I((I(I(13))))))=0;}}

/* Save data in buffer to file. This function does NOT re-open file.
 * This function will zero-fill file before write actual data to file.
 */
resRetTypedef file_bufToFile(FILE *fp, struct file_Buffer *psBuf)
{
    if (fp == NULL) {
        return FAIL_OPEN;
    }
    if (psBuf->data == NULL || psBuf->size == 0) {
        return FAIL_MEMORY;
    }
    
    /* get file size */
    fseek(fp, 0, SEEK_END);
    long lSize = ftell(fp);
    rewind(fp);

    /* zero-fill */
    for (long l = 0; l < lSize; l++) {
        fputc(0, fp);
    }
    rewind(fp);

    /* write to file */
    if (fwrite(psBuf->data, 1, psBuf->size, fp) < psBuf->size) {
        return FAIL_WRITE;
    } else {
        fflush(fp);
        return SUCCESS;
    }
}

resRetTypedef file_encrypt(struct file_Buffer *pBuf)
{
    if (pBuf->data == NULL || pBuf->size == 0) {
        return FAIL_OPEN;
    }

    gkv(GCD, V, K, 0x5e);
    struct AES_ctx ctx;
    AES_init_ctx_iv(&ctx, K, V);
    memset(K, 0, 16);
    memset(V, 0, 16);
    AES_CBC_encrypt_buffer(&ctx, pBuf->data, pBuf->size);
    return SUCCESS;
}

resRetTypedef file_decrypt(struct file_Buffer *pBuf)
{
    if (pBuf->data == NULL || pBuf->size == 0) {
        return FAIL_OPEN;
    }
    
    gkv(GCD, V, K, 0x5e);
    struct AES_ctx ctx;
    AES_init_ctx_iv(&ctx, K, V);
    memset(K, 0, 16);
    memset(V, 0, 16);
    AES_CBC_decrypt_buffer(&ctx, pBuf->data, pBuf->size);
    return SUCCESS;
}

static int compareFileInfo(const void *pa, const void *pb) { /* helper function for file_getFileList() */
    struct file_FileInfo *psA = (struct file_FileInfo*) pa;
    struct file_FileInfo *psB = (struct file_FileInfo*) pb;
    return (psA->number - psB->number);
}

#ifdef _WIN32
struct file_FileList file_getFileList() 
{
    struct file_FileList Result;
    Result.count = 0;
    
    WIN32_FIND_DATA FindData;
    HANDLE hFind = FindFirstFile("userData*.bin", &FindData);

    if (hFind != INVALID_HANDLE_VALUE) {
        do {
            int num, bytes_read = 0;
            if (strcmp(FindData.cFileName, "userData.bin") == 0) { /* name of first save is userData.bin */
                strncpy(Result.Files[Result.count].name, FindData.cFileName, PATH_MAX_LEN);
                Result.Files[Result.count++].number = 1;
            } else if (sscanf(FindData.cFileName, "userData%d.bin%n", &num, &bytes_read) == 1) {
                if (bytes_read == (int) strlen(FindData.cFileName)) {
                    if (num == 1) {
                        continue; /* userData1.bin is illegal */
                    } else if (Result.count < SAVE_NUM_MAX) {
                        strncpy(Result.Files[Result.count].name, FindData.cFileName, PATH_MAX_LEN);
                        Result.Files[Result.count++].number = num;
                    }
                }
            }
        } while (FindNextFile(hFind, &FindData) && Result.count < SAVE_NUM_MAX);
        FindClose(hFind);
    }

    if (Result.count > 0) {
        qsort(Result.Files, Result.count, sizeof(struct file_FileInfo), compareFileInfo);
    }

    return Result;
}
#else
struct file_FileList file_getFileList() {
    struct file_FileList Result;
    Result.count = 0;

    DIR *dir = opendir(".");
    struct dirent *psEntry;

    if (dir) {
        while ((psEntry = readdir(dir)) != NULL && Result.count < SAVE_NUM_MAX) {
            int num, bytes_read = 0;
            if (strcmp(psEntry->d_name, "userData.bin") == 0) { /* name of first save is userData.bin */
                strncpy(Result.Files[Result.count].name, psEntry->d_name, PATH_MAX_LEN);
                Result.Files[Result.count++].number = 1;
            } else if (sscanf(psEntry->d_name, "userData%d.bin%n", &num, &bytes_read) == 1) {
                if (num == 1) {
                    continue; /* userData1.bin is illegal */
                } else if (bytes_read == (int) strlen(psEntry->d_name)) {
                    strncpy(Result.Files[Result.count].name, psEntry->d_name, PATH_MAX_LEN);
                    Result.Files[Result.count++].number = num;
                }
            }
        }
        closedir(dir);
    }

    if (Result.count > 0) {
        qsort(Result.Files, Result.count, sizeof(struct file_FileInfo), compareFileInfo);
    }

    return Result;
}
#endif

resRetTypedef file_createBak(FILE *fSav, int saveNum)
{
    FILE *fBak = NULL;
    char fnameBak[PATH_MAX_LEN] = { 0, }; /* buffer to save backup file name */
    char *cpbuf = NULL;
    long lCpsize = 0;
    
    fseek(fSav, 0, SEEK_END); /* save file size */
    lCpsize = ftell(fSav);
    rewind(fSav);
    
    cpbuf = (char *)malloc(sizeof(char)*lCpsize); /* dynamic allocate mem */
    if (cpbuf == NULL) {
        return FAIL_MEMORY;
    }    
    size_t readSize = fread(cpbuf, 1, lCpsize, fSav);
    if (readSize != lCpsize) {
        free(cpbuf);
        return FAIL_READ;
    }

    rewind(fSav);

    if (saveNum == 1) {
        fBak = fopen("userData_bak.bin", "wb+"); /* first save does not have number in its name */
    } else {
        snprintf(fnameBak, sizeof(fnameBak), "userData%d_bak.bin", saveNum);
        fBak = fopen(fnameBak, "wb+");
    }
    if (fBak == NULL) {
        return FAIL_BAK;
    }

    if (fwrite(cpbuf, 1, lCpsize, fBak) < lCpsize) {
        free(cpbuf);
        fclose(fBak);
        remove(fnameBak);
        return FAIL_BAK;
    }
    
    free(cpbuf);
    fflush(fBak);
    fclose(fBak);
    return SUCCESS;
}