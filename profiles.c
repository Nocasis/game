#include <stdio.h>
#include <string.h>
#include <stdlib.h> //malloc


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

const int len=32;
const int attack=10, defence=5, inventory=5, hp=100; //default profile parametrs

char *profile_menu(); //call this (it return current profile_name)

//char *name=(char *)malloc(32*sizeof(char));
//name=profile_menu();

int get_intValue(char *profileName, char *valueName);
char *get_stringValue(char *profileName, char *valueName);

void get_inventory(char *profileName, int *inventory);
void set_inventory(char *profileName, int *inventory);
int epmty_slot(int *inventory, int size); //return nearest empty slot

void set_Value(char *profileName, char *valueName, char *value);
void set_intValue(char *profileName, char *valueName, int value);


int check_profile(char *profile);   //Check profile availabiliy
void add_profile(char *profile);    //Add profile to directory
int much_profiles();                //Profiles count

char *new_profile();                 //Create new profile (it return created profile_name)



char *profile_menu()
{    
    int count=much_profiles()+1;
    
    FILE *profile = fopen(Pcatalog,"r");
    if(profile==NULL)
    {
        printf("There are no profiles \nCreate new\n");
        getch();
        return new_profile();
    }
    
    int i;
    char **names;                             
    names=(char **)malloc(count*sizeof(char *));
    for(i=0;i<count;i++)
    names[i]=(char *)malloc(len*sizeof(char));
    
    char *result=(char *)malloc(len*sizeof(char));
    
    names[0]="New profile";
    
    for(i=1;i<count;i++)
    fscanf(profile,"%s",names[i]);
    
    fclose(profile);
    
    char button;
    int current=0;
    
    while(1)
    {
        //system("cls");
        system("clear");
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
            case(ENTER): 
                if(current==0)
                {
                    for(i=1; i<count; i++)
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
                    //system("cls");
                    system("clear");
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
    char name1 [32];
    int i;
    while(1)
    {
        //system("cls");
        system("clear");
        printf("Enter your profile name: ");
        fgets(name,len-15,stdin);
        for(i=0;i<len;i++)
        {
            if(name[i]=='\0')
            name[i-1]='\0';
        }
        
        strcat(name,format);
        if(check_profile(name))
        {
            char password[len];
            //system("cls");
            system("clear");
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
            fprintf(new_profile,"-1 ");
            fprintf(new_profile,"\n");
            
            fprintf(new_profile,"current_armor -1\n");
            fprintf(new_profile,"current_weapon -1\n");
            
            fprintf(new_profile,"experience 0\n");
            fprintf(new_profile,"gold 0\n");
            fprintf(new_profile,"hp %d\n",hp);
            
            
            
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
    while (!feof(config))
    {
        fscanf(config,"%s", currentValueName);
        if(strcmp(currentValueName,"inventory")==0)
        {
            fscanf(config,"%d", size);
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

void set_intValue(char *profileName, char *valueName, int value)
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

void set_inventory(char *profileName, int *inventory)
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

int epmty_slot(int *inventory, int size)
{
    for(int i=0; i<size; i++)
    {
        if(inventory[i]==-1)
        return i;
    }
    return -1;
}

