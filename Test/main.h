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

#ifndef __MAIN_H__
#define __MAIN_H__

#ifdef MAIN_H_GLOBAL
#define MAIN_H_EXTERN
#else
#define MAIN_H_EXTERN extern
#endif

#define DENSITY 20 //in 1000
#define WIDTH 51
#define HEIGHT 11

#define CORRECT 1
#define WRONG -1
#define BLANK 0

const int LIST_LENGTH = 100;
const std::string word_list[LIST_LENGTH] = {
    "panda",
    "shirt",
    "candy",
    "drink",
    "white",
    "zero",
    "lemon",
    "result",
    "humor",
    "sleepy",

    "police",
    "shower",
    "morning",
    "summer",
    "teacher",
    "mobile",
    "society",
    "pardon",
    "flower",
    "culture",

    "umbrella",
    "window",
    "yesterday",
    "kitchen",
    "theater",
    "pancake",
    "sandwich",
    "bamboo",
    "random",
    "discuss",

    "birthday",
    "engineering",
    "expensive",
    "headache",
    "history",
    "introduce",
    "newspaper",
    "strawberry",
    "vegetable",
    "watermelon",

    "activity",
    "achieve",
    "apology",
    "jewelry",
    "laundry",
    "forgive",
    "festival",
    "neighbor",
    "between",
    "calculate",

    "abnormal",
    "abundant",
    "adjustment",
    "bridegroom",
    "bungalow",
    "communicate",
    "information",
    "keyboard",
    "envelope",
    "interface",

    "circumstance",
    "coincidence",
    "compulsory",
    "deliberate",
    "earthquake",
    "kindergarten",
    "literature",
    "brainstorm",
    "commander",
    "phenomena",

    "formula",
    "graduate",
    "heritage",
    "fortunate",
    "balcony",
    "standard",
    "feedback",
    "dwelling",
    "estimate",
    "innocent",

    "advertisement",
    "approximate",
    "emergency",
    "individual",
    "instrument",
    "percentage",
    "represent",
    "scholarship",
    "convention",
    "significant",

    "acquaintance",
    "atmosphere",
    "congratulate",
    "paramount",
    "hurricane",
    "incredible",
    "architecture",
    "deficiency",
    "transaction",
    "distinguish",
};

const std::string tip_list[LIST_LENGTH] = {
    "panda",
    "shirt",
    "candy",
    "drink",
    "white",
    "zero",
    "lemon",
    "result",
    "humor",
    "sleepy",

    "police",
    "shower",
    "morning",
    "summer",
    "teacher",
    "mobile",
    "society",
    "pardon",
    "flower",
    "culture",

    "umbrella",
    "window",
    "yesterday",
    "kitchen",
    "theater",
    "pancake",
    "sandwich",
    "bamboo",
    "random",
    "discuss",

    "birthday",
    "engineering",
    "expensive",
    "headache",
    "history",
    "introduce",
    "newspaper",
    "strawberry",
    "vegetable",
    "watermelon",

    "activity",
    "achieve",
    "apology",
    "jewelry",
    "laundry",
    "forgive",
    "festival",
    "neighbor",
    "between",
    "calculate",

    "abnormal",
    "abundant",
    "adjustment",
    "bridegroom",
    "bungalow",
    "communicate",
    "information",
    "keyboard",
    "envelope",
    "interface",

    "circumstance",
    "coincidence",
    "compulsory",
    "deliberate",
    "earthquake",
    "kindergarten",
    "literature",
    "brainstorm",
    "commander",
    "phenomena",

    "formula",
    "graduate",
    "heritage",
    "fortunate",
    "balcony",
    "standard",
    "feedback",
    "dwelling",
    "estimate",
    "innocent",

    "advertisement",
    "approximate",
    "emergency",
    "individual",
    "instrument",
    "percentage",
    "represent",
    "scholarship",
    "convention",
    "significant",

    "acquaintance",
    "atmosphere",
    "congratulate",
    "paramount",
    "hurricane",
    "incredible",
    "architecture",
    "deficiency",
    "transaction",
    "distinguish",
};

class Fall
{
public:
    std::vector<std::string> display;
    int col; //only odd number
    int row;
    Fall(int col, int row)
    {
        this->col = col;
        this->row = row;
        for (int i = 0; i < this->row; i++)
        {
            (this->display).push_back(std::string(col, ' '));
        }
    }
    void push(std::string str)
    {
        (this->display).erase((this->display).begin());
        (this->display).push_back(str);
    }
};

class Word
{
public:
    int length;
    std::string target;
    std::string display;
    std::string tip;
    void init(std::string target, std::string tip)
    {
        this->target = target;
        this->length = this->target.length();
        this->display = std::string(this->length, '-');
        this->tip = tip;
    }
    void reveal(char c)
    {
        int last_pos = (this->target).find(c);
        while (last_pos != std::string::npos)
        {
            (this->display).replace(last_pos, 1, std::string(1, c));
            if (last_pos >= this->length)
            {
                break;
            }
            int pos = (this->target).find(c, last_pos + 1);
            last_pos = pos;
        }
    }
    void print()
    {
        std::cout << this->display << " (" << this->tip << ")";
    }
};

class Player_line
{
public:
    std::string display;
    int index;
    void init(int length)
    {
        this->display = std::string((length - 3) / 2, ' ') + "\\_/" + std::string((length - 3) / 2, ' ');
    }
    void fill_bucket(int m)
    {
        if (m == 1)
        {
            if ((this->display).find("_") != std::string::npos)
            {
                (this->display).replace((this->display).find("_"), 1, "o");
            }
        }
        else if (m == -1)
        {
            if ((this->display).find("_") != std::string::npos)
            {
                (this->display).replace((this->display).find("_"), 1, "x");
            }
        }
        else
        {
            if ((this->display).find("o") != std::string::npos)
            {
                (this->display).replace((this->display).find("o"), 1, "_");
            }
            if ((this->display).find("x") != std::string::npos)
            {
                (this->display).replace((this->display).find("x"), 1, "_");
            }
        }
    }
    void update(int dir)
    {
        if (dir == -1)
        {
            this->display = (this->display).substr(1) + ' ';
            this->index--;
        }
        if (dir == 1)
        {
            (this->display) = ' ' + (this->display).substr(0, (this->display).size() - 1);
            this->index++;
        }
    }
    void print()
    {
        std::cout << this->display;
    }
};

class Timer
{
public:
    int countdown;
    bool deducted;
    Timer(int countdown)
    {
        this->countdown = countdown;
        this->deducted = false;
    };
    void print()
    {
        std::cout << "COUNTDOWN: " << this->countdown;
    };
};

class Status
{
public:
    bool won;
    bool end;
    bool time_up;
    Status()
    {
        this->won = false;
        this->end = false;
        this->time_up = false;
    }
};

void print_option(std::string str, bool at);
void print_menu(int now_at);
int menu();
void game();
void player();
void tick();
void init();
std::string rand_str(int l);
void print();
int update_word(char c);
void update();
void judge();
void destroy();
void record(std::string playerName, int level, int time);

#endif // __MAIN_H__
