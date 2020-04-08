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
#include <string>
#include <vector>
#include <thread>
#include <chrono>
#include <future>
#include <cstdlib>
#include <cstdio>
#include <cmath>
#include <ctime>
#include <cstdint>
#include <csignal>
#include <unistd.h>

#include "game_app.h"

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
#else
#include <windows.h>
#include <conio.h>
#endif

using namespace std;

void game();
void player();
void timer();
void init_player_line(string &player_line);
void init_vector(vector<string> *v, int l);
void init_word();
void init();
string rand_str(int l);
void push_vector(vector<string> *v);
void print_timer();
void print_vector(vector<string> v, int l);
void print_player_line();
void print_word();
void print(vector<string> v, int l);
void update_player_line(int dir);
void reveal(char c);
char update_word(char c);
bool update();
void fill_bucket(int m);
void judge();

const int LIST_LENGTH = 10;
const string word_list[LIST_LENGTH] = {"engineering", "hangman", "brainstorm", "random", "envelope", "interface", "iceberg", "humour", "lemon", "commander"};
int word_length = 0;
string target_word = "";
string concealed_word = "";

string player_line = "";
int player_line_idx = 25;
vector<string> v;

int countdown = 100;

bool won = false;

int main()
{
    int start;
    cout << "Press any key and enter to start..." << endl;
    cin >> start;
    srand(time(NULL));
    init();
#ifdef LINUX
    setBufferedInput(false);
#endif
    thread t_game(game);
    t_game.detach();
    thread t_player(player);
    t_player.detach();
    thread t_timer(timer);
    t_timer.join();
    if (won)
    {
#ifdef LINUX
        setBufferedInput(true);
#endif
        cout << "Congratulations! You won!" << endl;
        cout << "The word is \"" << target_word << "\"" << endl;
    }
#ifndef LINUX
    system("pause");
#endif
    return 0;
}

void game()
{
    bool caught = false;
    while (!won)
    {
        caught = update();
        if (caught)
        {
            fill_bucket(1);
        }
        else
        {
            fill_bucket(0);
        }
        push_vector(&v);
        print(v, ROW);
        judge();
        this_thread::sleep_for(chrono::milliseconds(500));
    }
    return;
}

void player()
{
#ifdef LINUX
    int ch1, ch2, ch3;
    while (!won)
    {
        ch1 = -1;
        ch2 = -1;
        ch3 = -1;
        ch1 = getchar();
        if (ch1 != 27)
        {
            goto sleep;
        }
        ch2 = getchar();
        if (ch2 != 91)
        {
            goto sleep;
        }
        ch3 = getchar();
        if (ch3 == 68 && player_line_idx > 1) //left
        {
            update_player_line(-1);
        }
        else if (ch3 == 67 && player_line_idx < COL - 2) //right
        {
            update_player_line(1);
        }
        print(v, ROW);
    sleep:
        this_thread::sleep_for(chrono::milliseconds(20));
    }
    return;
#else
    int ch1, ch2;
    while (!won)
    {
        ch1 = -1;
        ch2 = -1;
        if (_kbhit())
        {
            ch1 = _getch();
            if (ch1 != 224)
            {
                goto sleep;
            }
            ch2 = _getch();
            if (ch2 == 75 && player_line_idx > 1) //left
            {
                update_player_line(-1);
            }
            else if (ch2 == 77 && player_line_idx < COL - 2) //right
            {
                update_player_line(1);
            }
            print(v, ROW);
        }
    sleep:
        this_thread::sleep_for(chrono::milliseconds(20));
    }
    return;
#endif
}

void timer()
{
    static int period = 1000;
    while (!won)
    {
        countdown--;
        /*period *= 0.9;
        if (period < 250)
        {
            period = 250;
        }
        print(v, ROW);*/
        this_thread::sleep_for(chrono::milliseconds(period));
    }
}

void init_player_line(string &player_line)
{
    player_line = string((COL - 3) / 2, ' ') + "\\_/" + string((COL - 3) / 2, ' ');
}

void init_vector(vector<string> *v, int l)
{
    for (int i = 0; i < l; i++)
    {
        v->push_back("");
    }
}

void init_word()
{
    int idx = rand() % LIST_LENGTH;
    target_word = word_list[idx];
    word_length = target_word.length();
    concealed_word = string(word_length, '-');
}

void init()
{
    init_word();
    init_player_line(player_line);
    init_vector(&v, ROW);
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
            while (concealed_word.find(c) != string::npos)
            {
                c = char(rand() % 26 + 97);
            }
        }
        s += c;
    }
    return s;
}

void push_vector(vector<string> *v)
{
    v->erase(v->begin());
    v->push_back(rand_str(COL));
}

void print_timer()
{
    cout << "COUNTDOWN: " << countdown;
}

void print_vector(vector<string> v, int l)
{
    for (vector<string>::iterator it = v.end() - 1; it != v.begin() - 1; it--)
    {
        if (it == v.end() - 1)
        {
            cout << *it << " ";
            print_timer();
            cout << endl;
        }
        else
        {
            cout << *it << endl;
        }
    }
}

void print_player_line()
{
    cout << player_line << endl;
}

void print_word()
{
    cout << concealed_word << endl;
}

void print(vector<string> v, int l)
{
#ifdef LINUX
    system("clear");
#else
    system("cls");
#endif
    print_vector(v, l);
    print_player_line();
    cout << endl;
    print_word();
}

void update_player_line(int dir)
{
    if (dir == -1)
    {
        player_line = player_line.substr(1) + ' ';
        player_line_idx--;
    }
    if (dir == 1)
    {
        player_line = ' ' + player_line.substr(0, player_line.size() - 1);
        player_line_idx++;
    }
}

void reveal(char c)
{
    int last_pos = target_word.find(c);
    while (last_pos != string::npos)
    {
        concealed_word.replace(last_pos, 1, string(1, c));
        if (last_pos >= word_length)
        {
            break;
        }
        int pos = target_word.find(c, last_pos + 1);
        last_pos = pos;
    }
}

char update_word(char c)
{
    int pos = target_word.find(c);
    if (pos != string::npos)
    {
        reveal(c);
        return c;
    }
    return '\0';
}

bool update()
{
    char left = update_word(v[0][player_line_idx - 1]);
    char mid = update_word(v[0][player_line_idx]);
    char right = update_word(v[0][player_line_idx + 1]);
    if (left != '\0' || mid != '\0' || right != '\0')
    {
        return true;
    }
    return false;
}

void fill_bucket(int m)
{
    if (m == 1)
    {
        if (player_line.find("_") != string::npos)
        {
            player_line.replace(player_line.find("_"), 1, "+");
        }
    }
    else
    {
        if (player_line.find("+") != string::npos)
        {
            player_line.replace(player_line.find("+"), 1, "_");
        }
    }
}

void judge()
{
    won = (concealed_word == target_word);
}
