#include <stdio.h>
#include <stdlib.h> //malloc

//catalog of the maps
#define list "catalog.txt"

//controls

#define ESC 27
#define W 119
#define A 97
#define S 115
#define D 100
#define SPACE 32
#define ENTER 13
#define TAB 9


//ojects numbers

#define total   6 //it must to be update when you add new objects 

#define empty   0
#define wall    1
#define finish  2 //finichCheck function use this item
#define coins   3
#define enemy   4
#define spawn   5

//view modes
#define SYM   0
#define NUM   1

void mapGenerator();//call this

int getValue(char *value, int left, int right);
int escMenu();
int Check(int height, int width, int **map, int check);
void generate(char *name);
void mapPrint(int height, int width, int **map, int mode, int x, int y, int symPos);

int checkMapName(char *mapname);
void add(char *name);


int getValue(char *value, int left, int right)
{
    int result;
    do
    {
        system("cls");
        printf("Enter the %s of the map [%d; %d]\n",value,left,right);
        scanf("%d",&result);
        if( (result>=left) && (result<=right) )
        return result;     
    }while(1);
}

int escMenu()
{
    int current=0;      //current menu item
    char temp;          //last button pressed
    do
    {
        system("cls");
        switch(current)
        {
            case(0):
                printf(" 1.Save and Quit<<<\n 2.Quit without saving\n 3.Cancel");
                break;
            case(1):
                printf(" 1.Save and Quit\n 2.Quit without saving<<<\n 3.Cancel");
                break;     
            case(2):
                printf(" 1.Save and Quit\n 2.Quit without saving\n 3.Cancel<<<");
                break;             
        }
        temp = getch();
        
        switch(temp)
        {
            case(ENTER):
                return current;
                break;
            case(W):
                if(current==0)
                current=2;
                else
                current--;
                break;     
            case(S):
                if(current==2)
                current=0;
                else
                current++;
                break;             
        }        
    }while(1);
    
}

int Check(int height, int width, int **map, int check)
{
    int i=0,j=0;
    for (i=0; i<height; i++)
    {
        for (j=0; j<width; j++)
        {
            if(map[i][j]==check)
            return 1;
        }
    }
    return 0; 
}

void mapPrint(int height, int width, int **map, int mode, int x, int y, int symPos)
{
    int i,j, temp;
    temp = map[x][y];   //����� �������� �� ������, ������ �������� ��������������� � ��� � �� � � ������
    map[x][y]=symPos;   //������� ���������� ������ ����� �������, ����� �� ������ ������ �������� ���� �����-����
                        //��� ���������� ������� ���� ����� ��������� ����� ������� :)
    for (i=0; i<height; i++)
    {
        for (j=0; j<width; j++)
        {
            switch(mode)
            {
                case(NUM):
                    if( (i==x)&&(j==y) )
                    printf("%d ",symPos);
                    else
                    printf("%1.1d ",map[i][j]);
                    break;
                case(SYM):
                    switch(map[i][j])
                    {
                        case(empty):
                            printf(" ");
                            break;
                        case(wall):
                            printf("#");
                            break;
                        case(finish):
                            printf("@");
                            break;
                        case(coins):
                            printf("$");
                            break;
                        case(enemy):
                            printf("E");
                            break;
                        case(spawn):
                            printf("S");
                            break; 
                    }
                    break;                
            }
            
            
        }
        printf("\n");
    }
    map[x][y]=temp;
    
}   


void generate(char *name)
{    
    int height, width, i, j;        //maps parametrs, counters
    
    width=getValue("Width",10, 35);
    height=getValue("Height",5, 25);

    int **map;
    map=(int**)malloc(sizeof(int*)*height);
    for (i=0; i<height; i++)
    map[i]=(int*)malloc(sizeof(int)*width);
    
    for (i=0; i<height; i++)
    {
        for (j=0; j<width; j++)
        {
            if((i==0)||(j==0)||(i==height-1)||(j==width-1))
            map[i][j]=wall;
            else
            map[i][j]=empty;
        }
    }    
    int mode=SYM;                   //mode of viewing map to console (NUMbers/SYMbols)
    int x=1,y=1,symPos=1;           //current coordinate and current symbol
    char button;                    //last pressed button               
    int flag=1;                     //flag of generating process: 1(true) - it should works, 0(false) - it should be finished
    short unsigned int sym[total]={empty,wall,finish,coins,enemy,spawn}; //actualy is useless, may be it should be removed later
    do                                                             //it can be usefull if we decide create map with the symbols and not from numbers
    {
        system("cls");
        mapPrint(height, width, map, mode, x, y, symPos); //it print the map [height][width] wtih mode (SYMbols or NUMbers) and on X,Y position put symPos        
        button=getch(); //what button pressed?
        switch(button)
        {
            case(ESC):
                switch(escMenu())   //start menu on ESC-button
                {
                    case(0):        //Save and Quit
                        if( (Check(height, width, map, finish)) && (Check(height, width, map, spawn)) )
                        {
                            FILE * gen = fopen(name, "w");
                            fprintf(gen,"%d %d\n",width,height);
                            for (i=0; i<height; i++)
                            {
                                for (j=0; j<width; j++)
                                {
                                    fprintf(gen,"%d ",map[i][j]); 
                                }
                                fprintf(gen,"\n");
                            }
                            fclose(gen);
                            flag=0;
                            add(name);
                            system("cls");
                            printf("Map is succesfull saved\n");
                            getch();
                            break;
                        }
                        else
                        {
                            system("cls");
                            printf("You should put at least 1 finish-block(2/@) and 1 spawn-block(5/S) \n");
                            getch();
                            break;                            
                        }

                    case(1):        //Quit without saving
                        flag=0;
                        system("cls");
                        break;
                    //case(2):                                                 
                }

                break;
            case(W):          
                if(x==1)
                x=height-2;
                else
                x--;
                break;
            case(S):          
                if(x==height-2)
                x=1;
                else x++;
                break;
            case(A):           
                if(y==1)
                y=width-2;
                else
                y--;
                break;
            case(D):             
                if(y==width-2)
                y=1;
                else
                y++;
                break;
            case(SPACE):               
                if(symPos==total-1)
                symPos=0;
                else
                symPos++;
                break;
            case(ENTER):
                map[x][y]=symPos;                              
                break;
            case (TAB):
                if(mode==SYM) mode=NUM; //sad, but this compiler dont support bool type, so i have to do this
                else mode=SYM;
                break;
            case(49):   // 1 (�� ��� ����� ������� ���� ����?)
                symPos=0;
                break;
            case(50):   // 2
                symPos=1;
                break;
            case(51):   // 3
                symPos=2;
                break; 
            case(52):   // 4
                symPos=3;
                break;
            case(53):   // 5
                symPos=4;
                break;
            case(54):   // 6
                symPos=5;
                break;        
        }   
               
    }while(flag);      
    
    for (i=0; i<height; i++)
    free(map[i]);
    free(map);
}

///////////////////////////////////////////
//�������� ����� ������� � ��������� ����//
///////////////////////////////////////////


//������� �������� ������� ���������� ����� ����� � �����-��������, ���������� 0 - ����� � ����� ��������� ��� ����, 1 - ����� ����� ���
int checkMapName(char *mapname)
{
//������� ����-����������
    FILE *catalog = fopen(list,"r");
    char getName[64];
//���� �� ������ ������� - ������ ��������� �� ������, ������� 0
//upd. ������� �������, ������� 1
    if(catalog==NULL)
    {
        /*printf("File %s not found\n",list);
        getch();*/
        freopen(list,"w",catalog);
        return 1;
    }

//� ����� ������������� ���������
    do
    {     
        fscanf(catalog,"%s", getName);
//���� ������� �������� ����������� � ��������, ������� ����, ������� 0           
        if(strcmp(getName,mapname)==0)
        {
            fclose(catalog);
            return 0;
        }
    }while(!feof(catalog));
//���� ����� �����, ������� ����, ������� 1
    fclose(catalog);
    return 1;      
}

//������� ���������� �������� ����� � �������
void add(char *name)
{
    FILE *catalog = fopen(list,"a");
    fprintf(catalog,"%s \n",name);
    fclose(catalog);
}

void mapGenerator()
{
    char mapName[64], format[5]=".txt";                       
    
    do//repeat until the mapname wil be input correct (presently it check only matches in catalog)
    {
        system("cls");
        printf("Enter map name (without .txt)\n");
        scanf("%s",mapName);
        strcat(mapName,format); // mapName = <mapName>+<.txt>

        if(checkMapName(mapName)) //checkMapName return 1 when mapname is not in the map catalog
        break;
        else
        {
            system("cls");
            printf("Incorrect name\n");
            getch();
        }
    }while(1);
    generate(mapName);
} 
    
