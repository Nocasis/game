#include <stdio.h>
#include <string.h>
#include <stdlib.h>

//controls

#define ESC 27
#define W 119
#define A 97
#define S 115
#define D 100
#define SPACE 32
#define ENTER 10
#define TAB 9
#define BackSpace 127

const int len=32;
const int attack=12, defence=11, inventory=5, hp=110; //default profile parametrs

char *profile_menu(MYSQL *mysql); //call this (it return current profile_name)

//char *name=(char *)malloc(32*sizeof(char));
//name = profile_menu();

int get_intValue(MYSQL *mysql,char *profileName, char *valueName);
char *get_stringValue(MYSQL *mysql,char *profileName, char *valueName);

void get_inventory(MYSQL *mysql,char *profileName, int *inventory);
void set_inventory(MYSQL *mysql,char *profileName, int *inventory);
int empty_slot(int *inventory, int size); //return nearest empty slot

void set_intValue(MYSQL *mysql,char *profileName, char *valueName, int value);


int check_profile(MYSQL *mysql,char *profile);   //Check profile availabiliy
//void add_profile(char *profile);    //Add profile to directory

char *new_profile(MYSQL *mysql);                 //Create new profile (it return created profile_name)
char *log_in_menu(MYSQL *mysql);                //log in, return current profile

int isCorrect(char sym);
int user_input(char *string, int size, char *Message);


char *profile_menu(MYSQL *mysql)
{
    int current=0;
    char button;
    
    while(1)
    {
        //system("cls");
        system("clear");
        
        if(current==0)
        printf("Log In<<<\nSign Up\n");
        else
        printf("Log In\nSign Up<<<\n");
        
        button=getch();
        
        switch(button)
        {
            case(W):
                if(current==0)
                current=1;
                else
                current=0;
                break;
            case(S):
                if(current==0)
                current=1;
                else
                current=0;
                break;
            case(ENTER):
                if(current==0)
                return log_in_menu(mysql);
                else
                return new_profile(mysql);
        }
        
    }
    
}

char *log_in_menu(MYSQL *mysql)
{
    char *name, *password, *temp,*req;
    MYSQL_ROW row;
    name=(char *)malloc(len*sizeof(char));
    password=(char *)malloc(len*sizeof(char));
    temp=(char *)malloc(len*sizeof(char));
    req=(char *)malloc(80*sizeof(char));
    MYSQL_RES *result;


    while(1)
    {
        system("clear");

        user_input(name,len,"Enter your profilename");//input profilename
        
        user_input(password,len,"Enter your password");//input password
        //printf("\nname %s pswd %s,temp %s",name,password,temp);
        //getch();


        sprintf(req,"SELECT EXISTS(SELECT name FROM user_profile WHERE name=\"%s\")",name);
        if(mysql_query(mysql,req))
            exit(1);
        result = mysql_store_result(mysql);
        row = mysql_fetch_row(result);
        mysql_free_result(result);
        strcpy(temp,row[0]);

        if(atoi(temp))
        {
                sprintf(req,"SELECT password from user_profile where name=\"%s\"",name);
                if(mysql_query(mysql,req))
                    exit(1);
                result = mysql_store_result(mysql);
                row = mysql_fetch_row(result);
                strcpy(temp,row[0]);
                mysql_free_result(result);
                if(strcmp(password,temp)==0)
                {
                    free (password);
                    free(temp);
                    return name;
                }
        }

        printf("\nIncorrect login or password\n");
        getch();
    }
    
}

char *new_profile(MYSQL *mysql)
{
    //char name[len], format[5]=".txt";
    char *name=(char *)malloc(len*sizeof(char));
    //char format[5]=".txt";
    char name1 [32];
    int i;
    while(1)
    {
        //system("cls");
        system("clear");
        
        user_input(name,len,"Enter your profilename");//input profilename
        //strcat(name,format);
        
        if(check_profile(mysql,name))
        {
            char *password;
            char *tmp;
            tmp=(char *)malloc(400*sizeof(char));
            password=(char *)malloc(len*sizeof(char));
            //system("cls");
            system("clear");
            
            user_input(password,len,"Enter your password");//input password
            //printf("--\n%s--%s--%d--%d--%d--\n",name,password,attack,defence,inventory);
            //getch();		
            //add_profile(name);

            sprintf(tmp,"INSERT INTO user_profile ("
                    "name,"
                    "password,"
                    "map_level,"
                    "player_level,"
                    "attack,"
                    "defence,"
                    "skill_points,"
                    "inventory,"
                    "inventory_slot_1,"
                    "inventory_slot_2,"
                    "inventory_slot_3,"
                    "inventory_slot_4,"
                    "inventory_slot_5,"
                    "current_armor,"
                    "current_weapon,"
                    "experience,"
                    "gold,"
                    "hp) VALUES (\"%s\",\"%s\",%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d)",name,password,1,1,attack,defence,0,inventory,-1,-1,-1,-1,-1,-1,-1,0,0,hp);
            if(mysql_query(mysql,tmp))
                exit(1);
            getch();
            free(tmp);
            free(password);
            return name;
                                 
        }
        else
        {
            //system("cls");
            system("clear");
            printf("Incorrect name\n");
            getch();
        }
    }
    
}

int check_profile(MYSQL *mysql,char *profile)
{
    char *name, *password, *temp,*req;
    MYSQL_ROW row;
    temp=(char *)malloc(len*sizeof(char));
    req=(char *)malloc(100*sizeof(char));
    MYSQL_RES *result;

    sprintf(req,"SELECT EXISTS(SELECT name FROM user_profile WHERE name=\"%s\")",profile);
    if(mysql_query(mysql,req))
        exit(1);
    result = mysql_store_result(mysql);
    row = mysql_fetch_row(result);
    mysql_free_result(result);
    strcpy(temp,row[0]);
    if(atoi(temp))
        return 0;
    return 1;        
}


//ЗАВТРА везде ниже добавить mysql

int get_intValue(MYSQL *mysql,char *profileName, char *valueName)
{
    int result;
    char *req = (char *)malloc(80*sizeof(char));
    char *tmp = (char *)malloc(len*sizeof(char));
    MYSQL_ROW row;
    MYSQL_RES *mysql_result;
    sprintf(req,"SELECT %s FROM user_profile WHERE name=\"%s\"",valueName,profileName);
    if(mysql_query(mysql,req))
        exit(1);
    mysql_result = mysql_store_result(mysql);
    row = mysql_fetch_row(mysql_result);
    strcpy(tmp,row[0]);
    result = atoi(tmp);
    mysql_free_result(mysql_result);
    free(req);
    free(tmp);
    return result;
}

char *get_stringValue(MYSQL *mysql,char *profileName, char *valueName)
{
    char *result = (char *)malloc(len*sizeof(char));
    char *req = (char *)malloc(80*sizeof(char));
    char *tmp = (char *)malloc(len*sizeof(char));
    MYSQL_ROW row;
    MYSQL_RES *mysql_result;
    sprintf(req,"SELECT %s FROM user_profile WHERE name=\"%s\"",valueName,profileName);
    if(mysql_query(mysql,req))
        exit(1);
    mysql_result = mysql_store_result(mysql);
    row = mysql_fetch_row(mysql_result);
    strcpy(result,row[0]);
    mysql_free_result(mysql_result);
    free(req);
    free(tmp);
    free(result);
    return result;

}

void get_inventory(MYSQL *mysql,char *profileName, int *inventory)
{
    int size;
    char *req = (char *)malloc(90*sizeof(char));
    char *tmp = (char *)malloc(len*sizeof(char));
    MYSQL_ROW row;
    MYSQL_RES *mysql_result;
    sprintf(req,"SELECT inventory FROM user_profile WHERE name=\"%s\"",profileName);
    if(mysql_query(mysql,req))
        exit(1);
    mysql_result = mysql_store_result(mysql);
    row = mysql_fetch_row(mysql_result);
    strcpy(tmp,row[0]);
    size = atoi(tmp);
    mysql_free_result(mysql_result);
    for(int i = 0,j = 1; i < size; i++,j++)
    {
        sprintf(req,"SELECT inventory_slot_%d FROM user_profile WHERE name=\"%s\"",j,profileName);
        if(mysql_query(mysql,req))
            exit(1);
        mysql_result = mysql_store_result(mysql);
        row = mysql_fetch_row(mysql_result);
        strcpy(tmp,row[0]);
        inventory[i] = atoi(tmp);
    }
    mysql_free_result(mysql_result);
    free(req);
    free(tmp);
    return;

}


void set_intValue(MYSQL *mysql,char *profileName, char *valueName, int value)
{
    char *req = (char *)malloc(100*sizeof(char));
    sprintf(req,"UPDATE user_profile SET %s=%d WHERE name=\"%s\"",valueName,value,profileName);
    if(mysql_query(mysql,req))
        exit(1);
    free(req);
    return;
}

void set_inventory(MYSQL *mysql,char *profileName, int *inventory)
{
    int size;
    char *req = (char *)malloc(90*sizeof(char));
    char *tmp = (char *)malloc(len*sizeof(char));
    MYSQL_ROW row;
    MYSQL_RES *mysql_result;
    sprintf(req,"SELECT inventory FROM user_profile WHERE name=\"%s\"",profileName);
    if(mysql_query(mysql,req))
        exit(1);
    mysql_result = mysql_store_result(mysql);
    row = mysql_fetch_row(mysql_result);
    strcpy(tmp,row[0]);
    size = atoi(tmp);
    mysql_free_result(mysql_result);
    for(int i = 0,j = 1;i < size; i++,j++)
    {
        sprintf(req,"UPDATE user_profile SET inventory_slot_%d=%d WHERE name=\"%s\"",j,inventory[i],profileName);
        if(mysql_query(mysql,req))
            exit(1);
    }
    free(req);
    free(tmp);
    return;
}

int empty_slot(int *inventory, int size)
{
    for(int i=0; i<size; i++)
    {
        if(inventory[i]==-1)
        return i;
    }
    return -1;
}

int isCorrect(char sym)
{
    //      a               z           A           Z               0           9
    if(  ((sym>=97)&&(sym<=122)) || ((sym>=65)&&(sym<=90)) || ((sym>=48)&&(sym<=57))  )
    return 1;
    else
    return 0;
}

int user_input(char *string, int size, char *Message)
{
    char button;
    int count=0;
    strcpy(string,"");
    
    while(1)
    {
        system("clear");
        printf("%s\n",Message);
        for(int i=0; i<count; i++)
        printf("%c",string[i]);
        
        button = getch();
        switch(button)
        {
            case(ENTER):
                if(count>2)
                    return 1;
                else
                    printf("\nToo short\n");
                    getch();
                break;
            case(BackSpace):
                count--;
                string[count]='\0';
                break;
            default:
                if(isCorrect(button))
                {
                    if(count<size-1)
                    {
                        string[count]=button;
                        count++;
                        string[count]='\0';
                    }
                    else
                    {
                        printf("\nIts limited to %d characters", size-1);
                        getch();   
                    }
                }
                else
                {
                    printf("\nIncorrect symbol!\n");
                    getch();                    
                }
                break;            
        }
    }
    return 1;
}

