#include <stdio.h>
#include <termios.h>
#include <unistd.h>
#include <stdlib.h>

#include <mysql.h>


#define ESC 27
#define W 119
#define A 97
#define S 115
#define D 100
#define SPACE 32
#define ENTER 10
#define TAB 9


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


#include "main_menu.c"


int main()
{
    MYSQL  *mysql=NULL;
    mysql = mysql_init(mysql);
    mysql_options(mysql,MYSQL_READ_DEFAULT_GROUP,"your_prog_name");
    if (!mysql_real_connect(mysql,"localhost","Nocasis","HeHe1234","profiles",3306,NULL,0))
    {
        fprintf(stderr, "Failed to connect to database: Error: %s\n",
        mysql_error(mysql));
    }
    else
        puts("Connect OK\n");


    char *profile_name=(char *)malloc(32*sizeof(char));
    profile_name=profile_menu(mysql);
    menu(mysql,profile_name);


    mysql_close(mysql);
    return 0;


}
