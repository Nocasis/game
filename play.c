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


//void move(int **Map



void print_stat(int score,int hpGG,int gold)
{
    system("clear");
    printf("Your score %6.1d\n\n",score);
    printf("Your health %6.1d\n\n",hpGG);
    printf("Your gold %6.1d\n\n",gold);
}



void print_map(int **Map,int i,int j)
{ 
        for (int x=0;x<j;x++)
        {   
            for(int y=0;y<i;y++)
            {
                switch(Map[x][y])
                {
                    case 0:
                        printf(" ");
                        break;
                    case 1:
                        printf("#");
                        break;
                    case 2:
                        printf("@");
                        break;
                    case 3:
                        printf("$");
                        break;
                    case 4:
                        printf("?");
                        break;
                    case 5:
                        printf("E");
                        break;
                }
            }
            printf("\n");
        }
}


void main(int level)
{
    FILE *map;
    int i,j,x,y;
    int GGxy[2]={1};
    int EXITxy[2]={0};
    int **Map;
    char *level_name;
    int gold=0,score=0,hpGG=100;

    level_name=(char*)malloc(30*sizeof(char));
    Selected(2,level_name);
    map=fopen(level_name,"r");
    free(level_name);
    fscanf(map,"%d",&i);
    fscanf(map,"%d",&j);
    Map=(int**)malloc(j*sizeof(int*));
        for(int k=0;k<j;k++)
            Map[k]=(int*)malloc(i*sizeof(int));
    for (x=0;x<j;x++)
        for(y=0;y<i;y++)
        {
            fscanf(map,"%d",&Map[x][y]);
            if (Map[x][y]==2)
            {
                GGxy[0]=x;
                GGxy[1]=y;
            }
            if (Map[x][y]==3)
            {
                EXITxy[0]=x;
                EXITxy[1]=y;
            }
        }
    fclose(map);
    while(1)
    {
        print_stat(score,hpGG,gold);
        print_map(Map,i,j);
        getch();
    }
}
