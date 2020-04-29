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

#include <iostream>
#include <cstdlib>
#include <cstdio>
#include <cmath>
#include <ctime>
#include <cstdint>
#include <csignal>
#include <unistd.h>

#include "switch.h"
#include "keyboard.h"

#ifdef LINUX
#include <termios.h>

void setBufferedInput(bool enable)
{
    static bool enabled = true;
    static struct termios old;
    struct termios neo;
    if (enable && !enabled)
    {
        // restore the former settings
        tcsetattr(STDIN_FILENO, TCSANOW, &old);
        // set the new state
        enabled = true;
    }
    else if (!enable && enabled)
    {
        // get the terminal settings for standard input
        tcgetattr(STDIN_FILENO, &neo);
        // we want to keep the old setting to restore them at the end
        old = neo;
        // disable canonical mode (buffered i/o) and local echo
        neo.c_lflag &= (~ICANON & ~ECHO);
        // set the new settings immediately
        tcsetattr(STDIN_FILENO, TCSANOW, &neo);
        // set the new state
        enabled = false;
    }
}

int getkey()
{
    int ch1 = -1, ch2 = -1, ch3 = -1;
    ch1 = getchar();
    if (ch1 == 27)
    {
        ch2 = getchar();
        if (ch2 == 91)
        {
            ch3 = getchar();
            if (ch3 == 65) //up
            {
                return UP;
            }
            else if (ch3 == 66) //down
            {
                return DOWN;
            }
            else if (ch3 == 68) //left
            {
                return LEFT;
            }
            else if (ch3 == 67) //right
            {
                return RIGHT;
            }
            else
            {
                return ERR;
            }
        }
        else
        {
            return ERR;
        }
    }
    else if (ch1 == 10) //enter
    {
        return ENTER;
    }
    else if (ch1 == 101)
    {
        return E;
    }
    else if (ch1 == 121)
    {
        return YES;
    }
    else if (ch1 == 113)
    {
        return QUIT;
    }
    else
    {
        return ERR;
    }
    return ERR;
}

#else
#include <windows.h>
#include <conio.h>

void setBufferedInput(bool enable) {}

int getkey()
{
    int ch1 = -1, ch2 = -1;
    if (_kbhit())
    {
        ch1 = _getch();
        if (ch1 == 224)
        {
            ch2 = _getch();
            if (ch2 == 72) //up
            {
                return UP;
            }
            else if (ch2 == 80) //down
            {
                return DOWN;
            }
            else if (ch2 == 75) //left
            {
                return LEFT;
            }
            else if (ch2 == 77) //right
            {
                return RIGHT;
            }
            else
            {
                return ERR;
            }
        }
        else if (ch1 == 13) //enter
        {
            return ENTER;
        }
        else if (ch1 == 101)
        {
            return E;
        }
        else if (ch1 == 121)
        {
            return YES;
        }
        else if (ch1 == 113)
        {
            return QUIT;
        }
        else
        {
            return ERR;
        }
    }
    return ERR;
}
#endif
