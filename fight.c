#include <stdio.h>
#include <stdlib.h>


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
            NPC[0]=45+0.5*(rand()%10)*(profile_level/2);
            NPC[1]=16+0.5*(rand()%8)*(profile_level/2);
            NPC[2]=5+0.5*(rand()%6)*(profile_level/2);
            return;
        case 1:
            strcpy(name_npc,"Zombie-Max");
            NPC[0]=115+0.5*(rand()%30)*(profile_level/2);
            NPC[1]=10+0.5*(rand()%3)*(profile_level/2);
            NPC[2]=5+0.5*(rand()%6)*(profile_level/2);
            return;
        case 2:
            strcpy(name_npc,"Ghost");
            NPC[0]=45+0.5*(rand()%20)*(profile_level/2);
            NPC[1]=12+0.5*(rand()%4)*(profile_level/2);
            NPC[2]=10+0.5*(rand()%6)*(profile_level/2);
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
                    printf("\nHit<<<\nHard blow\nCareful blow\nBook of skills\nInventory\nEscape\n");
                    break;
                case 1:
                    printf("\nHit\nHard blow<<<\nCareful blow\nBook of skills\nInventory\nEscape\n");
                    break;
                case 2:
                    printf("\nHit\nHard blow\nCareful blow<<<\nBook of skills\nInventory\nEscape\n");
                    break;
                case 3:
                    printf("\nHit\nHard blow\nCareful blow\nBook of skills<<<\nInventory\nEscape\n");
                    break;
                case 4:
                    printf("\nHit\nHard blow\nCareful blow\nBook of skills\nInventory<<<\nEscape\n");
                    break;
                case 5:
                    printf("\nHit\nHard blow\nCareful blow\nBook of skills\nInventory\nEscape<<<\n");
                    break;
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
    printf("\nYou have %d skill points.",*skill_points); // Не листается почему то
    switch(a)
    {
        case 0:
            printf("\nTriple hit<<<\nVampire\nBlood Magick\nMax's Punch\nQuick legs\n\nYou hit enemy on x3 damage.Cost 6 skill points");
            break;
        case 1:
            printf("\nTriple hit\nVampire<<<\nBlood Magick\nMax's Punch\nQuick legs\n\nPart of your damage heals you.Cost 4 skill points.");
            break;
        case 2:
            printf("\nTriple hit\nVampire\nBlood Magick<<<\nMax's Punch\nQuick legs\n\nGain 1 skill point and deal 10 damage to enemy.Cost 20 hp.");
            break;
        case 3:
            printf("\nTriple hit\nVampire\nBlood Magick\nMax's Punch<<<\nQuick legs\n\nYou just kill the enemy.Cost 10 skill points.");
            break;
        case 4:
            printf("\nTriple hit\nVampire\nBlood Magick\nMax's Punch\nQuick legs<<<\n\nChance to escape! Cost 2 skill points.");
    }
}



int fight_menu(int a,int GG[3],int NPC[3],char *profile_name,char name_npc[32])
{
    char temp;
    int menucount=5;
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
        printf("\nYou hitted enemy on %d hp.\n",D2NPC);
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

void blood_magick(int GG[3],int NPC[3],int *skill_points)
{
    int D2NPC,D2GG;

        D2NPC = 10;
        D2GG = 20;
        if (D2NPC > 0)
        {
            NPC[0] -= D2NPC;
            printf("\nYou hitted enemy on %d hp.\n", D2NPC);
        }
        if (D2GG > 0)
        {
            GG[0] -= D2GG;
            printf("Enemy hit you on %d hp.\n", D2GG);

        } else
            printf("You block enemys hit\n");
    *skill_points +=1;
}


int escape(int GG[3],int NPC[3])
{
    int chance,D2GG;
    chance=rand() % 10;
    if(chance == 5 || chance == 3 || chance == 1)
        return 1;
    else
    {
        if(GG[0] > 60 &&(GG[1] > NPC[1] || GG[2] > NPC[2]))
            return 1;
    }
    D2GG = NPC[1] + NPC[1] * (rand() % 101 - 50) / 100 - GG[2] + 5;
    if (D2GG > 0)
    {
        GG[0] -= D2GG;
        printf("\nEnemy hit you on %d hp.\n", D2GG);

    } else
        printf("You block enemys hit\n");
    return 0;
}


void max_beat(int GG[3],int NPC[3],int *skill_points)
{
    if(*skill_points<10)
    {
        printf("\nYou have not enough points for this\n");
        return;
    }
    else
    {
        NPC[0] = 0;
        *skill_points -= 10;
    }
}


void vampire(int GG[3],int NPC[3],int *skill_points)
{
    int D2NPC,D2GG,heal;
    if(*skill_points<4)
    {
        printf("\nYou have not enough points for this\n");
        return;
    }
    else
    {
        D2NPC=GG[1]*1.5+GG[1]*(rand()%101-50)/100-NPC[2];
        D2GG = NPC[1] + NPC[1] * (rand() % 101 - 50) / 100 - GG[2]+3;
        if (D2NPC > 0)
        {
            NPC[0] -= D2NPC;
            printf("\nYou hitted enemy on %d hp.\n", D2NPC);
        }
        if (D2GG > 0)
        {
            GG[0] -= D2GG;
            printf("Enemy hit you on %d hp.\n", D2GG);

        } else
            printf("You block enemys hit\n");
    }
    heal = D2NPC/2;
    printf("You heal yourself for %d hp.\n",heal);
    GG[0] += heal;
    *skill_points -=4;
}


void Triple_hit(int GG[3],int NPC[3],int *skill_points)
{
    int D2NPC,D2GG;
    if(*skill_points<6)
    {
        printf("\nYou have not enough points for this\n");
        return;
    }
    else
    {
        D2NPC=GG[1]*3+GG[1]*(rand()%101-50)/100-NPC[2];
        D2GG = NPC[1] + NPC[1] * (rand() % 101 - 50) / 100 - GG[2];
        if (D2NPC > 0)
        {
            NPC[0] -= D2NPC;
            printf("\nYou hitted enemy on %d hp.\n", D2NPC);
        }
        if (D2GG > 0)
        {
            GG[0] -= D2GG;
            printf("Enemy hit you on %d hp.\n", D2GG);

        } else
            printf("You block enemys hit\n");
    }
    *skill_points -=6;
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
        printf("\nYou hitted enemy on %d hp.\n",D2NPC);
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
        printf("\nYou hitted enemy on %d hp.\n",D2NPC);
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
    a = 0;
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

void Potions(MYSQL *mysql,char *profileName,int GG[3])
{
    int size = get_intValue(mysql,profileName,"inventory");

    int power[size], cost[size];

    int *inventory = (int*)malloc(sizeof(int)*size);
    get_inventory(mysql,profileName,inventory);
    char **item_name = (char**)malloc(size*sizeof(char*));
    for(int i=0; i<size; i++)
        item_name[i]=(char*)malloc(32*sizeof(char));

    get_item_info(inventory,item_name,power,cost,size);

    int hp = get_intValue(mysql,profileName,"hp");

    int pos=0;
    while(1)
    {
        //system("cls");
        system("clear");
        printf("Press ECS to exit\n");
        printf("Here you can use your potions\n");
        printf("Your Health: %d",GG[0]);
        printf("\n\tName\t\t\tPower\n");

        for(int i=0; i<size; i++)
        {
            printf("%20s\t\t%3d\t",item_name[i],power[i]);
            if(i==pos)
                printf("<<<");
            printf("\n");
        }

        char temp = getch();

        switch(temp)
        {
            case W:
                if(pos==0)
                    pos=size-1;
                else
                    pos--;
                break;
            case S:
                if(pos==size-1)
                    pos=0;
                else
                    pos++;
                break;
            case ENTER:
                if(inventory[pos] != -1)
                {
                    if(inventory[pos]>=0 && inventory[pos]<10)
                    {
                        GG[0] += power[pos];
                        inventory[pos]=-1;
                        strcpy(item_name[pos],"empty");
                        power[pos]=0;
                        cost[pos]=0;
                        if(GG[0]>hp)
                            GG[0]=hp;
                    }
                }
                break;
            case ESC:
                set_inventory(mysql,profileName,inventory);
                for(int i=0; i<size; i++)
                    free(item_name[i]);

                free(item_name);
                free(inventory);

                return;
        }

    }
}


int fight(MYSQL *mysql,int GG[3],char *profile_name,int profile_level,int *skill_points)//Call this
{
    int what_hit=0,what_skill=0,what_escape=0;
    char name_npc[32];
    int NPC[3];
    random_enemy(profile_level,NPC,name_npc);
    while(1)
    {
        what_hit=fight_menu(what_hit,GG,NPC,profile_name,name_npc);
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
                what_skill=skills(what_skill,GG,NPC,name_npc,skill_points);
                if(what_skill==-1)
                {
                    printf("\nYou are closed the book.\n");
                    break;
                }
                switch(what_skill)
                {
                    case 0:
                        Triple_hit(GG,NPC,skill_points);
                        break;
                    case 1:
                        vampire(GG,NPC,skill_points);
                        break;
                    case 2:
                        blood_magick(GG,NPC,skill_points);
                        break;
                    case 3:
                        max_beat(GG,NPC,skill_points);
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
                Potions(mysql,profile_name,GG);
                printf("\nYou closed you bag");
                break;
            case 5:
                what_escape = escape(GG,NPC);
                if(what_escape)
                    return 1;
                printf("\nUnseccessful escape");
                break;
        }

        if(GG[0]<=0)
        {
            printf("\t\t You are dead!\n");
            getch();
            return 2;
        }

        if(NPC[0]<=0)
        {
            printf("\t\t You killed a %s\n",name_npc);
            getch();
            return 0;
        }

        getch();
    }
}
                
