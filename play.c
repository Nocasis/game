#include <stdio.h>
#include <termios.h>
#include <unistd.h>
#include <stdlib.h>
#include <time.h>
#include <limits.h>
#include <string.h>

#include "profiles.c"

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
    FILE *file_map;
    file_map=fopen("catalog.txt","r");
    for(int i=0;i<level;i++)  //Тут нужно бдует исправить
        fscanf(file_map,"%s",map_name);
    fclose(file_map);
}





void print_stat(int exp,int hpGG,int gold,int profile_level)
{
    system("clear");
    printf("Your level %6.1d\n",profile_level);
    printf("Your experience %6.1d\n",exp);
    printf("Your health %6.1d\n",hpGG);
    printf("Your gold %6.1d\n",gold);
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



void loot(int *exp,int *gold,int *profile_level)
{
    *exp+=15+(rand()%20);
    *gold+=20+(rand()%10)*(*profile_level);
    if(*exp>=100)
    {
        *exp%=100;
        *profile_level+=1;
    }
}

/*void level_up(int GG[3],int *skill_points)
{

}*/


int play(int level,char *profile_name)
{
    FILE *map;
    int i,j,x,y;
    int GGxy[2];
    int GG[3];
    int exit;
    int **Map;
    char *level_name;
    int temp;


    int gold=get_intValue(profile_name,"gold");
    int experience=get_intValue(profile_name,"experience");
    int profile_level=get_intValue(profile_name,"player_level");
    int skill_points=get_intValue(profile_name,"skill_points");
    int map_level=get_intValue(profile_name,"skill_points");
    GG[0]=get_intValue(profile_name,"hp");
    GG[1]=get_intValue(profile_name,"attack");
    GG[2]=get_intValue(profile_name,"defence");


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
        print_stat(experience,GG[0],gold,profile_level);
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
                        exit=fight(GG,profile_name,profile_level,&skill_points);
                        if(exit==0)
                        {
                            GGxy[0]--;
                            Map[GGxy[0]][GGxy[1]]=empty;
                            loot(&experience,&gold,&profile_level);
                        }
                        if(exit==2)
                            return 0;
                        break;//Тут добавить файт
                    case coins:
                        GGxy[0]--;
                        Map[GGxy[0]][GGxy[1]]=empty;
                        loot(&experience,&gold,&profile_level);//Here i should add skill_points
                        break;//Тут добавить лут чего-либо
                    case finish:
                        set_intValue(profile_name,"gold",gold);
                        set_intValue(profile_name,"experience",experience);
                        set_intValue(profile_name,"player_level",profile_level);
                        set_intValue(profile_name,"skill_points",skill_points);
                        map_level+=1;
                        set_intValue(profile_name,"map_level",map_level);
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
                        exit=fight(GG,profile_name,profile_level,&skill_points);
                        if(exit==0)
                        {
                            GGxy[0]++;
                            Map[GGxy[0]][GGxy[1]]=empty;
                            loot(&experience,&gold,&profile_level);
                        }
                        if(exit==2)
                            return 0;
                        break;//Тут добавить файт
                    case coins:
                        GGxy[0]++;
                        Map[GGxy[0]][GGxy[1]]=empty;
                        loot(&experience,&gold,&profile_level);
                        break;//Тут добавить лут чего-либо
                    case finish:
                        set_intValue(profile_name,"gold",gold);
                        set_intValue(profile_name,"experience",experience);
                        set_intValue(profile_name,"player_level",profile_level);
                        set_intValue(profile_name,"skill_points",skill_points);
                        map_level+=1;
                        set_intValue(profile_name,"map_level",map_level);
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
                        exit=fight(GG,profile_name,profile_level,&skill_points);
                        if(exit==0)
                        {
                            GGxy[1]--;
                            Map[GGxy[0]][GGxy[1]]=empty;
                            loot(&experience,&gold,&profile_level);
                        }
                        if(exit==2)
                            return 0;
                        break;//Тут добавить файт
                    case coins:
                        GGxy[1]--;
                        Map[GGxy[0]][GGxy[1]]=empty;
                        loot(&experience,&gold,&profile_level);
                        break;//Тут добавить лут чего-либо
                    case finish:
                        set_intValue(profile_name,"gold",gold);
                        set_intValue(profile_name,"experience",experience);
                        set_intValue(profile_name,"player_level",profile_level);
                        set_intValue(profile_name,"skill_points",skill_points);
                        map_level+=1;
                        set_intValue(profile_name,"map_level",map_level);
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
                        exit=fight(GG,profile_name,profile_level,&skill_points);
                        if(exit==0)
                        {
                            GGxy[1]++;
                            Map[GGxy[0]][GGxy[1]]=empty;
                            loot(&experience,&gold,&profile_level);
                        }
                        if(exit==2)
                            return 0;
                        break;//Тут добавить файт
                    case coins:
                        GGxy[1]++;
                        Map[GGxy[0]][GGxy[1]]=empty;
                        loot(&experience,&gold,&profile_level);
                        break;//Тут добавить лут чего-либо
                    case finish:
                        set_intValue(profile_name,"gold",gold);
                        set_intValue(profile_name,"experience",experience);
                        set_intValue(profile_name,"player_level",profile_level);
                        set_intValue(profile_name,"skill_points",skill_points);
                        map_level+=1;
                        set_intValue(profile_name,"map_level",map_level);
                        return 1;
                }
                break;
        }
    }
}
