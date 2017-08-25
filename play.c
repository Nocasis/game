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


void Selected(int level,char *map_name)
{
    FILE *file;
    file=fopen("catalog.txt","r");
    for(int i=0;i<level;i++)  //Тут нужно бдует исправить
        fscanf(file,"%s",map_name);
    fclose(file);
}



void Map_mass(int **Map,int n,int m)
{
Map=(int**)malloc(n*sizeof(int*));
        for(int i=0;i<n;i++)
            Map[i]=(int*)malloc(m*sizeof(int));
}



int main(int level)
{
    FILE *map;
    int i,j;
    int GX,GY;
    int WX, WY;
    int **Map;
    char *level_name;

    level_name=(char*)malloc(30*sizeof(char));
    Selected(2,level_name);
    map=fopen(level_name,"r");
    free(level_name);
    fscanf(map,"%d",&i);
    fscanf(map,"%d",&j);
    Map_mass(Map,i,j);
    //Map[0][0]=0;
    //printf("%d",Map[0][0]);
    /*for (int x=0;x<i;x++)
        for(int y=0;y<j;y++)
        {
            fscanf(map,"%d",&Map[x][y]);
            if (Map[x][y]==2)
            {
                GX=x;
                GY=y;
            }
            if (Map[x][y]==3)
            {
                WX=x;
                WY=y;
            }
        }
*/

    fclose(map);
    return 0;
}
