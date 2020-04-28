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
