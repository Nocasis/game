//work with maps
//void menu() Call this
#include "play.c"



int much_maps();
int Select_map(MYSQL *mysql,char *profile_name);
void menu_list(int a);
int menu_select(int a);
void menu(MYSQL *mysql,char *profile_name);


int much_maps()
{
    int a=0;
    int i=0;
    FILE *file_maps;
    char string[30];
    file_maps = fopen("catalog.txt", "r"); //Тут менять название файла с картами.
    if(file_maps==NULL)
        return 0;
    while(fscanf(file_maps,"%s",string)!=EOF)
        a++;
    fclose(file_maps);
    return a;
}



int Select_map(MYSQL *mysql,char *profile_name)
{
    int a=1, mapcount=much_maps(),flag,i,j=1;
    FILE *file_maps;
    char string[30],temp;
    file_maps = fopen("catalog.txt", "r");
    int map_level=get_intValue(mysql,profile_name,"map_level");
    while(1)
    {
        fseek(file_maps,0,SEEK_SET);
        system("clear");
        printf("\t\tChoice the map.\n\t\tYour map_level: %d\n\tUse A and D buttons to list maps\n",map_level);
        flag=1;
        i=1;
        while(fscanf(file_maps,"%s",string)!=EOF)
        {
            if((j <= i) && (i<= j+29))
            {
                printf("%d.%s", i, string);
                if (flag == a)
                    printf(" <<<");
                printf("\n");
            }
            flag++;
            i++;
        }
        temp=getch();
        switch (temp)
        {
            case ESC:
                fclose(file_maps);
                return 0;
            case ENTER:
                fclose(file_maps);
                if(a>map_level)
                {
                    printf("You cant play this map");
                    getch();
                    return 0;
                }
                return a;
            case W:
                if((a<=j)||(a>j+30))
                    //a=mapcount;
                    a=j+29;
                else
                    a--;
                break;
            case S:
                if((a<1)||(a>=mapcount)||(a>j+28))
                    a=j;
                else
                    a++;
                break;
            case A:
                if(j <= 1)
                    j = 1;
                else
                {
                    j -= 30;
                    //flag -= 30;
                    a -= 30;
                }
                break;
            case D:
                if(j + 30 > 1000)
                j = 1000;

                else
                {
                    j += 30;
                    //flag += 30;
                    a += 30;
                }
        }
    }
}


//main menu



void menu_list(int a)
{
    switch(a)
            {
                case 0:
                        printf("New Game<<<\nSelect Map \nExit\n");
                        break;
                case 1:
                        printf("New Game\nSelect Map<<< \nExit\n");
                        break;
                case 2:
                        printf("New Game\nSelect Map \nExit<<<\n");
                        break;
            }
}


int menu_select(int a)
{
    int menucount=2;
    char temp;
    while(1)
    {
        system("clear");
        printf("\t\t The Game \n\n");
        menu_list(a);
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


void menu(MYSQL *mysql,char *profile_name)  //Call this
{
    int Select=0,level=1;
    int what_exit=1;
    while(1)
    {
        level = 1;
        Select=menu_select(Select);
        switch (Select)
        {
            case 0:
                system("clear");
                while(what_exit == 1)
                {
                    if(level > 1)
                        town(mysql,profile_name);
                    what_exit = play(mysql,level, profile_name);
                    level++;
                }
                what_exit = 1;
                level = 1;
                break;
            case 1:
                system("clear");
                level = Select_map(mysql, profile_name);
                if(level == 0)
                    break;
                while(what_exit == 1)
                {
                    what_exit = play(mysql, level, profile_name);
                    level++;
                    if(level > 1 && what_exit == 1)
                        town(mysql,profile_name);
                }
                what_exit = 1;
                level = 1;
                break;
            case 2:
                system("clear");
                return;
            default:
                printf("Error");
                getch();
                return;
        }
    }
    getch();
    return;
}

