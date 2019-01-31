/*
  Programmer    : Shawn Grant
  Date		    : 28,1, 2019
  Purpose	    : Main driver module
  Filename	    : main.c
*/

#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <string.h>
#include <conio.h>
#include "CYPHER.H"

void SplashScreen();
void Login(char []);
char MainMenu();
void GoodBye();

int main()
{
    TextCypher userInput;
    char username[30];
    char choice;

    SplashScreen();
    Login(username);

    choice = MainMenu();

    while(choice != 'E' && choice != 'e')
    {
        switch(choice)
        {
        case 'A':
        case 'a':
            Encode(userInput);
            break;

        case 'B':
        case 'b':
            Decode(userInput);
            break;

        case 'C':
        case 'c':
            OpenFromFile();
            break;

        case 'D':
        case 'd':
            ShowHistory();
            break;

        default:
            printf("\nINVALID OPTION!\n");
            printf("Press any key to continue...");
            getch();
            break;
        }

        choice = MainMenu();
        SetConsoleTitleA("ZEN CYPHER");
    }

    GoodBye();

    return 0;
}

void SplashScreen()
{
    int i;
    COORD coord;
    coord.X = 0;
    coord.Y = 0;

    ///Create color wave animation by printing text line by line
    /// incrementing the color and resetting the cursor position(0,0) at the end of the loop
    /// to print over the previous text in the next iteration of the loop
    for (i = 5; i < 10; i++)
    {
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), i);
        printf("\t     @@@@@@@@@@     ##########  ##########  ###########\n");Sleep(60);
        printf("\t     @@@    @@@     ##########  ##########  ###########\n");Sleep(60);
        printf("\t     @@@    @@@           ###               ###     ###\n");Sleep(60);
        printf("\t     @@@    @@@          ###                ###     ###\n");Sleep(60);
        printf("\t     @@@    @@@         ###     ##########  ###     ###\n");Sleep(60);
        printf("\t  @@@@@@@@@@@@@@@@     ###      ##########  ###     ###\n");Sleep(60);
        printf("\t  @@@@@@@@@@@@@@@@    ###                   ###     ###\n");Sleep(60);
        printf("\t  @@@@@@  O  @@@@@   ###                    ###     ###\n");Sleep(60);
        printf("\t  @@@@@@@@ @@@@@@@  #########   ##########  ###     ###\n");Sleep(60);
        printf("\t  @@@@@@@@ @@@@@@@  #########   ##########  ###     ###\n");Sleep(60);
        printf("\t  @@@@@@@@ @@@@@@@               CYPHER\n");Sleep(80);
        printf("\t  @@@@@@@@@@@@@@@@\n");Sleep(80);
        SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
    }

    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15); //reset the text collor to white
    system("cls");
}

void Login(char uName[])
{
    SetConsoleTitleA("LOGIN");

    printf("ENTER USERNAME: \n");
    CreateTextBox("%s", uName);
    fflush(stdin);

    printf("Username: %s", uName);
    getch();
}

char MainMenu()
{
    char c;
    system("cls");

    printf ("A) ENCODE TEXT\n");
    printf ("B) DECODE TEXT\n");
    printf ("C) NEW FROM FILE\n");
    printf ("D) SHOW HISTORY\n");
    printf ("E) EXIT\n\n");

    printf("CHOOSE AN OPTION ABOVE: ");
    c = getch();

    return c;
}

void GoodBye()
{
    system("cls");
}
