# ENGG1340 Project

## Catch Me
***
## Team Members
Lu Meng             3035639379<br />
Chen Xueqing        3035638351
***
## How to Use
- For Windows
   1. Go to `switch.h`
   2. Undefine `LINUX`
   3. Compile using `g++ -pedantic-errors -std=c++11 welcome.cpp keyboard.cpp menu.cpp main.cpp -o main.exe`
   4. Run `main.exe`
- For Linux
   1. Go to `switch.h`
   2. Define `LINUX`
   3. Use command `make main`<br />Alternatively, compile using `g++ -pedantic-errors -std=c++11 welcome.cpp keyboard.cpp menu.cpp main.cpp -o main -lpthread`
   4. Run `main`
- For Mac OS
   - Oops! We don't support that. 
- Caution! This is a real-time game. It performs better when running locally. 
***
## Game Description
### Overall Description
The game is a word-guessing game with a countdown. 
### Detailed Gameplay
At first, the player will get an incomplete word with only part of its letters displayed, other hidden letters will be displayed as short dashes. The player needs to use a basket to catch letters falling from the top of the screen within a given time. 

If he/she catches the right letter, the letter will be revealed by replacing the corresponding dash. If he/she catches the wrong letter, the left time will be reduced. 

If the player fills the word within the given time, he/she can challenge the next level, and the left time will be added to the countdown of the next level. 

If time runs out before the word is filled, the game is over directly. 
### Ranking Method
After the game, the player will be credited to the leaderboard. The player who passes more levels with more time left will get a higher ranking.
***
## Planned Functions
### 1. Preparation
- Include macro definitions and function declarations stored in *.h ***5.Program codes in multiple files*** 

### 2. Initialization
- Output the greeting words and the menu to the screen
- Get the commands of the player as input
- Initialize all kinds of data
   - Initialize the basket which is controlled by the player
   - Initialize the letters falling from the top of the screen ***2.Data structures for storing game status***
   - Initialize the hidden words for this level ***1.Generation of random game sets or events***
   - Initialize the countdown for this level

### 3. Process with Judgement and Update
- Move the basket according to the player's operation
- Judge whether the player has caught the right letter
- Update the letters falling from the top of the screen ***3.Dynamic memory management***
- Update the word by revealing the hidden letter if the player has caught the right one
- Show the passage of time
- Display all updated data
- Judge whether the player has passes the game

### 4. Record of Result
- Record the performance of the player ***4.File input/output***

***

## Some Non-standard C/C++ Libraries
- `#include <windows.h>` `#include <conio.h>` Implement reading keyboard for Windows
- `#include <termios.h>` `#include <unistd.h>` Implement reading keyboard for Linux
