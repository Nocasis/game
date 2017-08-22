#include <stdio.h>
#include <termios.h>
#include <unistd.h>
#include <stdlib.h>
const int menucount = 5;

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
#include "main_menu.c"


int main()
{
    int Select=0,level=1;
    while(1)
    {
        Select=menu(Select);
        switch (Select)
        {
            case 0:
                system("clear");
                printf("Test1");
                getch();
                break;
            case 1:
                system("clear");
                level=Select_map();
                printf("%d",level);
                getch();
                break;
            case 2:
                system("clear");
                printf("Creator");
                getch();
                break;
            case 3:
                system("clear");
                printf("Test3");
                getch();
                break;
            case 4:
                system("clear");
                return 0;
            case 5:
                system("clear");
                printf("Developers");
                int op=much_maps();
                printf("\n\n%d\n\n",op);
                getch();
                break;
            default:
                    printf("Error");
                    getch();
                    return 0;
        }
    }
    getch();
    return 1;
}
