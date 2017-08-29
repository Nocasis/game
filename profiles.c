#include <stdio.h>
#include <string.h>
#include <stdlib.h> //malloc
//#include <conio.h> //getch()

#define file "profiles.txt"

//controls

#define ESC 27
#define W 119
#define A 97
#define S 115
#define D 100
#define SPACE 32
#define ENTER 13
#define TAB 9

const int len=32;
const int attack=10, defence=5, inventory=5; //default profile parametrs

char *profile_menu(); //call this (it return current profile_name)

//char *name=(char *)malloc(32*sizeof(char));
//name=profile_menu();


int check_profile(char *profile);   //проверить есть ли такой профиль
void add_profile(char *profile);    //добавить профиль в каталог
int much_profiles();                //количество профилей в каталоге
int getValue(char *name, char* filename);

char *new_profile();                 //создание новго профиля



char *profile_menu()
{    
    int count=much_profiles()+1;
    
    FILE *profile = fopen(file,"r");
    if(profile==NULL)
    {
        printf("There are no profiles \n Create new\n");
        getch();
        return new_profile();
    }
    
    int i;
    char **names;                             
    names=(char **)malloc(count*sizeof(char *));
    for(i=1;i<count;i++)
    names[i]=(char *)malloc(len*sizeof(char));
    
    char *result=(char *)malloc(len*sizeof(char));
    
    names[0]="New profile";
    
    for(i=1;i<count;i++)
    fscanf(profile,"%s",names[i]);
    
    fclose(profile);
    
    char button;
    int current=0;
    /////////////////////////////////
    while(1)
    {
        system("cls");
        for(i=0;i<count;i++)
        {
            printf("%d. %s ",i,names[i]);
            if(current==i)
            printf("<<<");
            
            printf("\n");
        }
        
        button=getch();
        switch(button)
        {
            case(W):
                if(current==0)
                current=count-1;
                else
                current--;
                break;
            case(S):
                if(current==count-1)
                current=0;
                else
                current++;
                break;
            case(ENTER): //не забыть освободить память!
                if(current==0)
                {
                    for(i=0; i<count; i++)
                    free(names[i]);
                    free(names);
                    return new_profile();
                }
                
                char pass[len], temp[len];
 
 /////////////////////////////////////////////////////////////////               
                FILE *config =fopen(names[current],"r");
                if (config==NULL)
                {
                    printf("\nerror\n");
                    getch();
                    break;
                }
                while (!feof(config))
                {
                    fscanf(config,"%s", temp);
                    fscanf(config,"%s", pass);
                    if(strcmp(temp,"password")==0)
                    break;                    
                }
////////////////////////////////////////////////////////////////////                
                while(1)
                {
                    char password[len];
                    system("cls");
                    printf("Enter password: ");
                    fgets(password,len,stdin);
                    for(i=0;i<len;i++)
                    {
                        if(password[i]=='\0')
                        password[i-1]='\0';
                    }
                    if(strcmp(password,pass)==0)
                    {
                        strcpy(result,names[current]);
                        return result;
                    }
               }    

                strcpy(result,names[current]);
                return result;
        }       
        
    }
    //return " ";
    
}

char *new_profile()
{
    //char name[len], format[5]=".txt";
    char *name=(char *)malloc(len*sizeof(char));
    char format[5]=".txt";
    
    int i;
    while(1)
    {
        system("cls");
        printf("Enter your profile name: ");
        fgets(name,len-5,stdin);
        for(i=0;i<len;i++)
        {
            if(name[i]=='\0')
            name[i-1]='\0';
        }
        strcat(name,format);
        if(check_profile(name))
        {
            char password[len];
            system("cls");
            printf("Enter your password: ");
            fgets(password,len,stdin);
            for(i=0;i<len;i++)
            {
                if(password[i]=='\0')
                password[i-1]='\0';
            }
            
            //it need check for empty password
            
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
            fprintf(new_profile,"0 ");
            fprintf(new_profile,"\n");
            
            fprintf(new_profile,"current_armor -1\n");
            fprintf(new_profile,"current_weapon -1\n");
            
            fclose(new_profile);
            return name;
                                 
        }
        else
        {
            system("cls");
            printf("Incorrect name\n");
            getch();
        }
    }
    
}

int check_profile(char *profile)
{

    FILE *catalog = fopen(file,"r");
    char getName[64];

    if(catalog==NULL) //if there is no file
    {
        freopen(file,"w",catalog);  //create it
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
    FILE *catalog = fopen(file,"a");
    fprintf(catalog,"%s \n",profile);
    fclose(catalog);
}

int much_profiles()
{
    int count=0;
    FILE *catalog;
    char string[30];
    catalog = fopen(file, "r");
    
    if(catalog==NULL)
    return 0; //there are no profiles

    while(fscanf(catalog,"%s",string)!=EOF)
        count++;
    fclose(catalog);
    return count;
}

