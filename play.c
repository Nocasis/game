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
#define empty 0
#define wall 1
#define finish 2
#define coins 3
#define enemy 4
#define spawn 5


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





void print_stat(int score,int hpGG,int gold)
{
    system("clear");
    printf("Your score %6.1d\n\n",score);
    printf("Your health %6.1d\n\n",hpGG);
    printf("Your gold %6.1d\n\n",gold);
}



void print_map(int **Map,int i,int j,int GGxy[2])
{ 
        for (int x=0;x<i;x++)
        {   
            for(int y=0;y<j;y++)
            {
                if((x==GGxy[0])&&(y==GGxy[1]))
                {
                    printf("P");
                    continue;
                }
                switch(Map[x][y])
                {
                    case (empty):
                        printf(" ");
                        break;
                    case (wall):
                        printf("#");
                        break;
                    case (finish):
                        printf("@");
                        break;
                    case (coins):
                        printf("$");
                        break;
                    case (spawn):
                        printf(" ");
                        break;
                    case (enemy):
                        printf("E");
                        break;
                }
            }
            printf("\n");
        }
        GGxy[0]--;
        GGxy[1]++;
}

void move();

void main(int level)
{
    FILE *map;
    int i,j,x,y;
    int GGxy[2];
    int EXITxy[2];
    int **Map;
    char *level_name;
    int gold=0,score=0,hpGG=100;

    level_name=(char*)malloc(30*sizeof(char));
    Selected(3,level_name);
    map=fopen(level_name,"r");
    free(level_name);
    fscanf(map,"%d",&j);
    fscanf(map,"%d",&i);
    Map=(int**)malloc(i*sizeof(int*));
        for(int k=0;k<i;k++)
            Map[k]=(int*)malloc(j*sizeof(int));
    for (x=0;x<i;x++)
        for(y=0;y<j;y++)
        {
            fscanf(map,"%d",&Map[x][y]);
            if (Map[x][y]==spawn)
            {
                GGxy[0]=y;
                GGxy[1]=x;
            }
            if (Map[x][y]==finish)
            {
                EXITxy[0]=y;
                EXITxy[1]=x;
            }
        }
    fclose(map);
    while(1)
    {
<<<<<<< HEAD
    print_stat(score,hpGG,gold);
    print_map(Map,i,j,GGxy);
    getch();
=======
        print_stat(score,hpGG,gold);
        print_map(Map,i,j);
        getch();
>>>>>>> 46e39751c91e5b70ac539ad6a8279ffa4758f44a
    }
}
