/*
 * File Name: offset.h
 * Description: hexadecimal offset for various statistics
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

/* little endian */

#ifndef OFFSET_H
#define OFFSET_H

/* General Stats */
#define OFFSET_STAMINA             0x3f
#define OFFSET_STRENGTH            0x41
#define OFFSET_INTELLIGENCE        0x43
#define OFFSET_REFINEMENT          0x45
#define OFFSET_GLAMOUR             0x47
#define OFFSET_MORALITY            0x49
#define OFFSET_FAITH               0x4b 
#define OFFSET_SIN                 0x4d
#define OFFSET_SENSITIVITY         0x4f
#define OFFSET_STRESS              0x51

/* 4 Reputation Stats */
#define OFFSET_FIGHT_REP           0x53
#define OFFSET_MAGIC_REP           0x55
#define OFFSET_SOCIAL_REP          0x57
#define OFFSET_HOUSE_REP           0x59

/* Combat-related Stats */
#define OFFSET_COMBAT_SKILL        0x5b
#define OFFSET_ATTACK              0x5d
#define OFFSET_DEFENSE             0x5f
#define OFFSET_MAGIC_SKILL         0x61
#define OFFSET_MAGIC_ATTACK        0x63
#define OFFSET_MAGIC_DEFENSE       0x65

/* Social Skills */
#define OFFSET_DECORUM             0x67
#define OFFSET_ARTISTRY            0x69
#define OFFSET_ELOQUENCE           0x6b

/* Housework Skills */
#define OFFSET_COOKING             0x6d
#define OFFSET_CLEANING            0x6f
#define OFFSET_TEMPER              0x71

/* The ONLY int32 statistic [$]\($u$)/[$] ). */
#define OFFSET_MONEY               0x75 /* 4 Bytes */

/* Name */
#define OFFSET_NAME_START          0x79
/* Data at 0x79 defines how many bytes the first name occupies.
 * If *0x79 is 08, next 8 bytes will be the first name.
 * A byte right after the first name defines how many bytes the last name occupies.
 * Encoding is UTF-8.
 * Max length of name is 8B(English) or 12B(CJK, 4x 3B chars)
 * 
 * example 1:           [08] 5A 59 58 57 56 55 54 53 [08] 41 42 43 44 45 46 47 48
 * (Single-byte char)   LEN  Z  Y  X  W  V  U  T  S  LEN  A  B  C  D  E  F  G  H
 * example 2:           [09] (EB AF B8) (E8 A6 AC) (EB 82 B4) [03] (EC 9D B4)
 * (Multi-byte char)    LEN      미         리         내     LEN      이
 */

/* Personal Stats */
/* Personal statistic data order: Height Weight B W H ... Renown
 * These stats except for "Renown" are unsigned 16b fixed point 2 decimal point type.
 */
#define OFFSET_PERSONAL_FROM_REF         0x24 /* reference: last byte of last name */
#define OFFSET_PATTERN_HEIGHT            0x00
#define OFFSET_PATTERN_WEIGHT            0x02
#define OFFSET_PATTERN_BUST              0x04
#define OFFSET_PATTERN_WAIST             0x06
#define OFFSET_PATTERN_HIPS              0x08
#define OFFSET_PATTERN_RENOWN            0x19

/* Hidden Stats */
#define OFFSET_HID_TO_REF                0x14a /* First byte of hidden stats pattern to length descriptor of diet string */
#define OFFSET_PATTERN_R_PRINCE          0x00
#define OFFSET_PATTERN_R_FATHER          0x02
#define OFFSET_PATTERN_R_BUTLER          0x04
#define OFFSET_PATTERN_MATERNAL_INSTINCT 0x06 /* maternal instinct */
#define OFFSET_PATTERN_MONSTERS_KILLED   0x08 /* number of defeated monsters */

#endif /* OFFSET_H */