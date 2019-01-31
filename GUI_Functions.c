/*
  Programmer    : Shawn Grant
  Date		    : 28,1, 2019
  Purpose	    : To mimic GUI elements with text using windows.h
  Filename	    : GUI_Functions.c
*/

#include <stdio.h>
#include <stdlib.h>
#include <windows.h>

///custom function to create a textbox for input (inspired by scanf)
void CreateTextBox(char specifier[], void *var)
{
    COORD coord;//where to put the cursor
    CONSOLE_SCREEN_BUFFER_INFO cursor;//the cursor

    GetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursor);

    printf(" ________________________\n");
    printf("|                        |\n");
    printf("|________________________|\n");

    coord.X = cursor.dwCursorPosition.X + 1;
    coord.Y = cursor.dwCursorPosition.Y + 2;

    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);

    if(strcmp(specifier, "%s") == 0)
    {
        scanf(specifier, var);
    }else
    {
        gets(var);
    }

    coord.Y += 2;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

///custom function to create a textbox for input (inspired by scanf)
void CreateLargeTextBox(char specifier[], void *var)
{
    COORD coord;//where to put the cursor
    CONSOLE_SCREEN_BUFFER_INFO cursor;//the cursor

    GetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursor);

    printf(" ___________________________________________________________\n");
    printf("|                                                           |\n");
    printf("|___________________________________________________________|\n");

    coord.X = cursor.dwCursorPosition.X + 1;
    coord.Y = cursor.dwCursorPosition.Y + 2;

    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
    if(strcmp(specifier, "%s") == 0)
    {
        scanf(specifier, var);
    }else
    {
        gets(var);
    }

    coord.Y += 2;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

///custom function to create a button
void CreateButton(char label[])
{
    COORD coord;//where to put the cursor
    CONSOLE_SCREEN_BUFFER_INFO cursor;//the cursor

    GetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursor);

    printf(" ________________________\n");
    printf("|    %15s|\n", label);
    printf("|________________________|\n");

    coord.X = cursor.dwCursorPosition.X + 1;
    coord.Y = cursor.dwCursorPosition.Y + 2;

    coord.Y += 2;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

