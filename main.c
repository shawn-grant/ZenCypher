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
void LoginSignUp(User);
char MainMenu();
void GoodBye();

int main()
{
    TextCypher userInput;
    User user;
    char choice;

    SplashScreen();
    LoginSignUp(user);

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

void LoginSignUp(User user)
{
    SetConsoleTitleA("LOGIN");

    char nameOnFile[25], passwordOnFile[25];
    FILE *fp;

    if((fp = fopen("userData.dat", "w+")) != NULL)
    {
        fscanf(fp, "%s", nameOnFile);
        fscanf(fp, "%s", passwordOnFile);

        //check if to sign up or login
        if(strcmp(nameOnFile, "") !=0)
        {
            //login
            do
            {
                printf("LOGIN \n\n");
                printf("ENTER USERNAME: \n");
                CreateTextBox("%s", user.username, 0);
                printf("ENTER PASSWORD: \n");
                CreateTextBox("%s", user.password, 1);
                system("cls");
            }
            while(strcmp(user.username, "") != 0 && strcmp(user.password, "") != 0);

            //save to file
            //fwrite(,,fp);
        }
        else
        {
            //sign up
            do
            {
                printf("SIGN UP \n\n");
                printf("ENTER USERNAME: \n");
                CreateTextBox("%s", user.username, 0);
                printf("ENTER PASSWORD: \n");
                CreateTextBox("%s", user.password, 1);
                system("cls");
            }
            while(strcmp(user.username, "") != 0 && strcmp(user.password, "") != 0 &&
                   strcmp(user.username, nameOnFile) == 0 && strcmp(user.password, passwordOnFile) == 0);
        }

        fclose(fp);
    }else
    {
        printf("\nCANNOT LOAD USER DATA... RESTART THE PROGRAM");
    }
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
    int i;
    for (i = 0; i > 3; i++)
    {
        printf("\t     @@@@@@@@@@     \n");
        printf("\t     @@@    @@@     \n");
        printf("\t     @@@    @@@     \n");
        printf("\t     @@@    @@@     \n");

        printf("\t     @@@            \n");
        printf("\t     @@@            \n");
        printf("\t     @@@            \n");

        printf("\t  @@@@@@@@@@@@@@@@  \n");
        printf("\t  @@@@@@@@@@@@@@@@  \n");
        printf("\t  @@@@@@  O  @@@@@  \n");
        printf("\t  @@@@@@@@ @@@@@@@  \n");
        printf("\t  @@@@@@@@ @@@@@@@  \n");
        printf("\t  @@@@@@@@ @@@@@@@  \n");
        printf("\t  @@@@@@@@@@@@@@@@  \n");
    }
    Sleep(1000);
}
