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

char Menu()
{
    int i, opt;
    char ch;
    COORD pos, prev;

    system("cls");

    SetConsoleTitleA("Main Menu | ZEN CYPHER");
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), WHITE);

    pos.X = 21;
    pos.Y = 6;

    printf(" ___   __  __       \n");
    printf("| | | |   |  | |  | \n");
    printf("|   | |-- |  | |  | \n");
    printf("|   | |__ |  | |__| \n\n");
    printf("________________________\n");

    printf ("A) ENCODE A MESSAGE\n");
    printf ("B) DECODE A MESSAGE\n");
    printf ("C) NEW FROM FILE\n");
    printf ("D) SHOW HISTORY\n");
    printf ("E) UPDATE LOGIN INFO\n");
    printf ("F) EXIT\n\n");

    printf("Use the arrows to navigate to an option");

    while((ch = getch()) != '\r')
    {
        SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);

        if(ch == 72)/// up
        {
           if(pos.Y >= 7)
            {
                pos.Y--;
                ///  clear the arrow below
                prev.X = pos.X;
                prev.Y = pos.Y + 1;
                SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), prev);
                printf("        ");
           }

           SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
           SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), YELLOW);
           printf("<-------");
       }
       else
       {
           if(ch == 80)/// down
           {
               if(pos.Y < 11)
               {
                   pos.Y++;
                   ///  clear the arrow below
                   prev.X = pos.X;
                   prev.Y = pos.Y - 1;
                   SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), prev);
                   printf("        ");
               }

               SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
               SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), YELLOW);
               printf("<-------");
           }
       }

       SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), WHITE);
    }

    return 'y';
}

///custom function to create a textbox for input; includes password hiding (inspired by scanf)
void CreateTextBox(char specifier[], void *var, int isProtected)
{
    COORD coord;//where to put the cursor
    CONSOLE_SCREEN_BUFFER_INFO cursor;//the cursor
    char c, password[25];
    int i = 0;

    printf("\n");
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), CYAN);

    PrintAtCenterA ("|                        \n");
    PrintAtCenterA ("|________________________ ");
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), WHITE);

    GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursor);

    ///positioning the cursor inside the box
    coord.X = cursor.dwCursorPosition.X - 25;
    coord.Y = cursor.dwCursorPosition.Y - 1;

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
                    ///check to ensure its a letter or number and not an arrow
                    ///because getch seems to accept EVERYTHING on the keyboard as a char
                    if((isalpha(c) != 0 || isdigit(c) == 1) && (c != 72 && c != 80 && c != 75 && c != 77))
                    {
                        password[i] = c;
                        printf("-");
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
    printf("\n");
}

///custom function to create a textbox for input (inspired by scanf)
void CreateLargeTextBox(char specifier[], void *var)
{
    COORD coord;//where to put the cursor
    CONSOLE_SCREEN_BUFFER_INFO cursor;//the cursor

    printf("\n");
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), CYAN);

    PrintAtCenterA("|                                                           \n");
    PrintAtCenterA("|___________________________________________________________ ");
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), WHITE);

    GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursor);
    ///positioning the cursor inside the box
    coord.X = cursor.dwCursorPosition.X - 56;
    coord.Y = cursor.dwCursorPosition.Y - 1;

    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);

    ///reading the variable
    if(strcmp(specifier, "%s") != 0)
    {
        scanf(specifier, var);
    }
    else
    {
        gets(var);
    }

    ///re-place the cursor outside the box
    coord.Y += 2;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);

    printf("\n");
}

void ShowLoading()
{
    int i;
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
    CONSOLE_SCREEN_BUFFER_INFO csbi;

    PrintAtCenterA("#####################\n");
    PrintAtCenterA("#                   #\n");
    PrintAtCenterA("#   ###### ######   #\n");
    PrintAtCenterA("#       ## ##       #\n");
    PrintAtCenterA("#      ##  ##       #\n");
    PrintAtCenterA("#     ##   ##       #\n");
    PrintAtCenterA("#    ##    ##       #\n");
    PrintAtCenterA("#   ###### ######   #\n");
    PrintAtCenterA("#                   #\n");
    PrintAtCenterA("#####################");

    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), YELLOW);

    GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);

    coord.X = csbi.dwCursorPosition.X;
    coord.Y = 1;

    for(i = 0; i < 9; i++)
    {
        SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
        printf("###\n");
        coord.Y += 1;
    }

    PrintAtCenterA("    #######################\n");
    PrintAtCenterA("    #######################\n");
    PrintAtCenterA("ZENCYPHER 1.0\n");

    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), WHITE);

    Sleep(2000);
}

void GoodBye()
{
    system("cls");
    PrintAtCenterA ("   @@@@@@@@@@     \n");
    PrintAtCenterA ("   @@@    @@@     \n");
    PrintAtCenterA ("   @@@    @@@     \n");
    PrintAtCenterA ("   @@@    @@@     \n");
    PrintAtCenterA ("@@@@@@@@@@@@@@@@  \n");
    PrintAtCenterA ("@@@@@@@@@@@@@@@@  \n");
    PrintAtCenterA ("@@@@@@  O  @@@@@  \n");
    PrintAtCenterA ("@@@@@@@@ @@@@@@@  \n");
    PrintAtCenterA ("@@@@@@@@ @@@@@@@  \n");
    PrintAtCenterA ("@@@@@@@@ @@@@@@@  \n");
    PrintAtCenterA ("@@@@@@@@@@@@@@@@  \n");

    Sleep(1000);
    exit(0);
}

void PrintAtCenterA(char str[])
{
    COORD centerPos;
    int screenWwidth;
    CONSOLE_SCREEN_BUFFER_INFO csbi;

    GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
    screenWwidth = csbi.srWindow.Right - csbi.srWindow.Left + 1;

    /// cursor to center
    centerPos.X = (screenWwidth - strlen(str)) / 2;
    centerPos.Y = csbi.dwCursorPosition.Y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), centerPos);
    /// print
    printf(str);
}

//print at the center with specified length of the string
void PrintAtCenterB(char str[], int length)
{
    COORD centerPos;
    int screenWwidth;
    CONSOLE_SCREEN_BUFFER_INFO csbi;

    GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
    screenWwidth = csbi.srWindow.Right - csbi.srWindow.Left + 1;

    /// cursor to center
    centerPos.X = (screenWwidth - length) / 2;
    centerPos.Y = csbi.dwCursorPosition.Y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), centerPos);
    /// print
    printf(str);
}
