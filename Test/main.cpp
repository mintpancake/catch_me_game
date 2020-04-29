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
#include <iomanip>
#include <fstream>
#include <string>
#include <vector>
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
#include "main.h"
#include "welcome.h"
#include "menu.h"
#include "keyboard.h"

using namespace std;

Word *word = new Word{0, "", ""};
Player_line *player_line = new Player_line{"", 25};
Fall *fall = new Fall(WIDTH, HEIGHT - 1);
Timer *timer = new Timer(100);
Status *status = new Status();
int level = 1;
int leftTime = 0;
string playerName;

int main()
{
    welcome();
    std::cout << "\n\n";
    print_option("Welcome!", false);
    print_option("Please tell me your nickname: ", false);
    std::cout << string(21, ' ');
    std::cin >> playerName;
    while (1)
    {
#ifdef LINUX
        setBufferedInput(false);
#endif
        int choice = menu();
        if (choice == 0)
        {
            while (level <= 10)
            {
                destroy();
                init();
                thread t_game(game);
                t_game.detach();

                thread t_player(player);
                t_player.detach();

                thread t_timer(tick);
                t_timer.join();

                if (status->won)
                {
                    std::cout << endl;
                    std::cout << "Congratulations! You guessed right!" << endl;
                    std::cout << "The word is \"" << word->target << "\". " << endl;
                    std::cout << "Your remaining time is " << timer->countdown << " second(s). " << endl;
                    std::cout << "You level is " << level << ". " << endl;
                    std::cout << endl;
                    if (level == 10)
                    {
                        std::cout << "Unbelievable! You did it, " << playerName << "!" << endl;
                        std::cout << "Your great performance is recorded in the leaderboard!" << endl;
                        record(playerName, timer->countdown);
                        std::cout << endl;
#ifdef LINUX
                        std::cout << "Back to menu? (double tap q)" << endl;
#else
                        std::cout << "Back to menu? (q)" << endl;
#endif
                        int key = getkey();
                        while (key != QUIT)
                        {
                            key = getkey();
                            this_thread::sleep_for(chrono::milliseconds(100));
                        }
                        break;
                    }
                    else
                    {
                        std::cout << "Please prepare for the next level, " << playerName << "!" << endl;
                        std::cout << endl;
#ifdef LINUX
                        std::cout << "Back to menu? (double tap y)" << endl;
#else
                        std::cout << "Back to menu? (y)" << endl;
#endif
                        int key = ERR;
                        while (key != YES)
                        {
                            key = getkey();
                            this_thread::sleep_for(chrono::milliseconds(100));
                        }
                        leftTime = timer->countdown;
                        level++;
                        continue;
                    }
                }
                else if (status->time_up)
                {
                    std::cout << endl;
                    std::cout << "Sorry! Time's up!" << endl;
                    std::cout << "The word is \"" << word->target << "\". " << endl;
                    std::cout << "You level is " << level << ". " << endl;
                    std::cout << endl;
                    if (level == 1 || level == 2 || level == 3)
                    {
                        std::cout << "To be honest, your performance is not good, " << playerName << "." << endl;
                    }
                    else if (level == 4 || level == 5 || level == 6)
                    {
                        std::cout << "This is a good try, " << playerName << ". "
                                  << "Keep it up!" << endl;
                    }
                    else if (level == 7 || level == 8 || level == 9)
                    {
                        std::cout << "Good job, " << playerName << ". "
                                  << "You are close to success!" << endl;
                    }
                    if (level == 10)
                    {
                        std::cout
                            << "Excellent! You are only one step away from success, " << playerName << "." << endl;
                    }

                    std::cout << "Your performance is recorded in the leaderboard!" << endl;
                    record(playerName, timer->countdown);
                    std::cout << endl;
#ifdef LINUX
                    std::cout << "Back to menu? (double tap q)" << endl;
#else
                    std::cout << "Back to menu? (q)" << endl;
#endif
                    int key = ERR;
                    while (key != QUIT)
                    {
                        key = getkey();
                        this_thread::sleep_for(chrono::milliseconds(100));
                    }
                    break;
                }
            }
        }
        else if (choice == 1)
        {
#ifdef LINUX
            std::system("clear");
#else
            std::system("cls");
#endif
            //to be implemented
            std::cout << endl;
            std::cout << "Back to menu? (q)" << endl;
            int key = getkey();
            while (key != QUIT)
            {
                key = getkey();
                this_thread::sleep_for(chrono::milliseconds(100));
            }
            continue;
        }
        else if (choice == 2)
        {
#ifdef LINUX
            std::system("clear");
#else
            std::system("cls");
#endif
            //to be implemented
            std::cout << endl;
            std::cout << "Back to menu? (q)" << endl;
            int key = getkey();
            while (key != QUIT)
            {
                key = getkey();
                this_thread::sleep_for(chrono::milliseconds(100));
            }
            continue;
        }
        else if (choice == 3)
        {
#ifdef LINUX
            std::system("clear");
#else
            std::system("cls");
#endif
            std::cout << endl;
            print_option("Developers:", false);
            std::cout << endl;
            print_option("Chen Xueqing", false);
            print_option("Lu Meng", false);
            std::cout << endl;
            print_option("2020 The University of Hong Kong", false);
            std::cout << endl;
            std::cout << "Back to menu? (q)" << endl;
            int key = getkey();
            while (key != QUIT)
            {
                key = getkey();
                this_thread::sleep_for(chrono::milliseconds(100));
            }
            continue;
        }
        else if (choice == 4)
        {
#ifdef LINUX
            std::system("clear");
#else
            std::system("cls");
#endif
            std::cout << "Thank you, " << playerName << "!" << endl;
            std::cout << "Byebye!" << endl;
            break;
        }
        else
        {
            continue;
        }
#ifdef LINUX
        setBufferedInput(true);
#endif
    }

    destroy();
#ifdef LINUX
    setBufferedInput(true);
#endif
#ifndef LINUX
    std::system("pause");
#endif
    return 0;
}

void game()
{
    srand(time(NULL));
    while (!status->end)
    {
        update();
        fall->push(rand_str(fall->col));
        print();
        judge();
        this_thread::sleep_for(chrono::milliseconds(500));
    }
    return;
}

void player()
{
    while (!status->end)
    {
        int key = getkey();
        if (key == LEFT && player_line->index > 1) //left
        {
            player_line->update(-1);
        }
        else if (key == RIGHT && player_line->index < fall->col - 2) //right
        {
            player_line->update(1);
        }
        else
        {
            this_thread::sleep_for(chrono::milliseconds(20));
            continue;
        }
        print();
        this_thread::sleep_for(chrono::milliseconds(20));
    }
}

void tick()
{
    while (!status->end)
    {
        if (timer->countdown > 0)
        {
            timer->countdown--;
        }
        else
        {
            status->time_up = true;
        }
        this_thread::sleep_for(chrono::milliseconds(1000));
    }
}

void init()
{
    srand(time(NULL));
    word = new Word{0, "", ""};
    player_line = new Player_line{"", 25};
    fall = new Fall(WIDTH, HEIGHT - 1);
    timer = new Timer(100 + leftTime);
    status = new Status();
    if (playerName == "Debug")
    {
        word->init("testestest");
    }
    else
    {
        word->init(word_list[(rand() % 10) + (level - 1) * 10]);
    }
    word->reveal((word->target)[rand() % (word->target).length()]);
    player_line->init(fall->col);
}

string rand_str(int l)
{
    string s;
    for (int i = 0; i < l; i++)
    {
        char c = ' ';
        int p = rand() % 1000;
        if (p < DENSITY)
        {
            c = char(rand() % 26 + 97);
            while ((word->display).find(c) != string::npos)
            {
                c = char(rand() % 26 + 97);
            }
        }
        s += c;
    }
    return s;
}

void print()
{
#ifdef LINUX
    std::system("clear");
#else
    std::system("cls");
#endif

    for (vector<string>::iterator it = (fall->display).end() - 1; it != (fall->display).begin() - 1; it--)
    {
        if (it == (fall->display).end() - 2)
        {
            std::cout << *it;
            timer->print();
            if (timer->deducted)
            {
                std::cout << "-3";
                timer->deducted = false;
            }
            std::cout << endl;
        }
        else if (it == (fall->display).end() - 1)
        {
            std::cout << *it;
            std::cout << "    LEVEL: " << level << endl;
        }
        else
        {
            std::cout << *it << endl;
        }
    }

    player_line->print();
    std::cout << endl;
    std::cout << "TARGET: ";
    word->print();
    std::cout << endl;
}

int update_word(char c)
{
    if (c == ' ')
    {
        return BLANK;
    }
    else if ((word->target).find(c) != string::npos)
    {
        word->reveal(c);
        return CORRECT;
    }
    else
    {
        return WRONG;
    }
}

void update()
{
    bool recover = true;
    int left = update_word((fall->display)[0][player_line->index - 1]);
    int mid = update_word((fall->display)[0][player_line->index]);
    int right = update_word((fall->display)[0][player_line->index + 1]);
    if (left == CORRECT || mid == CORRECT || right == CORRECT)
    {
        player_line->fill_bucket(1);
        recover = false;
    }
    if (left == WRONG || mid == WRONG || right == WRONG)
    {
        player_line->fill_bucket(-1);
        timer->countdown -= 3;
        timer->deducted = true;
        recover = false;
    }
    if (recover)
    {
        player_line->fill_bucket(0);
    }
}

void judge()
{
    status->won = (word->target == word->display);
    if (status->won || status->time_up)
    {
        status->end = true;
    }
}

void destroy()
{
    if (word != NULL)
    {
        delete word;
        word = NULL;
    }
    if (player_line != NULL)
    {
        delete player_line;
        player_line = NULL;
    }
    if (fall != NULL)
    {
        delete fall;
        fall = NULL;
    }
    if (timer != NULL)
    {
        delete timer;
        timer = NULL;
    }
    if (status != NULL)
    {
        delete status;
        status = NULL;
    }
}

void record(string playerName, int time)
{
    vector<string> oldRecords;
    string s;
    ifstream fin;
    fin.open("leaderboard.txt");
    while (getline(fin, s))
    {
        oldRecords.push_back(s.substr(10));
    }
    int size = oldRecords.size();
    int i = 0;
    while (i < size)
    {
        if (atoi(oldRecords[i].substr(10).c_str()) >= time)
        {
            continue;
        }
        else
        {
            break;
        }
        i++;
    }
    ofstream fout;
    fout.open("leaderboard.txt");
    for (int j = 0; j < i; j++)
    {
        fout << left << setw(10) << j << oldRecords[j] << endl;
    }
    fout << left << setw(10) << i << setw(10) << playerName << setw(10) << time << endl;
    for (int j = i + 1; j <= size; j++)
    {
        fout << left << setw(10) << j << oldRecords[j - 1] << endl;
    }

    fin.close();
    fout.close();
}
