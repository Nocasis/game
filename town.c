#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define ESC 27
#define W 119
#define A 97
#define S 115
#define D 100
#define SPACE 32
#define ENTER 10
#define TAB 9

const int min_potions = 0;
const int max_potions = 9;
const int min_armors = 10;
const int max_armors = 49;
const int min_weapons = 50;
const int max_weapons = 99;


void town(char *profileName);//+
void shop(char *profileName);//+
void lvl_up(char *profileName);//-

void sell(char *profileName);//+
void buy_items(char *profileName, char *itemname);//+

int town_menu();//+
int town_ESC();//-

int much_items(char *itemname);//+
void get_item_info(int* inventory, char** item_name, int* power, int* cost, int size);//+

void sell(char *profileName)
{
    int size = get_intValue(profileName,"inventory");
    
    int power[size], cost[size];
    
    int *inventory = (int*)malloc(sizeof(int)*size);
    get_inventory(profileName,inventory);
    
    char **item_name = (char**)malloc(size*sizeof(char*));
    for(int i=0; i<size; i++)
    item_name[i]=(char*)malloc(32*sizeof(char));
    
    get_item_info(inventory,item_name,power,cost,size);
    
    int gold = get_intValue(profileName,"gold");
    
    int pos=0;
    while(1)
    {
        //system("cls");
        system("clear");
        printf("Press ECS to exit\n");
        printf("Well, let's see what you offer me\n");
        printf("YOUR GOLD: %d\n",gold);
        printf("\n\tName\t\tPower\tCost\n");
        
        for(int i=0; i<size; i++)
        {
            printf("%2d%20s\t%3d\t%3d",i+1,item_name[i],power[i],cost[i]);
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
                if(inventory[pos]!=-1)
                {
                    gold+=cost[pos];
                    inventory[pos]=-1;
                    strcpy(item_name[pos],"empty");
                    power[pos]=0;
                    cost[pos]=0;
                }
                break;
            case ESC:
                set_inventory(profileName,inventory);
                set_intValue(profileName,"gold",gold);
                for(int i=0; i<size; i++)
                    free(item_name[i]);
                
                free(item_name);
                free(inventory);
                
                return;
        }
        
    }
  
}


void get_item_info(int* inventory, char** item_name, int* power, int* cost, int size)
{
    int tid, tpower, tcost; //t-temp
    char *tname = (char*)malloc(sizeof(char)*32);
    
    FILE *items=fopen("items.txt","r");
    if(items==NULL)
    {
        //system("cls");
        system("clear");
        printf("items.txt not found");
        getch();
        return;
    }

    while(!feof(items))
    {
        //printf("\n\nss\n\n");
        fscanf(items,"%d %s",&tid, tname);  
        if(strcmp(tname,"NULL")!=0)
            fscanf(items,"%d %d",&tpower, &tcost);
        else
            continue;
        
        for(int i=0; i<size; i++)
        {
            if(tid==inventory[i])
            {
                strcpy(item_name[i],tname);
                power[i]=tpower;
                cost[i]=tcost;
            }
        }      
    }
    //printf("\n\nss\n\n");
    for(int i=0; i<size; i++)
    {
        if(inventory[i]==-1)
        {            
            strcpy(item_name[i],"empty");
            power[i]=0;
            cost[i]=0;
        }
    } 

    fclose(items);
    free(tname);
} 

void town(char *profileName)
{
    int current;
    while(1)
    {
        current=town_menu();
        switch(current)
        {
            case 0:
                shop(profileName);
                break;
            case 1:
                //lvl_up();
                break;
            case 2:
                return;
            case ESC:
                //escmenu
                break;
        }
    }
    
}

int town_menu()
{
    int select=0;
    char button;
    while(1)
    {
        //system("cls");
        system("clear");
        printf("Welcome to the Huibelburg!\n");
        
        switch(select)
        {
            case(0):
                printf("\n 1.Shop<<<\n 2.Level Up!\n 3.Leave the town\n");
                break;
            case(1):
                printf("\n 1.Shop\n 2.Level Up!<<<\n 3.Leave the town\n");
                break;
            case(2):
                printf("\n 1.Shop\n 2.Level Up!\n 3.Leave the town<<<\n");
                break;
            
        }
        
        button = getch();
        
        switch(button)
        {
            case(W):
                if(select==0)
                select=2;
                else
                select--;
                break;
            case(S):
                if(select==2)
                select=0;
                else
                select++;
                break;
            case(ENTER):
                return select;
                break;
            case(ESC):
                return ESC;
                break;    
        }
    }
}


void shop(char *profileName)
{
    int select=0;
    char button;
    while(1)
    {
        //system("cls");
        system("clear");
        printf("We are glad to see you in the store Dirty Billy\n");
        printf("Here are sold the most rare potions from around the city\n");
        printf("Here you can buy excellent armor\n");
        printf("And here you can choose the most impressive items for murders\n");
        printf("Also you can sell your trash at the highest price in the city\n");
        
        switch(select)
        {
            case(0):
                printf("\n 1. Sell<<<\n 2. Buy potions\n 3. Buy armors\n 4. Buy weapons\n 5. Exit\n");
                break;
            case(1):
                printf("\n 1. Sell\n 2. Buy potions<<<\n 3. Buy armors\n 4. Buy weapons\n 5. Exit\n");
                break;
            case(2):
                printf("\n 1. Sell\n 2. Buy potions\n 3. Buy armors<<<\n 4. Buy weapons\n 5. Exit\n");
                break;
            case(3):
                printf("\n 1. Sell\n 2. Buy potions\n 3. Buy armors\n 4. Buy weapons<<<\n 5. Exit\n");
                break;
            case(4):
                printf("\n 1. Sell\n 2. Buy potions\n 3. Buy armors\n 4. Buy weapons\n 5. Exit<<<\n");
                break;      
        }
        
        button = getch();
        
        switch(button)
        {
            case(W):
                if(select==0)
                select=4;
                else
                select--;
                break;
            case(S):
                if(select==4)
                select=0;
                else
                select++;
                break;
            case(ENTER):
                switch(select)
                {
                    case(0):
                        sell(profileName);
                        break;
                    case(1):
                        buy_items(profileName, "potions");
                        break;
                    case(2):
                        buy_items(profileName, "armors");
                        break;
                    case(3):
                        buy_items(profileName, "weapons");
                        break;
                    case(4):
                        return;
                        break;                    
                }
                break;
        }
    }
}

void buy_items(char *profileName, char *itemname) //Тут возможна ошибка
{
    //////////////////////////////
    //           DATA           //
    //////////////////////////////
    int level = get_intValue(profileName,"player_level");
    
    int gold = get_intValue(profileName,"gold");
    int mas_len = get_intValue(profileName,"inventory");
    ////////////////////////////////
    int *inventory = (int*)malloc(mas_len*sizeof(int));
    get_inventory(profileName,inventory);
    char **item_name = (char**)malloc(mas_len*sizeof(char*));
    printf("-----%d-----",mas_len);
    for(int i=0; i<mas_len; i++)
        item_name[i]=(char*)malloc(32*sizeof(char));
    int power[mas_len], cost[mas_len];

    get_item_info(inventory,item_name,power,cost,mas_len); // Тут ошибка

    ////////////////////////////////

    int select=0;//menu 
    char button;//attributes 
    
    FILE *items=fopen("items.txt","r");
    if(items==NULL)
    {
        //system("cls");
        system("clear");
        printf("items.txt not found");
        getch();
        return;
    }
    
    int mode=-1;
    if(strcmp(itemname,"potions")==0) //impossible to use switch-case
        mode=0;
    if(strcmp(itemname,"armors")==0)
        mode=1;
    if(strcmp(itemname,"weapons")==0)
        mode=2;
    if(mode==-1)//default
    {
        system("clear");
        //system("cls");
        printf("incorrect itemname: %s\n",itemname);
        getch();
        fclose(items);
        return;
    }
    
    int last_item_index;//potions_count
    int a,b; //                 [min, min + 1, ... , [a, ... , b] ... , max]
    int d; // delta(d)=b(beta)-a(alpha)               |__delta__|  
    
    switch(mode)
    {
        case 0:

            last_item_index=much_items("potions")-1;//first potion id = 0
            
            a=level/5-1;
            b=level/5+1;
            
            if(a<min_potions)
                a=min_potions;
            
            if(b>last_item_index)
                b=last_item_index;

            break;
        case 1:
            last_item_index=much_items("armors")+10;//first armor id = 10
            
            a=level/2-3+min_armors;
            b=level/2+3+min_armors;
            
            if(a<min_armors)
                a=min_armors;
            
            if(b>last_item_index)
                b=last_item_index;
            
            break;
        case 2:
            last_item_index=much_items("weapons")+50;//first potion id = 50
            a=level/2-3+min_weapons;
            b=level/2+3+min_weapons;
            
            if(a<min_weapons)
                a=min_weapons;
            
            if(b>last_item_index)
                b=last_item_index;
            
            break;
    }
    d=b-a+1;// delta(d)=b(beta)-a(alpha) + 1
    // count of [1;2] => 2-1+1=2    
    
    int sh_id[d]; //item ID (sh-shop)
    int sh_power[d]; //item POWER
    int sh_cost[d];//item COST
    char **sh_item_name = (char**)malloc(d*sizeof(char*));
    for(int i=0; i<d; i++)
        sh_item_name[i]=(char*)malloc(32*sizeof(char));
    //////////////////////////////
    //          END_DATA        //
    //////////////////////////////
    
    int have_scanned_count=0;
    for(int i=0; ;i++) //i - id-counter, d - memory size
    {
        int temp_ID, temp_POWER, temp_COST;
        char temp_item_name[32];

        //fscanf(items,"%d %s %d %d",&temp_ID, temp_item_name, &temp_POWER, &temp_COST);
        fscanf(items,"%d %s",&temp_ID, temp_item_name);

        if(temp_ID>b)
        break;
        
        if( (temp_ID>a)&&(strcmp(temp_item_name,"NULL")==0)  )
        break;
        
        if(have_scanned_count>=d)
        break;
        
        if(feof(items))
        break;
        
        if(strcmp(temp_item_name,"NULL")!=0)
        fscanf(items,"%d %d",&temp_POWER, &temp_COST);
        
        if(  (a<=temp_ID) && (temp_ID<=b) && (strcmp(temp_item_name,"NULL")!=0)  )
        {
            sh_id[have_scanned_count]=temp_ID;
            strcpy(sh_item_name[have_scanned_count],temp_item_name);
            sh_power[have_scanned_count]=temp_POWER;
            sh_cost[have_scanned_count]=temp_COST;
            have_scanned_count++;
        }
    }
    fclose(items);
    
    
    while(1)
    {
        //system("cls");
        system("clear");
        printf("Press ESC to exit\n");
        printf("YOUR GOLD: %d\n",gold);
        printf("\t\tNAME\t POWER\t COST\t\n\n");
        //printf("\n\tName\t\tPower\tCost\n");
        for(int i=0; i<d; i++)
        {
            printf("%18s\t %d\t %d", sh_item_name[i], sh_power[i], sh_cost[i]);
            if(select==i)
                printf("<<<");
            printf("\n");
        }
        
        printf("\nYOUR INVENTORY:\n\n");
        /*for(int i=0; i<mas_len; i++)
        {
            printf("%d. %d\n",i+1,inventory[i]);            
        }*/
        for(int i=0; i<mas_len; i++)
        {
            printf("%2d.%20s\t%3d\t%3d\n",i+1,item_name[i],power[i],cost[i]);
        }
        
        
        button=getch();
        switch(button)
        {
            case(W):
                if(select==0)
                select=d-1;
                else
                select--;
                break;
            case(S):
                if(select==d-1)
                select=0;
                else
                select++;
                break;
            case(ENTER):
                if(gold >= sh_cost[select])
                {
                    int slot=epmty_slot(inventory,mas_len);
                    if(slot==-1)
                        break;
                    gold-=sh_cost[select];
                    inventory[slot]=sh_id[select];
                    printf("%d slot ",slot);
                    //item_name[slot]=sh_item_name[select];
                    strcpy(item_name[slot],sh_item_name[select]);
                    power[slot]=sh_power[select];
                    cost[slot]=sh_cost[select];
                }
                break;
            case(ESC):
                set_inventory(profileName,inventory);
                set_intValue(profileName, "gold", gold);
                for(int i=0; i<d; i++)
                    free(sh_item_name[i]);
                for(int i=0;i<mas_len;i++)
                    free(item_name[i]);
                free(sh_item_name);
                free(item_name);
                free(inventory);
                return;
        }
    }   
}

int much_items(char *itemname)
{
    FILE *items = fopen("items.txt","r");
    if(items==NULL)
    {
        system("clear");
        //system("cls");
        printf("item.txt not found\n");
        getch();
        return -1;
    }
    int id, power, cost;
    char name[32];
    int result=0;
    
    int mode=-1;
    if(strcmp(itemname,"potions")==0) //impossible to use switch-case
    mode=0;
    if(strcmp(itemname,"armors")==0)
    mode=1;
    if(strcmp(itemname,"weapons")==0)
    mode=2;
    if(mode==-1)//default
    {
        system("clear");
        //system("cls");
        printf("incorrect itemname: %s\n",itemname);
        getch();
        fclose(items);
        return -1;
    }
        
    
    while(!feof(items))
    {
        fscanf(items,"%d%s",&id,name);
        if(strcmp(name,"NULL")!=0)
        fscanf(items,"%d%d",&power,&cost);
        
        switch(mode)
        {
            case 0:
                if( (id>=min_potions)&&(id<=max_potions)&&(strcmp(name,"NULL")!=0) )
                result++;
                break;
            case 1:
                if( (id>min_armors)&&(id<max_armors)&&(strcmp(name,"NULL")!=0) )
                result++;
                break;
            case 2:
                if( (id>min_weapons)&&(id<max_weapons)&&(strcmp(name,"NULL")!=0) )
                result++;
                break;
        }
        
    }
    fclose(items);
    return result;
}
         
           
