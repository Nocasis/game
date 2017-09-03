#include <stdio.h>
#include <termios.h>
#include <unistd.h>
#include <stdlib.h>

#define ESC 27
#define W 119
#define A 97
#define S 115
#define D 100
#define SPACE 32
#define ENTER 10 
#define TAB 9


int getch( ) 
{
    struct termios oldt,
                   newt;
    int ch;
    tcgetattr( STDIN_FILENO, &oldt );
    newt = oldt;
    newt.c_lflag &= ~( ICANON | ECHO );
    tcsetattr( STDIN_FILENO, TCSANOW, &newt );
    ch = getchar();
    tcsetattr( STDIN_FILENO, TCSANOW, &oldt );
    return ch;
}
#include "Generator.c"
#include "main_menu.c"
int main()
{
    char *profile_name=(char *)malloc(32*sizeof(char));
    profile_name=profile_menu();
    menu(profile_name);
    return 1;
}
