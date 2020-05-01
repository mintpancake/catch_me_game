/****************************************************************************
 *  Copyright (C) 2020 Lu Meng and Chen Xueqing.
 *
 *  This program is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of 
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program. If not, see <http://www.gnu.org/licenses/>.
 ***************************************************************************/

/** @file menu.cpp
 *  @version 1.0
 *  @date May 2018
 *
 */

#include <iostream>
#include <string>
#include <thread>
#include <chrono>
#include <future>
#include <utility>
#include <cstdlib>
#include <cstdio>
#include <cmath>
#include <ctime>
#include <cstdint>
#include <csignal>
#include <unistd.h>

#include "switch.h"
#include "menu.h"
#include "keyboard.h"

using namespace std;

const string options[6] = {"Start", "Instruction", "Leaderboard", "About", "Quit", "[up/down to select | e to enter]"};

/**
  * @brief  print one line of option
  * @param  str the content of the option
  *         at whether the focus is on this option
  * @retval void
  */
void print_option(string str, bool at)
{
    char fill = ' ';
    if (at)
    {
        fill = '-';
    }
    int front_sep, back_sep;
    if ((LENGTH - str.length()) % 2 == 1)
    {
        front_sep = (LENGTH - str.length()) / 2;
        back_sep = (LENGTH - str.length()) / 2 + 1;
    }
    else
    {
        front_sep = (LENGTH - str.length()) / 2;
        back_sep = (LENGTH - str.length()) / 2;
    }
    cout << string(front_sep, fill) << str << string(back_sep, fill) << endl;
}

/**
  * @brief  print the whole menu
  * @param  now_at which option the focus is on
  * @retval void
  */
void print_menu(int now_at)
{
#ifdef LINUX
    std::system("clear");
#else
    std::system("cls");
#endif
    cout << endl;
    for (int i = 0; i < 6; i++)
    {
        bool at = (i == now_at);
        print_option(options[i], at);
    }
}

/**
  * @brief  print the menu and get the player's keyboard input
  * @param  void
  * @retval the option which the player chooses
  */
int menu()
{
    int now_at = 0;
    print_menu(now_at);
    while (1)
    {
        int key = getkey();
        if (key == UP && now_at > 0) //up
        {
            now_at--;
        }
        else if (key == DOWN && now_at < 4) //down
        {
            now_at++;
        }
        else if (key == E)
        {
            return now_at;
        }
        else
        {
            this_thread::sleep_for(chrono::milliseconds(100));
            continue;
        }
        print_menu(now_at);
        this_thread::sleep_for(chrono::milliseconds(100));
    }
}