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
}



int EXIT()
{
    int temp,a=1;
    system("clear");
    while(1)
    {
        system("clear");
        switch(a)
        {
            case 1:
                printf("Do you want to leave?\n1.Yes<<<\n2.No\n");
                break;
            case 0:
                printf("Do you want to leave?\n1.Yes\n2.No<<<\n");
                break;
        }
        temp=getch();
        switch(temp)
        {
            case W:
                a++;
                if(a>1)
                    a=0;
                break;
            case S:
                a--;
                if(a<0)
                    a=1;
                break;
            case ENTER:
                return a;
        }
    }
}






int play(int level)
{
    FILE *map;
    int i,j,x,y;
    int GGxy[2];
    int GG[3]={100,25,8};
    char profile_name[32]="Nocasis";
    int exit;
    int **Map;
    char *level_name;
    int temp;
    int gold=0,score=0
        ;

    level_name=(char*)malloc(30*sizeof(char));
    Selected(level,level_name);
    map=fopen(level_name,"r");
    free(level_name);
    fscanf(map,"%d",&j);//Кол-во столбцов
    fscanf(map,"%d",&i);//Кол-во строк
    Map=(int**)malloc(i*sizeof(int*));
        for(int k=0;k<i;k++)
            Map[k]=(int*)malloc(j*sizeof(int));
    for (x=0;x<i;x++)
        for(y=0;y<j;y++)
        {
            fscanf(map,"%d",&Map[x][y]);
            if (Map[x][y]==spawn)
            {
                GGxy[0]=x;
                GGxy[1]=y;
            }
        }
    fclose(map);
    while(1)
    {
        print_stat(score,GG[0],gold);
        print_map(Map,i,j,GGxy);
        temp=getch();
        switch(temp)
        {
            case ESC:
                exit=EXIT();
                if(exit==1)
                    return 0;
                break;
            case W:
                switch(Map[GGxy[0]-1][GGxy[1]])
                {
                    case empty:
                        GGxy[0]--;
                        break;
                    case spawn:
                        GGxy[0]--;
                        break;
                    case wall:
                        break;
                    case enemy:
                        system("clear");
                        exit=fight(GG,profile_name);
                        if(exit==0)
                        {
                            GGxy[0]--;
                            Map[GGxy[0]][GGxy[1]]=empty;
                        }
                        if(exit==2)
                            return 0;
                        break;//Тут добавить файт
                    case coins:
                        break;//Тут добавить лут чего-либо
                    case finish:
                        return 1;
                }
                break;
            case S:
                switch(Map[GGxy[0]+1][GGxy[1]])
                {
                    case empty:
                        GGxy[0]++;
                        break;
                    case spawn:
                        GGxy[0]++;
                        break;
                    case wall:
                        break;
                    case enemy:
                        system("clear");
                        exit=fight(GG,profile_name);
                        if(exit==0)
                        {
                            GGxy[0]++;
                            Map[GGxy[0]][GGxy[1]]=empty;
                        }
                        if(exit==2)
                            return 0;
                        break;//Тут добавить файт
                    case coins:
                        break;//Тут добавить лут чего-либо
                    case finish:
                        return 1;
                }
                break;
            case A:
                switch(Map[GGxy[0]][GGxy[1]-1])
                {
                    case empty:
                        GGxy[1]--;
                        break;
                    case spawn:
                        GGxy[1]--;
                        break;
                    case wall:
                        break;
                    case enemy:
                        system("clear");
                        exit=fight(GG,profile_name);
                        if(exit==0)
                        {
                            GGxy[1]--;
                            Map[GGxy[0]][GGxy[1]]=empty;
                        }
                        if(exit==2)
                            return 0;
                        break;//Тут добавить файт
                    case coins:
                        break;//Тут добавить лут чего-либо
                    case finish:
                        return 1;
                }
                break;
            case D:
                switch(Map[GGxy[0]][GGxy[1]+1])
                {
                    case empty:
                        GGxy[1]++;
                        break;
                    case spawn:
                        GGxy[1]++;
                        break;
                    case wall:
                        break;
                    case enemy:
                        system("clear");
                        exit=fight(GG,profile_name);
                        if(exit==0)
                        {
                            GGxy[1]++;
                            Map[GGxy[0]][GGxy[1]]=empty;
                        }
                        if(exit==2)
                            return 0;
                        break;//Тут добавить файт
                    case coins:
                        break;//Тут добавить лут чего-либо
                    case finish:
                        return 1;
                }
                break;
        }
    }
}
