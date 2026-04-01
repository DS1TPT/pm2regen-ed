/*
 * File Name: langPack.c
 * Description: language pack that contains various messages
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

#include "langPack.h"

const struct LangPack Langs[3] = {
	[LANG_EN] = {
		.stamina = "Stamina",
		.strength = "Strength",
		.intelligence = "Intelligence",
		.refinement = "Refinement",
		.glamour = "Glamour",
		.morality = "Morality",
		.faith = "Faith",
		.sin = "Sin",
		.sensitivity = "Sensitivity",
		.stress = "Stress",
		.fightReputation = "Fight Reputation",
		.magicReputation = "Magic Reputation",
		.socialReputation = "Social Reputation",
		.houseReputation = "Housework Reputation",
		.combatSkill = "Combat Skill",
		.attack = "Attack",
		.defense = "Defense",
		.magicSkill = "Magic Skill",
		.magicAttack = "Magic Attack",
		.magicDefense = "Magic Defense",
		.decorum = "Decorum",
		.artistry = "Artistry",
		.eloquence = "Eloquence",
		.cooking = "Cooking",
		.cleaning = "Cleaning",
		.temper = "Temper",
		.money = "Money(GOLD)",
		.renown = "Renown",
		.height = "Height",
		.weight = "Weight",
		.bust = "Bust",
		.waist = "Waist",
		.hips = "Hips",
		.relationshipPrince = "Relationship Prince",
		.relationshipFather = "Relationship Father",
		.relationshipButler = "Relationship Butler",
		.maternalInstinct = "Maternal Instinct",
		.monstersKilled = "Monsters Killed",
		
		.guideNav = "ARROW: Select, Enter/Space: Edit, S: \033[1;4mS\033[0mave & Quit, Q: Discard & \033[1;4mQ\033[0muit",
		.guideEdit = "C: \033[1;4mC\033[0mancel, Enter/Space: Done. Numeric input only                       ",
		.msgFileSelector = "Please select save file number",
		.guideFileSelector = "ARROW: Select, Enter/Space: OK, Q: \033[1;4mQ\033[0muit",
		.fileSelectorWarningFileInvalid = "WARNING: Corrupt or Invalid file",
		.askSave = "SAVE modified data to the disk?",
		.askDiscard = "DISCARD changes and exit?",
		.success = "Save file has been successfully modified.\n",
		.cancelled = "Editing has been cancelled by user. Exiting without saving.\n",
		.popupYN_Y = "│ \033[7mYES\033[0m │  │  NO  │",
		.popupYN_N = "│ YES │  │  \033[7mNO\033[0m  │",
		.popupOk = "│ \033[7mOK\033[0m │",
		.errNoFile = "ERROR: Save file not found.\n",
		.errFileOpen = "ERROR: Failed to open file: ",
		.errFileRead = "ERROR: Failed to read data from file.\n",
		.errFileWrite = "ERROR: Failed to write data to file.\n",
		.errFileBak = "ERROR: Failed to create backup file.\n",
		.errFileSize = "ERROR: Incorrect file size.\n",
		.errFileInvalid = "ERROR: File is corrupt or invalid.\n",
		.errTooManyArg = "ERROR: Too many arguments.\n",
		.errArg = "ERROR: Invalid argument(s).\n",
		.errMemory = "ERROR: Could not get memory allocation from the system.\n",
		.help = "pm2regen-ed is simple text based save file editor for Princess Maker 2 Regeneration.\n"
	            "Usage: pm2regen-ed <lang>: select and edit userData in CURRENT directory\n"
	            "       pm2regen-ed <lang> <number>: Edit userData<number>.bin in CURRENT directory.\n"
				"       pm2regen-ed <lang> -h / --help: Show this help message\n"
				"       pm2regen-ed -l / --license: Show license\n"
	            "If argument <lang> is not given, default language set at build-time will be used.\n"
	            "Possible <lang> parameters(case-sensitive): en(English), kr(Korean), jp(Japanese)\n"
	            "Please move or copy this executable to the same folder(directory) as the save file(s) before use.\n"
	            "This software can load save files ONLY if it is in the same folder as the save file(s).\n",
		.anykey = "Press any key to continue... "
	}, [LANG_KR] = {
		.stamina = "체력",
		.strength = "근력",
		.intelligence = "지능",
		.refinement = "기품",
		.glamour = "매력",
		.morality = "도덕심",
		.faith = "신앙심",
		.sin = "업보",
		.sensitivity = "감수성",
		.stress = "스트레스",
		.fightReputation = "전사평가",
		.magicReputation = "마법평가",
		.socialReputation = "사교평가",
		.houseReputation = "가사평가",
		.combatSkill = "전투기술",
		.attack = "공격력",
		.defense = "방어력",
		.magicSkill = "마법기술",
		.magicAttack = "마력",
		.magicDefense = "항마력",
		.decorum = "예의범절",
		.artistry = "예술",
		.eloquence = "화술",
		.cooking = "요리",
		.cleaning = "청소세탁",
		.temper = "성품",
		.money = "소지금(GOLD)",
		.renown = "인맥",
		.height = "키",
		.weight = "몸무게",
		.bust = "가슴",
		.waist = "허리",
		.hips = "엉덩이",
		.relationshipPrince = "왕자와의 관계",
		.relationshipFather = "아버지와의 관계",
		.relationshipButler = "집사와의 관계",
		.maternalInstinct = "모성",
		.monstersKilled = "몬스터 살육 수",
		
		.guideNav = "방향키: 선택, Enter/Space: 수정, S: 저장 및 종료, Q: 저장하지 않고 종료",
		.guideEdit = "C: 수정 취소, Enter/Space: 수정 완료, 숫자만 입력 가능                ",
		.msgFileSelector = "세이브 파일 번호를 선택하십시오",
		.guideFileSelector = "방향키: 선택, Enter/Space: 확인, Q: 종료",
		.fileSelectorWarningFileInvalid = "\b\b경고: 손상되었거나 유효하지 않은 파일",
		.askSave = "수정사항을 디스크에 작성합니까?",
		.askDiscard = "저장하지 않고 종료합니까?",
		.success = "세이브 파일을 성공적으로 수정했습니다.\n",
		.cancelled = "사용자가 작업을 취소하였습니다. 저장하지 않고 종료합니다.\n",
		.popupYN_Y = "│ \033[7m예 \033[0m │  │아니오│",
		.popupYN_N = "│ 예  │  │\033[7m아니오\033[0m│",
		.popupOk = "│\033[7m확인\033[0m│",
		.errNoFile = "오류: 세이브 파일을 찾지 못하였습니다.\n",
		.errFileOpen = "오류: 다음 파일을 열지 못했습니다: ",
		.errFileRead = "오류: 파일을 읽지 못했습니다.\n",
		.errFileWrite = "오류: 파일에 쓰지 못했습니다.\n",
		.errFileBak = "오류: 백업 파일을 만들지 못했습니다.\n",
		.errFileSize = "오류: 파일 크기가 올바르지 않습니다.\n",
		.errFileInvalid = "오류: 파일이 손상되었거나 유효하지 않습니다.\n",
		.errTooManyArg = "오류: 인자가 너무 많습니다.\n",
		.errArg = "오류: 인자가 잘못되었습니다.\n",
		.errMemory = "오류: 시스템으로부터 메모리를 할당받지 못하였습니다.\n",
		.help = "pm2regen-ed는 프린세스 메이커 2 리제네레이션을 위한 단순한 텍스트 인터페이스 세이브 파일 편집기입니다.\n"
	            "사용법: pm2regen-ed <언어>: 현재 디렉토리에 있는 세이브 파일을 선택 및 수정 \n"
				"      pm2regen-ed <언어> <번호>: 현재 디렉토리의 userData<번호>.bin 파일을 수정\n"
				"      pm2regen-ed <언어> -h / --help: 이 도움말을 출력\n"
				"      pm2regen-ed -l / --license: 라이선스(사용 허가서) 출력\n"
	            "<언어> 인자가 주어지지 않은 경우 pm2regen-ed는 빌드시 설정한 기본 언어를 표시합니다.\n"
				"가용한 <언어> 목록(소문자만 인식): en(영어), kr(한국어), jp(일본어)\n"
	            "사용 전, 이 실행 파일을 세이브 파일과 같은 폴더(디렉터리)로 이동해주세요.\n"
	            "이 프로그램은 세이브 파일과 같은 폴더에 있을 때에만 정상적으로 파일을 불러올 수 있습니다.\n",
		.anykey = "계속하려면 아무 키나 누르십시오... "
	}, [LANG_JP] = {
		.stamina = "体力",
		.strength = "筋力",
		.intelligence = "知能",
		.refinement = "気品",
		.glamour = "色気",
		.morality = "モラル",
		.faith = "信仰",
		.sin = "因業",
		.sensitivity = "感受性",
		.stress = "ストレス",
		.fightReputation = "戦士評価",
		.magicReputation = "魔法評価",
		.socialReputation = "社交評価",
		.houseReputation = "家事評価",
		.combatSkill = "戦鬪技術",
		.attack = "攻擊力",
		.defense = "防御力",
		.magicSkill = "魔法技術",
		.magicAttack = "魔力",
		.magicDefense = "抗魔力",
		.decorum = "礼儀作法",
		.artistry = "芸術",
		.eloquence = "話術",
		.cooking = "料理",
		.cleaning = "掃除洗濯",
		.temper = "気だて",
		.money = "所持金(GOLD)",
		.renown = "人脈",
		.height = "身長",
		.weight = "体重",
		.bust = "バスト",
		.waist = "ウエスト",
		.hips = "ヒップ",
		.relationshipPrince = "王子との関係",
		.relationshipFather = "父との関係",
		.relationshipButler = "執事との関係",
		.maternalInstinct = "母性",
		.monstersKilled = "モンスター殺戮数",
		
		.guideNav = "矢印キー：選択、Enter/Space：修正、S：保存して終了、Q：保存せずに終了",
		.guideEdit = "C：キャンセル、Enter/Space：修正完了、数字のみ入力可能               ",
		.msgFileSelector = "セーブ番号を選択してください",
		.guideFileSelector = "\b\b矢印キー：選択、Enter/Space: 確認, Q: 終了",
		.fileSelectorWarningFileInvalid = "警告: 破損しているか無効なファイル",
		.askSave = "修正内容をディスクに書きますか？",
		.askDiscard = "変更を保存せずに終了しますか？",
		.success = "セーブファイルの修正に成功しました。\n",
		.cancelled = "ユーザーが作業をキャンセルしました。 保存せずに終了します。\n",
		.popupYN_Y = "│\033[7mは い\033[0m│  │いいえ│",
		.popupYN_N = "│は い│  │\033[7mいいえ\033[0m│",
		.popupOk = "│\033[7mはい\033[0m│",
		.errNoFile = "エラー：セーブファイルが見つかりませんでした。\n",
		.errFileOpen = "エラー: 次のファイルを開くことができませんでした: ",
		.errFileRead = "エラー: ファイルを読み取れませんでした。\n",
		.errFileWrite = "エラー: ファイルに書き込めませんでした。\n",
		.errFileBak = "エラー: バックアップファイルを作成できませんでした。\n",
		.errFileSize = "エラー: ファイルサイズが正しくありません。\n",
		.errFileInvalid = "エラー: ファイルが破損しているか、無効です。\n",
		.errTooManyArg = "エラー: 引数が多すぎます。\n",
		.errArg = "エラー: 無効な引数を受け取りました。\n",
		.errMemory = "エラー: システムからメモリを割り当てられませんでした。",
		.help = "pm2regen-edは、プリンセスメーカー2 リジェネレーションのためのシンプルなテキストインターフェースのセーブファイルエディタです。\n"
	            "使用法: pm2regen-ed <言語>: 現在のディレクトリにあるセーブファイルを選択して編集\n"
	            "       pm2regen-ed <言語> <番号>: 現在のディレクトリの userData<番号>.bin ファイルを修正\n"
				"       pm2regen-ed <言語> -h / --help: このヘルプを表示\n"
				"       pm2regen-ed -l / --license: ライセンスを表示(英語)\n"
	            "<言語> 引数が指定されていない場合、pm2regen-edはビルド時に設定したデフォルト言語を表示します。\n"
	            "利用可能な<言語>のリスト（小文字のみ認識）：en（英語）、kr（韓国語）、jp（日本語）\n"
	            "使用前に、この実行ファイルをセーブファイルと同じフォルダー（ディレクトリ）に移動してください。\n"
	            "このプログラムは、セーブファイルと同じフォルダーにあるときだけ、正常にファイルを読み込むことができます。\n",
		.anykey = "継続するには任意のキーを押してください。 "
	}
};

const char license[] =    "LICENSE\nCopyright (c) 2026 Lee Geon-goo\n\n"
						  "This program is free software: you can redistribute it and/or modify it under the terms of "
						  "the GNU General Public License as published by the Free Software Foundation, either version 3 "
						  "of the License, or (at you option) any later version.\n\n"
						  "This program is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; "
						  "without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. "
						  "See the GNU General Public License for more details.\n\n"
						  "You should have received a copy of the GNU General Public License along with this program. "
						  "If not, see <https://www.gnu.org/licenses/>.\n";

const char disclaimer[] = "\nDISCLAIMER\n\n"
					      "1. NO ORIGINAL ASSETS & RESOURCES INCLUDED\n"
					      "THE SOFTWARE DOES NOT INCLUDE, DISTRIBUTE, OR MODIFY ANY ORIGINAL GAME ASSETS, INCLUDING BUT NOT LIMITED TO "
					      "EXECUTABLE FILES (.EXE, .DLL), IMAGES, OR AUDIO.\n\n"
					      "2. DATA ACCESS INTENT\n"
					      "This Software provides only the minimum necessary functions for modifying save data."
					      "This Software does NOT include any features for dynamically or intelligently "
						  "analyzing/probing file structures. This Software can only read and modify data at fixed offsets "
					      "according to pre-defined specifications. This Software EXCLUSIVELY modifies data files associated "
						  "with the user that contain in-game progress data, specifically matching the pattern 'userData.bin' "
						  "or 'userData[number].bin' (e.g., 'userData2.bin', 'userData10.bin'). This Software does NOT access "
						  "any copyrightable game assets, including but not limited to executable files and resource container files.\n\n"
					      "3. NO COPYRIGHT INFRINGEMENT INTENT\n"
					      "THE ENCRYPTION / DECRYPTION LOGIC IS INTENDED SOLELY FOR ALLOWING USERS TO ACCESS THEIR OWN PROGRESS DATA, "
					      "SPECIFICALLY 'userData.bin' AND ANY NUMBERED VARIATIONS THEREOF, AS DEFINED IN THE 'DATA ACCESS INTENT' "
					      "SECTION OF THE DISCLAIMER. IT IS NOT DESIGNED TO, NOR DOES IT FACILITATE, COPYRIGHT INFRINGEMENT OR SOFTWARE PIRACY.\n\n";

