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

/** @file main.cpp
 *  @version 1.0
 *  @date May 2020
 *
 */

#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
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

Word *word = NULL;
Player_line *player_line = NULL;
Fall *fall = NULL;
Timer *timer = NULL;
Status *status = NULL;
int level;
int leftTime;
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
            level = 1;
            leftTime = 0;
            while (level <= 10)
            {
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
                    std::cout << "Your current level is " << level << ". " << endl;
                    std::cout << endl;
                    if (level == 10)
                    {
                        std::cout << "Unbelievable! You did it, " << playerName << "!" << endl;
                        std::cout << "Your great performance is recorded in the leaderboard!" << endl;
                        record(playerName, level, timer->countdown);
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
                        std::cout << "Ready? (double tap y)" << endl;
#else
                        std::cout << "Ready? (y)" << endl;
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
                    std::cout << "Oops! Time's up!" << endl;
                    std::cout << "The word is \"" << word->target << "\". " << endl;
                    std::cout << "Your final level is " << level << ". " << endl;
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

                    std::cout << "Your performance has been recorded in the leaderboard!" << endl;
                    record(playerName, level, timer->countdown);
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
        else if (choice == 1) //instruction
        {
#ifdef LINUX
            std::system("clear");
#else
            std::system("cls");
#endif
            std::cout << "At  first,  you  will  get an incomplete word with" << endl;
            std::cout << "only  part  of its letters displayed, other hidden" << endl;
            std::cout << "letters will be displayed as short dashes." << endl;
            std::cout << endl;
            std::cout << "You  need to use a basket to catch letters falling" << endl;
            std::cout << "from the top of the screen within a given time." << endl;
            std::cout << endl;
            std::cout << "If  you catch the right letter, the letter will be" << endl;
            std::cout << "revealed  by  replacing the corresponding dash." << endl;
            std::cout << "If  you catch the wrong letter, the left time will" << endl;
            std::cout << "be reduced." << endl;
            std::cout << endl;
            std::cout << "If  you  fill  the word within the given time, you" << endl;
            std::cout << "can  challenge  the  next level, and the left time" << endl;
            std::cout << "will be added to the countdown of the next level." << endl;
            std::cout << "If  time  runs  out before the word is filled, the" << endl;
            std::cout << "game will be over directly." << endl;
            std::cout << endl;
            std::cout << "After  the  game,  you  will  be  credited  to the" << endl;
            std::cout << "leaderboard.  The  player  who  passes more levels" << endl;
            std::cout << "with more time left will get a higher ranking." << endl;
            std::cout << endl;
            std::cout << "Good luck, " << playerName << "!" << endl;
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
        else if (choice == 2) //show leaderboard
        {
#ifdef LINUX
            std::system("clear");
#else
            std::system("cls");
#endif
            std::cout << left << setw(10) << "No." << setw(10) << "Name" << setw(10) << "Level" << setw(10) << "Time" << endl;
            ifstream fin_to_show;
            string s1;
            int order = 1;
            fin_to_show.open("leaderboard.txt");
            if (fin_to_show.fail())
            {
                cout << "---------------None---------------" << endl;
            }
            else
            {
                while (getline(fin_to_show, s1))
                {
                    std::cout << left << setw(10) << order;
                    std::cout << s1 << endl;
                    order++;
                }
            }
            fin_to_show.close();
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

/**
  * @brief  a thread to execute game
  * @param  void
  * @retval void
  */
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

/**
  * @brief  a thread to handle input from player
  * @param  void
  * @retval void
  */
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

/**
  * @brief  a thread to count time
  * @param  void
  * @retval void
  */
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

/**
  * @brief  initialize game parameters
  * @param  void
  * @retval void
  */
void init()
{
    destroy();
    srand(time(NULL));
    word = new Word{0, "", ""};
    player_line = new Player_line{"", 25};
    fall = new Fall(WIDTH, HEIGHT - 1);
    timer = new Timer(90 + leftTime);
    status = new Status();
    if (playerName == "Debug") //cheat
    {
        word->init("testestest", "testestest");
    }
    else
    {
        int index = (rand() % 10) + (level - 1) * 10;
        word->init(word_list[index], tip_list[index]);
    }
    int num_of_reveal = word->target.length() / 3;
    vector<int> index_of_reveal;
    while (index_of_reveal.size() < num_of_reveal)
    {
        int random_choice = rand() % word->target.length();
        bool exist = false;
        for (int i = 0; i < index_of_reveal.size(); i++)
        {
            if (random_choice == index_of_reveal[i])
            {
                exist = true;
            }
        }
        if (!exist)
        {
            index_of_reveal.push_back(random_choice);
        }
    }
    for (int i = 0; i < index_of_reveal.size(); i++)
    {
        word->reveal((word->target)[index_of_reveal[i]]);
    }
    player_line->init(fall->col);
}

/**
  * @brief  generate a random line of characters for fall
  * @param  l the length of line
  * @retval the string of the line
  */
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

/**
  * @brief  print the fall
  * @param  void
  * @retval void
  */
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

/**
  * @brief  judge whether a character is in the target word or whether it is a space
  * @param  c the input character
  * @retval RIGHT in the target word
  *         WRONG not in the target word
  *         BLANK a space
  */
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

/**
  * @brief  execute countdown deduction and change of basket display according to whether the basket catches a charater
  * @param  void
  * @retval void
  */
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
        if (timer->countdown - 3 < 0)
        {
            timer->countdown = 0;
        }
        else
        {
            timer->countdown -= 3;
        }
        timer->deducted = true;
        recover = false;
    }
    if (recover)
    {
        player_line->fill_bucket(0);
    }
}

/**
  * @brief  judge and change game status
  * @param  void
  * @retval void
  */
void judge()
{
    status->won = (word->target == word->display);
    if (status->won || status->time_up)
    {
        status->end = true;
    }
}

/**
  * @brief  free the memory of game parameters
  * @param  void
  * @retval void
  */
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

/**
  * @brief  record the player's performance into the leaderboard
  * @param  playerName the player's name
  *         level the final level
  *         time the remaining time
  * @retval void
  */
void record(string playerName, int level, int time)
{
    vector<string> oldRecords;
    string s;
    ifstream fin;
    if (time < 0)
    {
        time = 0;
    }
    int i = 0;
    fin.open("leaderboard.txt");
    if (fin.fail())
    {
    }
    else
    {
        while (getline(fin, s))
        {
            oldRecords.push_back(s);
        }

        while (i < oldRecords.size())
        {
            if (atoi(oldRecords[i].substr(10, 10).c_str()) >= level && atoi(oldRecords[i].substr(20, 10).c_str()) >= time)
            {
                if (atoi(oldRecords[i].substr(10, 10).c_str()) == level && atoi(oldRecords[i].substr(20, 10).c_str()) == time && oldRecords[i].substr(0, 10) > playerName)
                {
                    break;
                }
                else
                {
                    i++;
                }
            }
            else
            {
                break;
            }
        }
    }
    fin.close();
    ofstream fout;
    fout.open("leaderboard.txt");
    for (int j = 0; j < i; j++)
    {
        fout << oldRecords[j] << endl;
    }
    if (time == 0)
    {
        if (level == 10)
        {
            fout << left << setw(10) << playerName << setw(10) << level << setw(10) << "0" << endl;
        }
        else
        {
            fout << left << setw(10) << playerName << setw(10) << level << setw(10) << "-" << endl;
        }
    }
    else
    {
        fout << left << setw(10) << playerName << setw(10) << level << setw(10) << time << endl;
    }
    for (int j = i + 1; j <= oldRecords.size(); j++)
    {
        fout << oldRecords[j - 1] << endl;
    }
    fout.close();
}
