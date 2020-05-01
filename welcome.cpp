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

/** @file welcome.cpp
 *  @version 1.0
 *  @date May 2018
 *
 */

#include <iostream>
#include <string>
#include <thread>
#include <chrono>
#include <future>
#include <cstdlib>
#include <cstdio>
#include <cmath>
#include <ctime>

#include "switch.h"
#include "welcome.h"

using namespace std;

const std::string appear[8][6] = {{" @@@@@@@ ", "!@@      ", "!@!      ", "!@@      ", " @@@@@@@ ", ""},
                                  {" @@@@@@  ", "@@!  @@@ ", "@!@!@!@! ", "@@!  @@@ ", "@@@  @@@ ", ""},
                                  {"@@@@@@@ ", "  @@!   ", "  @@!   ", "  @@!   ", "  @@!   ", ""},
                                  {" @@@@@@@ ", "!@@      ", "!@!      ", "!@@      ", " @@@@@@@ ", ""},
                                  {"@@@  @@@ ", "@@!  @@@ ", "@!@!@!@! ", "@@!  @@@ ", "@@@  @@@ ", ""},
                                  {"     ", "     ", "     ", "     ", "     ", ""},
                                  {"@@@@@@@@@@  ", "@@! @@! @@! ", "@@! @@! @@! ", "@@! !!@ @@! ", "@@@     @!@ ", ""},
                                  {"@@@@@@@@ ", "@@!      ", "@@@@!@   ", "@@!      ", "@@@@@@@@ ", ""}};

const std::string disappear[8] = {" @@@@@@@  @@@@@@  @@@@@@@  @@@@@@@ @@@  @@@      @@@@@@@@@@  @@@@@@@@\n!@@      @@!  @@@   @@!   !@@      @@!  @@@      @@! @@! @@! @@!     \n!@!      @!@!@!@!   @@!   !@!      @!@!@!@!      @@! @@! @@! @@@@!@  \n!@@      @@!  @@@   @@!   !@@      @@!  @@@      @@! !!@ @@! @@!     \n @@@@@@@ @@@  @@@   @@!    @@@@@@@ @@@  @@@      @@@     @!@ @@@@@@@@",
                                  " @@@@@@@  @@@@@@  @@@@@@@  @@@@@@@ @@@  @@@      @@@@@@@@@@  @@@@@@@@\n!@@      @@!  @@@   @@!   !@@      @@!  @@@      @@! @@! @@! @@!     \n!@!      @!@!@!@!   @@!   !@!      @!@!@!@!      @@! @@! @@! @@@@!@  \n!@@      @@!  @@@   @@!   !@@      @@!  @@@      @@! !!@ @@! @@!     \n !!@!!@! !!@  !!@   !!!    !!@!!@! !!@  !!@      !!@     !!! !!@!!@!!",
                                  " @@@@@@@  @@@@@@  @@@@@@@  @@@@@@@ @@@  @@@      @@@@@@@@@@  @@@@@@@@\n!@@      @@!  @@@   @@!   !@@      @@!  @@@      @@! @@! @@! @@!     \n!@!      @!@!@!@!   @@!   !@!      @!@!@!@!      @@! @@! @@! @@@@!@  \n!::      @::  :@:   @!!   ::!      @!:  @:!      @@! ::  @!: @!:     \n !!: ::! :!:  !::   !::    : !:: : ::   !::      !::     !:: ! :: !::",
                                  " @@@@@@@  @@@@@@  @@@@@@@  @@@@@@@ @@@  @@@      @@@@@@@@@@  @@@@@@@@\n!@@      @@!  @@@   @@!   !@@      @@!  @@@      @@! @@! @@! @@!     \n!@!      @!@!@!@!   @!!   !@!      @!@!@!@!      @!! !!@ @!@ @!!!:!  \n:!!      !!:  !!!   !!:   :!!      !!:  !!!      !!:     !!: !!:     \n :: :: :  :   : :    :     :: :: :  :   : :       :      :   : :: :::",
                                  " @@@@@@@  @@@@@@  @@@@@@@  @@@@@@@ @@@  @@@      @@@@@@@@@@  @@@@@@@@\n!!@      !@!  @!@   @@!   !!@      @!:  @!@      !@! !:! !@! @!!     \n!::      !@::!!:!   @!!   !::      @:!!: !:      !:  !:  :!: !::!:!  \n :       ::   !::   : :   !:       ::   !::      :         : :!      \n  :  :          :          :  :         :         :            :   : ",
                                  " !@!@!@@  @!@@!@  @!!@@!@  !@!@!@@ @!@  @!!      @@!@@!!@@@  @@!!@@!@\n!::      :!:  :!@   :!!   !::      !::  @!:      !:! : : :!: !::     \n::       ! :! ::!   !:    : :      :  !!: !      :       : : :  : :  \n          :     :   :      :        :    ::      :           :       \n                                                                     ",
                                  " : :: ::  : ! !:  : !  :!  !:  :   ::!  : :      !:: :  :::  ! :  ::!\n:             :     ::               :               :   :     :     \n                                                                     \n                                                                     \n                                                                     ",
                                  " :    :!  :       :     !:      :    :     :     :   :         :  : !\n                                                                     \n                                                                     \n                                                                     \n                                                                     "};

/**
  * @brief  print the welcome animation
  * @param  void
  * @retval void
  */
void welcome()
{
    bool *complete = new bool[8]();
    for (int i = 1; i < 13; i++)
    {
#ifdef LINUX
        std::system("clear");
#else
        std::system("cls");
#endif
        for (int j = 0; j < ((i > 5) ? 5 : i); j++)
        {
            for (int k = 0; k < 8; k++)
            {
                int n = 5 - i + j + k;
                n = n > 4 ? 5 : n;
                if (n < 0)
                {
                    complete[k] = true;
                }
                if (!complete[k])
                {
                    cout << appear[k][n];
                }
                else
                {
                    cout << appear[k][j];
                }
            }
            cout << endl;
        }
        this_thread::sleep_for(chrono::milliseconds(200));
    }
    delete complete;
    complete = NULL;
    this_thread::sleep_for(chrono::milliseconds(1000));
    for (int i = 0; i < 8; i++)
    {
#ifdef LINUX
        std::system("clear");
#else
        std::system("cls");
#endif
        cout << disappear[i] << endl;
        this_thread::sleep_for(chrono::milliseconds(200));
    }
#ifdef LINUX
    std::system("clear");
#else
    std::system("cls");
#endif
    return;
}
