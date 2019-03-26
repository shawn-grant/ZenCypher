/*
  Programmer    : Shawn Grant
  Date		    : 28,1, 2019
  Purpose	    : To mimic GUI elements with text using windows.h
  Filename	    : GUI_Functions.c
*/

#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <windows.h>
#include "CYPHER.H"

///custom function to create a textbox for input; includes password hiding (inspired by scanf)
void CreateTextBox(char specifier[], void *var, int isProtected)
{
    COORD coord;//where to put the cursor
    CONSOLE_SCREEN_BUFFER_INFO cursor;//the cursor
    char c, password[25];
    int i = 0;

    GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursor);

    printf(" ________________________\n");
    printf("|                        |\n");
    printf("|________________________|\n");

    ///positioning the cursor inside the box
    coord.X = cursor.dwCursorPosition.X + 1;
    coord.Y = cursor.dwCursorPosition.Y + 1;

    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);

    ///reading the variable
    if(strcmp(specifier, "%s") != 0)//not a string
    {
        scanf(specifier, var);
    }
    else//is a string
    {
        if(isProtected == 1)///if isProtected = 1, use password protection
        {
            //print asterisks for chars
            while((c = getch()) != '\r')//return or enter key
            {
                if(c == '\b')//backspace pressed
                {
                    ///manually remove perform backspace action
                    if(strlen(password) > 0)
                    {
                        password[strlen(password)-1] = '\0';//remove last character
                        printf("\b \b");//visual backspace
                        i--;
                    }
                }
                else
                {
                    ///check to ensure its a letter or number
                    ///because getch seems to accept EVERYTHING on the keyboard as a char
                    if(isalpha(c) != 0 || isdigit(c) == 1)
                    {
                        password[i] = c;
                        printf("*");
                        i++;
                    }
                }
            }

            password[i] = '\0';//end the string
            strcpy(var, password);
        }
        else//regular string
        {
            gets(var);
        }
    }

    ///re-place the cursor outside the box
    coord.Y += 2;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

///custom function to create a textbox for input (inspired by scanf)
void CreateLargeTextBox(char specifier[], void *var)
{
    COORD coord;//where to put the cursor
    CONSOLE_SCREEN_BUFFER_INFO cursor;//the cursor

    GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursor);

    printf(" ___________________________________________________________\n");
    printf("|                                                           |\n");
    printf("|___________________________________________________________|\n");

    ///positioning the cursor inside the box
    coord.X = cursor.dwCursorPosition.X + 1;
    coord.Y = cursor.dwCursorPosition.Y + 1;

    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);

    ///reading the variable
    if(strcmp(specifier, "%s") != 0)
    {
        scanf(specifier, var);
    }else
    {
        gets(var);
    }

    ///re-place the cursor outside the box
    coord.Y += 2;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

void ShowLoading()
{
    int i, j = 0;
    char space[10] = "";

    for (i = 0; i < 13; i++)
    {
        system("cls");

        printf("     ENCODING ....\n");

        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 2);

        printf("\t _____________\n");
        printf("\t|%-13s|\n", space);
        printf("\t|_____________|\n");

        strcat(space, "@");
        Sleep(50);
    }

    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), WHITE);
}

void SplashScreen()
{
    int i;
    COORD coord;//where to put the cursor
    CONSOLE_SCREEN_BUFFER_INFO cursor;//the cursor


    printf("\t#####################\n");
    printf("\t#                   #\n");
    printf("\t#   ###### ######   #\n");
    printf("\t#       ## ##       #\n");
    printf("\t#      ##  ##       #\n");
    printf("\t#     ##   ##       #\n");
    printf("\t#    ##    ##       #      ZENCYPHER\n");
    printf("\t#   ###### ######   #         1.0\n");
    printf("\t#                   #\n");
    printf("\t#####################\n");

    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), YELLOW);

    coord.X = 29;
    coord.Y = 1;

    for(i = 0; i < 9; i++)
    {
        SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
        printf("###\n");
        coord.Y += 1;
    }

    printf("\t #######################\n");
    printf("\t #######################\n");

    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), WHITE);

    Sleep(2000);
}

void GoodBye()
{
    system("cls");
    printf("\t     @@@@@@@@@@     \n");
    printf("\t     @@@    @@@     \n");
    printf("\t     @@@    @@@     \n");
    printf("\t     @@@    @@@     \n");
    printf("\t  @@@@@@@@@@@@@@@@  \n");
    printf("\t  @@@@@@@@@@@@@@@@  \n");
    printf("\t  @@@@@@  O  @@@@@  \n");
    printf("\t  @@@@@@@@ @@@@@@@  \n");
    printf("\t  @@@@@@@@ @@@@@@@  \n");
    printf("\t  @@@@@@@@ @@@@@@@  \n");
    printf("\t  @@@@@@@@@@@@@@@@  \n");
}

