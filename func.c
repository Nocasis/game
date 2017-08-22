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

//work with maps



int much_maps()
{
    int a=0;
    FILE *file;
    char string[30];char temp;
    file = fopen("maps", "r");
    while(fscanf(file,"%s",string)!=EOF)
        a++;
    fclose(file);
    return a;
}



int Select_map()
{
    int a=1, mapcount=much_maps(),flag;
    FILE *file;
    char string[30],temp;
    //file = fopen("maps", "r");
    while(1)
    {
        file=fopen("maps","r");
        system("clear");
        printf("\t\tChoice the map\n");
        flag=1;
        while(fscanf(file,"%s",string)!=EOF)
        {
            printf("%s",string);
            if(flag==a)
                printf("<<<");
            flag++;
            printf("\n");
        }
        fclose(file);
        temp=getch();
        switch (temp)
        {
            case ENTER:
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
    return 0;
}


//main menu



void menulist(int a)
{
    switch(a)
            {
                case 0:
                        printf("1.New Game<<<\n2.Select Map \n3.Map Creator\n4.About \n5.Exit\n6.Test\n");
                        break;
                case 1:
                        printf("1.New Game\n2.Select Map<<< \n3.Map Creator\n4.About \n5.Exit\n6.Test\n");
                        break;
                case 2:
                        printf("1.New Game\n2.Select Map \n3.Map Creator<<<\n4.About \n5.Exit\n6.Test\n");
                        break;

                case 3:
                        printf("1.New Game\n2.Select Map \n3.Map Creator\n4.About<<<\n5.Exit\n6.Test\n");
                        break;
                case 4:
                        printf("1.New Game\n2.Select Map\n3.Map Creator\n4.About\n5.Exit<<<\n6.Test\n");
                        break;
                case 5:
                        printf("1.New Game\n2.Select Map \n3.Map Creator\n4.About\n5.Exit\n6.Test<<<\n");
                        break;
            }
}


int menu(int a)
{
    char temp;
    while(1)
    {
        system("clear");
        printf("\t\t The Game \n\n");
        menulist(a);
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

