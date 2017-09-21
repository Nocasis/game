//work with maps
//void menu() Call this
#include "fight.c"
#include "play.c"


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



int Select_map(char *profile_name)
{
    int a=1, mapcount=much_maps(),flag;
    FILE *file_maps;
    char string[30],temp;
    file_maps = fopen("catalog.txt", "r");
    int map_level=get_intValue(profile_name,"map_level");
    while(1)
    {
        fseek(file_maps,0,SEEK_SET);
        system("clear");
        printf("\t\tChoice the map\n");
        flag=1;
        while(fscanf(file_maps,"%s",string)!=EOF)
        {
            printf("%s",string);
            if(flag==a)
                printf("<<<");
            flag++;
            printf("\n");
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
                if((a<=1)||(a>mapcount))
                    a=mapcount;
                else
                    a--;
                break;
            case S:
                if((a<1)||(a>=mapcount))
                    a=1;
                else
                    a++;
        }
    }
}


//main menu



void menu_list(int a)
{
    switch(a)
            {
                case 0:
                        printf("1.New Game<<<\n2.Select Map \n3.Map Creator\n4.About \n5.Exit\n");
                        break;
                case 1:
                        printf("1.New Game\n2.Select Map<<< \n3.Map Creator\n4.About \n5.Exit\n");
                        break;
                case 2:
                        printf("1.New Game\n2.Select Map \n3.Map Creator<<<\n4.About \n5.Exit\n");
                        break;

                case 3:
                        printf("1.New Game\n2.Select Map \n3.Map Creator\n4.About<<<\n5.Exit\n");
                        break;
                case 4:
                        printf("1.New Game\n2.Select Map\n3.Map Creator\n4.About\n5.Exit<<<\n");
                        break;
            }
}


int menu_select(int a)
{
    int menucount=4;
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


void menu(char *profile_name)  //Call this
{
    int Select=0,level=1;
    int what_exit;
    while(1)
    {
        Select=menu_select(Select);
        switch (Select)
        {
            case 0:
                system("clear");
                what_exit=play(level,profile_name);
                break;
            case 1:
                system("clear");
                level=Select_map(profile_name);
                if(level==0)
                    break;
                what_exit=play(level,profile_name);
                break;
            case 2:
                system("clear");
                mapGenerator();
                break;
            case 3:
                system("clear");
                printf("Test3");

                getch();
                break;
            case 4:
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

