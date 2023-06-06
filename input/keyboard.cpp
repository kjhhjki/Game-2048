#include <keyboard.hpp>
#include <cctype>

#include <stdio.h>
#include <unistd.h>

int check_input(int c)
{
    
    if(!c && read() == 107) return -1;
    if(c == 23 || c == 26) return -1;

    if(std::isalpha(c))
    {
        switch(c)
        {
            case 'w':
                return 4;
            case 'a':
                return 3;
            case 's':
                return 2;
            case 'd':
                return 1;
            default:
                return 0;
        }
    }

    #ifdef _WIN32
        if(c == KEYCODE_ESC) return -1;
    #endif
    #ifdef __linux__
        if(c == KEYCODE_ESC) if(!__kbhit()) return -1;
        c = read();
    #endif
    
    if(c == KEYCODE_DIRECTION)
    {
        switch(read())
        {
            case KEYCODE_DIRECTION_R:
                return 1;
            case KEYCODE_DIRECTION_D:
                return 2;
            case KEYCODE_DIRECTION_L:
                return 3;
            case KEYCODE_DIRECTION_U:
                return 4;
            default:
                return 0;
        }
    }
    return 0;
}

int read(int n)
{
    int c = 0;
    for(int i = 0; i < n; ++i)
    {
        if(!__kbhit()) return 0;
        c += read();
    }
    return c;
}

#ifdef __WIN32__
#include <conio.h>

void keyboard_open()
{
    return;
}
void keyboard_close()
{
    return;
}
int __kbhit(void)
{
    return _kbhit();
}
int read()
{
    return _getch();
}
#endif

#ifdef __linux__
#include <unistd.h>
#include <termios.h>
#include <cstring>
#include <sys/select.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>

struct termios cooked, raw;

void keyboard_open()
{
    int kfd = 0;
    tcgetattr(kfd, &cooked);
    std::memcpy(&raw, &cooked, sizeof(struct termios));
    raw.c_lflag &=~ (ICANON | ECHO);
    raw.c_cc[VEOL] = 1;
    raw.c_cc[VEOF] = 2;
    tcsetattr(kfd, TCSANOW, &raw);
}
void keyboard_close()
{
    int kfd = 0;
    tcsetattr(kfd, TCSANOW, &cooked);
    system("stty echo");
}
int __kbhit(void)
{
    struct termios oldt, newt;
    int ch;
    int oldf;
    tcgetattr(STDIN_FILENO, &oldt);
    newt = oldt;
    newt.c_lflag &= ~(ICANON | ECHO);
    tcsetattr(STDIN_FILENO, TCSANOW, &newt);
    oldf = fcntl(STDIN_FILENO, F_GETFL, 0);
    fcntl(STDIN_FILENO, F_SETFL, oldf | O_NONBLOCK);
    ch = getchar();
    tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
    fcntl(STDIN_FILENO, F_SETFL, oldf);
    if(ch != EOF)
    {
        ungetc(ch, stdin);
        return 1;
    }
    return 0;
}
int read()
{
    return getchar();
}
#endif
