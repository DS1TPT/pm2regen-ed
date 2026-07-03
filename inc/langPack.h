/*
 * File Name: langPack.h
 * Description: language pack that contains various messages
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

#ifndef LANGPACK_H
#define LANGPACK_H

#define LANG_EN 0
#define LANG_KR 1
#define LANG_JP 2

struct LangPack {
	/* statistics */
	const char *stamina;
	const char *strength;
	const char *intelligence;
	const char *refinement;
	const char *glamour;
	const char *morality;
	const char *faith;
	const char *sin;
	const char *sensitivity;
	const char *stress;
	const char *fightReputation;
	const char *magicReputation;
	const char *socialReputation;
	const char *houseReputation;
	const char *combatSkill;
	const char *attack;
	const char *defense;
	const char *magicSkill;
	const char *magicAttack;
	const char *magicDefense;
	const char *decorum;
	const char *artistry;
	const char *eloquence;
	const char *cooking;
	const char *cleaning;
	const char *temper;
	const char *money;
	const char *renown;
	const char *height;
	const char *weight;
	const char *bust;
	const char *waist;
	const char *hips;
	const char *relationshipPrince;
	const char *relationshipFather;
	const char *relationshipButler;
	const char *maternalInstinct;
	const char *monstersKilled;
	
	/* program messages */
	const char *guideNav;
	const char *guideEdit;
	const char *hintMinVal;
	const char *hintMaxVal;
	const char *msgFileSelector;
	const char *guideFileSelector;
	const char *fileSelectorWarningFileInvalid;
	const char *askSave;
	const char *askDiscard;
	const char *success;
	const char *cancelled;
	const char *popupYN_Y;
	const char *popupYN_N;
	const char *popupOk;
	const char *errNoFile;
	const char *errFileOpen;
	const char *errFileRead;
	const char *errFileWrite;
	const char *errFileBak;
	const char *errFileSize;
	const char *errFileInvalid;
	const char *errTooManyArg;
	const char *errArg;
	const char *errMemory;
	const char *help;
	const char *anykey;
};

extern const struct LangPack Langs[3];
extern const char license[];
extern const char disclaimer[];

#endif /* LANGPACK_H */
