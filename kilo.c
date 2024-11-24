#include <unistd.h>
#include <termios.h>
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

struct termios orig_termios;

void disableRowMode(void)
{
    tcsetattr(STDIN_FILENO, TCSAFLUSH, &orig_termios);
}

void enableRowMode(void)
{
    tcgetattr(STDIN_FILENO, &orig_termios);
    atexit(disableRowMode);
    struct termios raw = orig_termios;

    raw.c_lflag &= ~(ECHO | ICANON);

    tcsetattr(STDIN_FILENO, TCSAFLUSH, &raw);
}

int main(void)
{   
    enableRowMode();
    char c;
    while (read(STDIN_FILENO, &c, 1) == 1 && c != 'q') {
        if (iscntrl(c))
            printf("%d\n", c);
        if (!iscntrl(c))
            printf("%d ('%c') \n", c, c);
    }
    return 0;
}

