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




void random_enemy(int profile_level,int NPC[3],char name_npc[32])
{
    int k=rand()%3;
    switch(k)
    {
        case 0:
            strcpy(name_npc,"Zloy Golub'");
            NPC[0]=45+0.5*(rand()%10)*profile_level;
            NPC[1]=20+0.5*(rand()%8)*profile_level;
            NPC[2]=5+0.5*(rand()%6)*profile_level;
            return;
        case 1:
            strcpy(name_npc,"Zombie-Navalny");
            NPC[0]=100+0.5*(rand()%30)*profile_level;
            NPC[1]=10+0.5*(rand()%3)*profile_level;
            NPC[2]=5+0.5*(rand()%6)*profile_level;
            return;
        case 2:
            strcpy(name_npc,"Ghost");
            NPC[0]=45+0.5*(rand()%20)*profile_level;
            NPC[1]=15+0.5*(rand()%4)*profile_level;
            NPC[2]=15+0.5*(rand()%6)*profile_level;
            return;
    }
}
void print_window(int a,int GG[3],int NPC[3],char name_npc[32]) // Here we should add some things from profiles
{
    printf("\t\t   ***Fight***\n");
    printf("\n\t You \t\t%s\n",name_npc);
    printf("%c",124);
    for(int i=0;i<23; i++)
        printf("%c",61);
    printf("%c",124);
    for(int i=0;i<23;i++)
        printf("%c",61);
    printf("%c",124);

    printf("\n%c Health: %d\t\t%c Health:%d\t\t%c",124,GG[0],124,NPC[0],124);
    printf("\n%c \t\t %8c \t\t %8c",124,124,124);
    printf("\n%c Attack: %d\t%9c Attack: %d\t%9c",124,GG[1],124,NPC[1],124);
    printf("\n%c \t\t %8c \t\t %8c",124,124,124);
    printf("\n%c Defence: %d\t%9c Defence: %d\t%9c",124,GG[2],124,NPC[2],124);
    printf("\n%c \t\t %8c \t\t %8c\n",124,124,124);

    printf("%c",124);
    for(int i=0; i<23; i++)
        printf("%c",61);
    printf("%c",124);
    for(int i=0;i<23;i++)
        printf("%c",61);
    printf("%c",124);

    switch(a)
            {
                case 0:
                    printf("\n1.Hit<<<\n2.Hard blow\n3.Careful blow\n4.Book of skills\n5.Escape\n");
                    break;
                case 1:
                    printf("\n1.Hit\n2.Hard blow<<<\n3.Careful blow\n4.Book of skills\n5.Escape\n");
                    break;
                case 2:
                    printf("\n1.Hit\n2.Hard blow\n3.Careful blow<<<\n4.Book of skills\n5.Escape\n");
                    break;
                case 3:
                    printf("\n1.Hit\n2.Hard blow\n3.Careful blow\n4.Book of skills<<<\n5.Escape\n");
                    break;
                case 4:
                    printf("\n1.Hit\n2.Hard blow\n3.Careful blow\n4.Book of skills\n5.Escape<<<\n");
            }
}



void print_fight_window(int a,int GG[3],int NPC[3],char name_npc[32],int *skill_points) // Here we should add some things from profiles
{
    printf("\t\t   ***Fight***\n");
    printf("\n\t You \t\t%s\n",name_npc);
    printf("%c",124);
    for(int i=0;i<23; i++)
        printf("%c",61);
    printf("%c",124);
    for(int i=0;i<23;i++)
        printf("%c",61);
    printf("%c",124);

    printf("\n%c Health: %d\t\t%c Health:%d\t\t%c",124,GG[0],124,NPC[0],124);
    printf("\n%c \t\t %8c \t\t %8c",124,124,124);
    printf("\n%c Attack: %d\t%9c Attack: %d\t%9c",124,GG[1],124,NPC[1],124);
    printf("\n%c \t\t %8c \t\t %8c",124,124,124);
    printf("\n%c Defence: %d\t%9c Defence: %d\t%9c",124,GG[2],124,NPC[2],124);
    printf("\n%c \t\t %8c \t\t %8c\n",124,124,124);

    printf("%c",124);
    for(int i=0; i<23; i++)
        printf("%c",61);
    printf("%c",124);
    for(int i=0;i<23;i++)
        printf("%c",61);
    printf("%c",124);
    printf("\nYou have %d skill points.",*skill_points);
    switch(a)
    {
        case 0:
            printf("\n1.Hit1<<<\n2.Hit2\n3.Hit3\n4.Hit4\n5.Quick legs\n");
            break;
        case 1:
            printf("\n1.Hit1\n2.Hit2<<<\n3.Hit3\n4.Hit4\n5.Quick legs\n");
            break;
        case 2:
            printf("\n1.Hit1\n2.Hit2\n3.Hit3<<<\n4.Hit4\n5.Quick legs\n");
            break;
        case 3:
            printf("\n1.Hit1\n2.Hit2\n3.Hit3\n4.Hit4<<<\n5.Quick legs\n");
            break;
        case 4:
            printf("\n1.Hit1\n2.Hit2\n3.Hit3\n4.Hit4\n5.Quick legs<<<\n\n100 Chance to escape! Cost 2 skill points.");
    }
}



int fight_menu(int a,int GG[3],int NPC[3],char *profile_name,char name_npc[32])
{
    char temp;
    int menucount=4;
    while(1)
    {
        system("clear");
        print_window(a,GG,NPC,name_npc);
        temp=getch();
        switch (temp)
        {
            case ENTER:
                return a;
            case W:
                if((a<=0)||(a>menucount))
                    a=menucount;
                else
                    a--;
                break;
            case S:
                if((a<0)||(a>=menucount))
                    a=0;
                else
                    a++;
        }
    }
}



void Hit(int GG[3],int NPC[3])
{
    int D2NPC,D2GG;

    D2NPC=GG[1]+GG[1]*(rand()%101-50)/100-NPC[2];
    D2GG=NPC[1]+NPC[1]*(rand()%101-50)/100-GG[2];
    if(D2NPC>0)
    {
        NPC[0]-=D2NPC;
        printf("You hitted enemy on %d hp.\n",D2NPC);
    }
    else
        printf("Enemy block your hit\n");
    if(D2GG>0)
    {
        GG[0]-=D2GG;
        printf("Enemy hit you on %d hp.\n",D2GG);

    }
    else
        printf("You block enemys hit\n");
}



void Hard_blow(int GG[3],int NPC[3])
{
    int D2NPC,D2GG;
    GG[2]-=10;
    GG[1]+=8;
    D2NPC=GG[1]+GG[1]*(rand()%101-50)/100-NPC[2];
    D2GG=NPC[1]+NPC[1]*(rand()%101-50)/100-GG[2];
    GG[2]+=10;
    GG[1]-=8;
    if(D2NPC>0)
    {
        NPC[0]-=D2NPC;
        printf("You hitted enemy on %d hp.\n",D2NPC);
    }
    else
        printf("Enemy block your hit\n");
    if(D2GG>0)
    {
        GG[0]-=D2GG;
        printf("Enemy hit you on %d hp.\n",D2GG);

    }
    else
        printf("You block enemys hit\n");
}



void Careful_blow(int GG[3],int NPC[3])
{
    int D2NPC,D2GG;
    GG[2]+=8;
    GG[1]-=10;
    D2NPC=GG[1]+GG[1]*(rand()%101-50)/100-NPC[2];
    D2GG=NPC[1]+NPC[1]*(rand()%101-50)/100-GG[2];
    GG[2]-=8;
    GG[1]+=10;
    if(D2NPC>0)
    {
        NPC[0]-=D2NPC;
        printf("You hitted enemy on %d hp.\n",D2NPC);
    }
    else
        printf("Enemy block your hit\n");
    if(D2GG>0)
    {
        GG[0]-=D2GG;
        printf("Enemy hit you on %d hp.\n",D2GG);

    }
    else
        printf("You block enemys hit\n");
}


int skills(int a,int GG[3],int NPC[3],char name_npc[32],int *skill_points)
{
    char temp;
    int menucount = 4;
    while (1) {
        system("clear");
        print_fight_window(a, GG, NPC, name_npc,skill_points);
        temp = getch();
        switch (temp)
        {
            case ESC:
                return -1;
            case ENTER:
                return a;
            case W:
                if ((a <= 0) || (a > menucount))
                    a = menucount;
                else
                    a--;
                break;
            case S:
                if ((a < 0) || (a >= menucount))
                    a = 0;
                else
                    a++;
        }
    }
}




int fight(int GG[3],char *profile_name,int profile_level,int *skill_points)//Call this
{
    int what_hit=0;
    char name_npc[32];
    int NPC[3];
    random_enemy(profile_level,NPC,name_npc);
    while(1)
    {
        what_hit=fight_menu(0,GG,NPC,profile_name,name_npc);
        switch (what_hit)
        {
            case 0:
                Hit(GG,NPC);
                break;
            case 1:
                Hard_blow(GG,NPC);
                break;
            case 2:
                Careful_blow(GG,NPC);
                break;
            case 3:
                what_hit=skills(0,GG,NPC,name_npc,skill_points);
                if(what_hit==-1)
                {
                    printf("\nYou are closed the book.\n");
                    break;
                }
                switch(what_hit)
                {
                    case 0:
                        Hit(GG,NPC);
                        break;
                    case 1:
                        Hit(GG,NPC);
                        break;
                    case 2:
                        Hit(GG,NPC);
                        break;
                    case 3:
                        Hit(GG,NPC);
                        break;
                    case 4:
                        if(*skill_points>=2)
                        {
                            *skill_points -= 2;
                            return 1;
                        }
                        printf("\nYou have not enough points");
                        break;
                }
                break;//For the not a long time
            case 4:
                printf("\nYou escaped");
                getch();
                return 1;
        }
        if(NPC[0]<=0)
        {
            printf("\t\t You are killed %s\n",name_npc);
            getch();
            return 0;
        }
        if(GG[0]<=0)
        {
            printf("\t\t You are dead!\n");
            getch();
            return 2;
        }
        getch();
    }
}
                
