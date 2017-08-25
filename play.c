#include <stdio.h>
#include <termios.h>
#include <unistd.h>
#include <stdlib.h>
#include <time.h>
#include <limits.h>
#include <string.h>

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


char *Selected(int level)
{
    FILE *file;
    char *string;
    file=fopen("catalog.txt","r");
    for(int i=0;i<level;i++)  //Тут нужно бдует исправить
        fscanf(file,"%s",string);
    return string;
}




int main(int level)
{
    FILE *map;
    int i,j;
    int GX,GY;
    int hpGG=100, attackGG=17, defenceGG=10; //Тут я ошибки исправляю и тещу всякую дичь, например пытаюсь прочитать ЕБАННЫЙ РАЗМЕР ЕБАННОЙ КАРТЫ.
    int WX, WY;
    char *level_name;
    level_name=Selected(2);
    printf("%s",level_name);
    map=fopen(level_name,"r");
    fscanf(map,"%d",&i);
    //printf("%s",level_name);
    //i=atoi(level_name);
    //fscanf(map,"%s",temp);
    //j=atoi(temp);
    //fscanf(map,"%d",&j);
    //printf("%d %d",i,j);
    fclose(map);
    return 0;
}
