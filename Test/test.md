This folder is for testing anything. 
All files will be deleted after the project is completed. 

void print_option(string str, bool at)
{
    char fill = ' ';
    if (at)
    {
        fill = '#';
    }
    int front_sep, back_sep;
    if ((WIDTH - str.length()) % 2 == 1)
    {
        front_sep = (WIDTH - str.length()) / 2;
        back_sep = (WIDTH - str.length()) / 2 + 1;
    }
    else
    {
        front_sep = (WIDTH - str.length()) / 2;
        back_sep = (WIDTH - str.length()) / 2;
    }
    cout << string(front_sep, fill) << str << string(back_sep, fill) << endl;
}

void print_menu(int now_at)
{
    string options[6] = {"New Game", "Load Game", "Show Leaderboard", "About", "Quit", "[up/down to select | e to enter]"};
    const int OFFSET = 2;
#ifdef LINUX
    std::system("clear");
#else
    std::system("cls");
#endif
    for (int i = 0; i < HEIGHT; i++)
    {
        bool at = (i == (now_at + OFFSET));
        if (i >= OFFSET && i <= OFFSET + 5)
        {
            print_option(options[i - OFFSET], at);
        }
        else
        {
            print_option("", false);
        }
    }
}

int menu()
{
#ifdef LINUX
    setBufferedInput(false);
#endif
    int now_at = 0;
    print_menu(now_at);
#ifdef LINUX
    int ch1, ch2, ch3;
    while (1)
    {
        ch1 = -1;
        ch2 = -1;
        ch3 = -1;
        ch1 = getchar();
        if (ch1 == 27)
        {
            ch2 = getchar();
            if (ch2 == 91)
            {
                ch3 = getchar();
                if (ch3 == 65 && now_at > 0) //left
                {
                    now_at--;
                }
                else if (ch3 == 66 && now_at < 4) //right
                {
                    now_at++;
                }
            }
            else
            {
                goto sleep;
            }
        }
        else if (ch1 == 101) //e
        {
            return now_at;
        }
        else
        {
            goto sleep;
        }
        print_menu(now_at);
    sleep:
        this_thread::sleep_for(chrono::milliseconds(20));
    }
    return -1;
#else
    int ch1, ch2;
    while (1)
    {
        ch1 = -1;
        ch2 = -1;
        if (_kbhit())
        {
            ch1 = _getch();
            if (ch1 == 224)
            {
                ch2 = _getch();
                if (ch2 == 72 && now_at > 0) //up
                {
                    now_at--;
                }
                else if (ch2 == 80 && now_at < 4) //down
                {
                    now_at++;
                }
            }
            else if (ch1 == 101) //enter
            {
                //promiseObj.set_value(now_at);
                return now_at;
            }
            else
            {
                goto sleep;
            }
            print_menu(now_at);
        }
    sleep:
        this_thread::sleep_for(chrono::milliseconds(20));
    }
    return -1;
#endif
}