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
    COORD pos1, pos2;//where to put the cursor
    CONSOLE_SCREEN_BUFFER_INFO cursor;//the cursor

    GetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursor);
    pos1.X = cursor.dwCursorPosition.X;
    pos1.Y = cursor.dwCursorPosition.Y;

    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_GREEN);
    printf(" _________________\n");
    printf("|   %-12s  |\n", label);
    printf("|_________________|\n");
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);

    GetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursor);
    pos2.X = cursor.dwCursorPosition.X;
    pos2.Y = cursor.dwCursorPosition.Y;

    cursor.dwCursorPosition.Y += 2;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), cursor.dwCursorPosition);

    ClickCheck(pos1, pos2);
}

//listen for click events by buttons
void ClickCheck (COORD pos1, COORD pos2) //void (*f)())
{
    CONSOLE_SCREEN_BUFFER_INFO cursor;//the cursor

    while(1)
    {
        GetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursor);

        if(cursor.dwCursorPosition.X > pos1.X && cursor.dwCursorPosition.X < pos2.X)
        {
            if(cursor.dwCursorPosition.Y > pos1.Y && cursor.dwCursorPosition.Y < pos2.Y)
            {
                ///click registered
                printf("\nSomething was clicked\n");
                //(*f)();
            }
        }
    }
}
