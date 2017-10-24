#include <stdio.h>
#include <string.h>
#include <stdlib.h>


#define Pcatalog "profiles.txt"

//controls

#define ESC 27
#define W 119
#define A 97
#define S 115
#define D 100
#define SPACE 32
#define ENTER 10
#define TAB 9
#define BackSpace 8

const int len=32;
const int attack=10, defence=10, inventory=5, hp=100; //default profile parametrs

char *profile_menu(); //call this (it return current profile_name)

//char *name=(char *)malloc(32*sizeof(char));
//name = profile_menu();

int get_intValue(char *profileName, char *valueName);
char *get_stringValue(char *profileName, char *valueName);

void get_inventory(char *profileName, int *inventory);
void set_inventory(char *profileName, int *inventory);
int empty_slot(int *inventory, int size); //return nearest empty slot

void set_Value(char *profileName, char *valueName, char *value);
void set_intValue(char *profileName, char *valueName, int value);


int check_profile(char *profile);   //Check profile availabiliy
void add_profile(char *profile);    //Add profile to directory
int much_profiles();                //Profiles count

char *new_profile();                 //Create new profile (it return created profile_name)
char *log_in_menu();                //log in, return current profile

int isCorrect(char sym);
int user_input(char *string, int size, char *Message);


char *profile_menu()
{
    int current=0;
    char button;
    
    while(1)
    {
        system("cls");
        //system("clear");
        
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
                return log_in_menu();
                else
                return new_profile();
                break;
        }
        
    }
    
}

char *log_in_menu()
{
    char *name, *password, *temp;
    name=(char *)malloc(len*sizeof(char));
    password=(char *)malloc(len*sizeof(char));
    temp=(char *)malloc(len*sizeof(char));
    char format[5]=".txt";
    
    FILE *profile = fopen(Pcatalog,"r");
    if(profile==NULL)
    {
        system("cls");
        //system("clear");
        printf("data is not found, create new profile\n");
        getch();
        return new_profile();
    }
    
    while(1)
    {
        fseek(profile,0,SEEK_SET);
        system("cls");
        //system("clear");
        

        user_input(name,len-5,"Enter your profilename");//input profilename
        strcat(name,format);
        
        user_input(password,len-5,"Enter your password");//input password  
        
        while(!feof(profile))
        {
            fscanf(profile,"%s",temp);
            if(strcmp(name,temp)==0)
            {
                temp=get_stringValue(name, "password");
                if(strcmp(password,temp)==0)
                {
                    free (password);
                    free(temp);
                    fclose(profile);
                    return name;
                }               
            }
        }
        
        printf("\nIncorrect login or passwrod\n");
        getch();        
    }
    
}

char *new_profile()
{
    //char name[len], format[5]=".txt";
    char *name=(char *)malloc(len*sizeof(char));
    char format[5]=".txt";
    char name1 [32];
    int i;
    while(1)
    {
        //system("cls");
        system("clear");
        
        user_input(name,len-5,"Enter your profilename");//input profilename
        strcat(name,format);
        
        if(check_profile(name))
        {
            char *password;
            password=(char *)malloc(len*sizeof(char));
            system("cls");
            //system("clear");
            
            user_input(password,len-5,"Enter your password");//input password
            
            add_profile(name);
            FILE * new_profile = fopen(name,"w");
            fprintf(new_profile,"password %s\n",password);
            fprintf(new_profile,"map_level 1\n");
            fprintf(new_profile,"player_level 1\n");
            fprintf(new_profile,"attack %d\n",attack);
            fprintf(new_profile,"defence %d\n",defence);
            fprintf(new_profile,"skill_points 0\n");
            
            fprintf(new_profile,"inventory %d\n",inventory);
            for(i=0; i<inventory; i++)
            fprintf(new_profile,"-1 ");
            fprintf(new_profile,"\n");
            
            fprintf(new_profile,"current_armor -1\n");
            fprintf(new_profile,"current_weapon -1\n");
            
            fprintf(new_profile,"experience 0\n");
            fprintf(new_profile,"gold 0\n");
            fprintf(new_profile,"hp %d\n",hp);
            
            
            free(password);
            fclose(new_profile);
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

int check_profile(char *profile)
{

    FILE *catalog = fopen(Pcatalog,"r");
    char getName[64];
    if(catalog==NULL) //if there is no file
    {
        fopen(Pcatalog,"w");  //create it
        return 1;                   //return 1 because the catalog is empty
    }

    do
    {     
        fscanf(catalog,"%s", getName);     
        if(strcmp(getName,profile)==0)
        {
            fclose(catalog);
            return 0;
        }
    }while(!feof(catalog));
    
    fclose(catalog);
    return 1;        
}

//add profile in catalog
void add_profile(char *profile)
{
    FILE *catalog = fopen(Pcatalog,"a");
    fprintf(catalog,"%s \n",profile);
    fclose(catalog);
}

int much_profiles()
{
    int count=0;
    FILE *catalog;
    char string[30];
    catalog = fopen(Pcatalog, "r");
    
    if(catalog==NULL)
    return 0; //there are no profiles

    while(fscanf(catalog,"%s",string)!=EOF)
        count++;
    fclose(catalog);
    return count;
}


int get_intValue(char *profileName, char *valueName)
{
    int result;
    char *currentValueName = (char *)malloc(len*sizeof(char));
    FILE *config =fopen(profileName,"r");
    if (config==NULL)
    {
        system("clear");
        //system("cls");
        printf("incorect profileName\n");
        getch();
        return 0;//incorect profileName
    }
    
    while (!feof(config))
    {
        fscanf(config,"%s", currentValueName);
        fscanf(config,"%d", &result);
        if(strcmp(currentValueName,valueName)==0)
        {
            fclose(config);
            return result;
        }                    
    }
    
    printf("incorect valueName\n");
    getch();
    fclose(config);
    return 0;
    
}

char *get_stringValue(char *profileName, char *valueName)
{
    char *result = (char *)malloc(len*sizeof(char));
    char *currentValueName = (char *)malloc(len*sizeof(char));
    FILE *config =fopen(profileName,"r");
    if (config==NULL)
    return "\0";//incorect profileName
    
    while (!feof(config))
    {
        fscanf(config,"%s", currentValueName);
        fscanf(config,"%s", result);
        if(strcmp(currentValueName,valueName)==0)
        {
            fclose(config);
            return result;
        }                    
    }
    fclose(config);
    return "\0"; //incorect valueName        
}

void get_inventory(char *profileName, int *inventory)
{
    int size;
    char *currentValueName = (char *)malloc(len*sizeof(char));
    FILE *config =fopen(profileName,"r");
    if (config==NULL)
    {
        system("clear");
        //system("cls");
        printf("incorect profileName\n");
        getch();
        return;//incorect profileName
    }
    while (!feof(config)) //С‚СѓС‚ РІС‹Р»РµС‚
    {

        fscanf(config,"%s", currentValueName);
        if(strcmp(currentValueName,"inventory")==0)
        {
            fscanf(config,"%d", &size);
            for(int i=0; i<size; i++)
            fscanf(config,"%d", &inventory[i]);
            return;            
        }
    }
    fclose(config);    
}

void set_Value(char *profileName, char *valueName, char *value)
{
    FILE *prim =fopen(profileName,"r");
    FILE *temp =fopen("system_temp.txt","w");
    char *string = (char*)malloc(len*sizeof(char));
    int itemp;
    
    fscanf(prim,"%s", string);//"password"
    if(strcmp(string,valueName)==0)
    {
        fprintf(temp,"password %s\n",value);//print new value
        fscanf(prim,"%s", string);//old-value
    }
    else
    {    
        fscanf(prim,"%s", string);//value
        fprintf(temp,"password %s\n",string);
    }
    
    for(int i=0; i<11; i++)
    {
        fscanf(prim,"%s", string);
        fscanf(prim,"%d", &itemp);
        
        if(strcmp(string,valueName)==0)
        fprintf(temp,"%s %d\n",string,value);
        else
        fprintf(temp,"%s %d\n",string,itemp);
        
        if(strcmp(string,"inventory")==0)
        {
            for(int j=0; j<itemp; j++)
            {
                int mas;
                fscanf(prim,"%d", &mas);
                fprintf(temp,"%d ",mas);
            }
            fprintf(temp,"\n");
        }
        
    }
    freopen(profileName,"w",prim);
    freopen("system_temp.txt","r",temp);
    
    fscanf(temp,"%s", string);//"password"
    fscanf(temp,"%s", string);//value
    fprintf(prim,"password %s\n",string);
    
    for(int i=0; i<11; i++)
    {
        fscanf(temp,"%s", string);
        fscanf(temp,"%d", &itemp);
        
        fprintf(prim,"%s %d\n",string,itemp);
        
        if(strcmp(string,"inventory")==0)
        {
            for(int j=0; j<itemp; j++)
            {
                int mas;
                fscanf(temp,"%d", &mas);
                fprintf(prim,"%d ",mas);
            }
            fprintf(prim,"\n");
        }
        
    }
    free(string);
    fclose(prim);
    fclose(temp);
    
}

void set_intValue(char *profileName, char *valueName, int value) //РўСѓС‚ РІРѕР·РјРѕР¶РЅР° РѕС€РёР±РєР°---РЅРµС‚ С‚СѓС‚ РѕС€РёР±РєРё
{
    FILE *prim =fopen(profileName,"r");
    FILE *temp =fopen("system_temp.txt","w");
    char *string = (char*)malloc(len*sizeof(char));
    int itemp;
    
    fscanf(prim,"%s", string);//"password"
    fscanf(prim,"%s", string);//value
    fprintf(temp,"password %s\n",string);
    for(int i=0; i<11; i++)
    {
        fscanf(prim,"%s", string);
        fscanf(prim,"%d", &itemp);
        
        if(strcmp(string,valueName)==0)
        fprintf(temp,"%s %d\n",string,value);
        else
        fprintf(temp,"%s %d\n",string,itemp);
        
        if(strcmp(string,"inventory")==0)
        {
            for(int j=0; j<itemp; j++)
            {
                int mas;
                fscanf(prim,"%d", &mas);
                fprintf(temp,"%d ",mas);
            }
            fprintf(temp,"\n");
        }
        
    }
    freopen(profileName,"w",prim);
    freopen("system_temp.txt","r",temp);
    fscanf(temp,"%s", string);//"password"
    fscanf(temp,"%s", string);//value
    fprintf(prim,"password %s\n",string);
    
    for(int i=0; i<11; i++)
    {
        fscanf(temp,"%s", string);
        fscanf(temp,"%d", &itemp);
        
        fprintf(prim,"%s %d\n",string,itemp);
        
        if(strcmp(string,"inventory")==0)
        {
            for(int j=0; j<itemp; j++)
            {
                int mas;
                fscanf(temp,"%d", &mas);
                fprintf(prim,"%d ",mas);
            }
            fprintf(prim,"\n");
        }
        
    }
    free(string);
    fclose(prim);
    fclose(temp);
}

void set_inventory(char *profileName, int *inventory) //РўСѓС‚ РІРѕР·РјРѕР¶РЅРѕ РѕС€РёР±РєР°, РІС‹Р»РµС‚РѕРІ СЃ armor Рё def, С‡РёСЃС‚Рѕ РґР»СЏ potion
{
    FILE *prim =fopen(profileName,"r");
    FILE *temp =fopen("system_temp.txt","w");
    char *string = (char*)malloc(len*sizeof(char));
    int itemp;
    
    fscanf(prim,"%s", string);//"password"
    fscanf(prim,"%s", string);//value
    fprintf(temp,"password %s\n",string);
    
    for(int i=0; i<11; i++)
    {
        fscanf(prim,"%s", string);
        fscanf(prim,"%d", &itemp);
        fprintf(temp,"%s %d\n",string,itemp);
        
        if(strcmp(string,"inventory")==0)
        {
            for(int j=0; j<itemp; j++)
            {
                int mas;
                fscanf(prim, "%d",&mas);
                fprintf(temp,"%d ",inventory[j]);
            }
            
            fprintf(temp,"\n");
        }
    }
    freopen(profileName,"w",prim);
    freopen("system_temp.txt","r",temp);
    fscanf(temp,"%s", string);//"password"
    fscanf(temp,"%s", string);//value
    fprintf(prim,"password %s\n",string);
    for(int i=0; i<11; i++)
    {
        fscanf(temp,"%s", string);
        fscanf(temp,"%d", &itemp);
        
        fprintf(prim,"%s %d\n",string,itemp);
        
        if(strcmp(string,"inventory")==0)
        {
            for(int j=0; j<itemp; j++)
            {
                int mas;
                fscanf(temp,"%d", &mas);
                fprintf(prim,"%d ",mas);
            }
            fprintf(prim,"\n");
        }
        
    }
    free(string);
    fclose(prim);
    fclose(temp);
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
        system("cls");
        //system("clear");
        printf("%s\n",Message);
        for(int i=0; i<count; i++)
        printf("%c",string[i]);
        //printf("*");
        
        button = getch();
        switch(button)
        {
            /*case(ESC):
                strcpy(string,"");
                return 0;//отмена ввода
                break;*/
            case(ENTER):
                if(count>2)
                    return 1;//ввод корректно завршен
                else
                    printf("\nToo short\n");
                    getch();
                break;
            case(BackSpace)://удалить крайний правый символ
                count--;
                string[count]='\0';
                break;
            default://добавить корректный символ
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
