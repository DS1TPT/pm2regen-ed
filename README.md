pm2regen-ed
============
※ 한국어 설명서 -> [바로가기](https://github.com/DS1TPT/pm2regen-ed/blob/main/README_KOREAN.md)   
pm2regen-ed is a very tiny and simple cross-platform TUI(Text-based User Interface) save editor for Princess Maker 2 Regeneraion.   
   
pm2regen-ed is a tool for enhancing gaming experience by enabling players to collect endings easier and faster instead of spending enormous amount of time, fixing broken statistics due to bug of the game, or play the game in unusual ways(for example, starting with massive amount of money from beginning instead of puny 500 golds).   
pm2regen-ed can edit the following statistics:  
1. 8 Basic statistics including Stamina, Strength, etc.
2. Stress and Money
3. 4 Reputation statistics
4. Skill statistics
5. Hidden statistics(Maternal Instinct, Relationship with Prince/Father/Butler(Cube), Monsters Killed)
6. Renown
7. Measurements(Height, Weight, BWH)
   
This software contains tiny-AES-c by kokke @ Github. You can obtain source code and information from: https://github.com/kokke/tiny-AES-c/   
   
Requirements
------------
- POSIX-compliant OS(Linux, BSD, macOS ...) or Windows 10 Version 1511 and later
- Terminal emulator that supports ANSI VT standard(Modern Operating Systems already have them installed out of the box)

Usage
------
1. Pre-built binary is available in Releases page. Download compressed file with your preferred default language setting. De-compress the file, place executable and launcher in save folder of PM2 Regeneration and run from it to edit your save(s).   
2. Place executable and Launcher in save directory. Saves are typically located at the following directory:
```
Windows: %localappdata%\BrisBrain\PM2\Saved\SaveGames\<Some numbers>
Linux: ~/.steam/steam/steamapps/compatdata/2311530/pfx/drive_c/users/steamuser/AppData/Local/BrisBrain/PM2/Saved/SaveGames/<Some numbers>
```
3. Double-click the launcher(Linux) or executable(Windows) to run pm2regen-ed.   
CAUTION: Do NOT double click executable itself if you are using Linux. It will make it run in background without having any terminal attached to it. Instead, run it using launcher desktop entry.
```
Windows: Double click pm2regen-ed.exe to run.   
Linux: Double click "Launch pm2regen-ed"(Desktop entry. This must be in the same directory as pm2regen-ed) to run.
```
   
To run this software on terminal:
```
On Linux:   ./pm2regen-ed <language>
On Windows: pm2regen-ed <language> (On Command Prompt)
            .\pm2regen-ed <language> (Powershell)

/* To edit without selector menu on terminal */
On Linux:   ./pm2regen-ed <language> <save number>
On Windows: pm2regen-ed <language> <save number> (On Command Prompt)
            .\pm2regen-ed <language> <save number> (On Powershell)
```
If argument is not given(including double-clicking the executable), or language is the only given argument, file selector menu will show up.
Available languages: en(English), kr(Korean), jp(Japanese)   
If language argument is not given(i.e. ./pm2regen-ed 2), this program will display default language set on build-time and load userData<number>.bin without launching file selector.   
If pm2regen-ed successfully load the save file, it will create back-up file named userData<number>_bak.bin . Be aware, this program will overwrite the backup file each time it loads a save file with same <number>, so be sure to move/rename that if you are planning to edit another save file with same number!   
   
Note: If <number> argument is 1, pm2regen-ed will load "userData.bin". This is an intended behavior, since the Princess Maker 2 Regeneration names its first save as "userData.bin", NOT "userData1.bin".   
   
Building
---------
Pre-built executables for Windows and Linux are available in Releases page.   
If you are going to build pm2regen-ed from scratch, download this repository by:   
```
git clone --recursive https://github.com/DS1TPT/pm2regen-ed.git
```
After you've finished downloading, move to (root directory of pm2regen-ed)/build directory, and build using CMake. Example of building on Linux is as follows:   
```
cmake ..
make
```
You can also build pm2regen-ed without CMake. Move to the root directory pm2regen-ed and build using GCC with this one-liner:
```
gcc -I./inc -I./lib ./src/*.c ./lib/tinyAES/aes.c -o pm2regen-ed
```
This software will be built for POSIX-compliant OS if _WIN32 is not defined.   
To change this software's default language, edit line 27 of main.h.   
