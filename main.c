/*
  Programmer    : Shawn Grant
  Created       : 28,1, 2019
  Purpose	    : Driver and helping functions
  Filename	    : main.c
*/

#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <string.h>
#include <conio.h>
#include "CYPHER.H"

void SplashScreen();
int LoginSignUp(User *);
char MainMenu();
void GoodBye();

int main()
{
    TextCypher userInput;
    User user;
    char choice;

    srand(time(0));

    SplashScreen();

    ///If user successfully logged in
    if(LoginSignUp(&user) == 1)
    {
        choice = MainMenu();

        while(choice != 'F' && choice != 'f')
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

            case 'E':
            case 'e':
                UpdateLogin();
                break;

            default:
                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), RED);
                printf("\n  INVALID OPTION!\n");
                printf("     Press any key to continue...");
                getch();
                break;
            }

            choice = MainMenu();
        }
    }

    GoodBye();///leave the program
    return 0;
}

void SplashScreen()
{
    int i;
    COORD coord;
    coord.X = 0;
    coord.Y = 0;

    /// Create color wave animation by printing text line by line
    /// incrementing the color and resetting the cursor position(0,0) at the end of the loop
    /// to print over the previous text in the next iteration of the loop
    for (i = 5; i < 10; i++)
    {
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), i);
        printf("\t     @@@@@@@@@@     ##########  ##########  ###########\n"); Sleep(60);
        printf("\t     @@@    @@@     ##########  ##########  ###########\n"); Sleep(60);
        printf("\t     @@@    @@@           ###               ###     ###\n"); Sleep(60);
        printf("\t     @@@    @@@          ###                ###     ###\n"); Sleep(60);
        printf("\t     @@@    @@@         ###     ##########  ###     ###\n"); Sleep(60);
        printf("\t  @@@@@@@@@@@@@@@@     ###      ##########  ###     ###\n"); Sleep(60);
        printf("\t  @@@@@@@@@@@@@@@@    ###                   ###     ###\n"); Sleep(60);
        printf("\t  @@@@@@  O  @@@@@   ###                    ###     ###\n"); Sleep(60);
        printf("\t  @@@@@@@@ @@@@@@@  #########   ##########  ###     ###\n"); Sleep(60);
        printf("\t  @@@@@@@@ @@@@@@@  #########   ##########  ###     ###\n"); Sleep(60);
        printf("\t  @@@@@@@@ @@@@@@@               CYPHER\n"); Sleep(80);
        printf("\t  @@@@@@@@@@@@@@@@\n"); Sleep(80);
        SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
    }

    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15); //reset the text collor to white
    system("cls");
}

int LoginSignUp(User *user)
{
    SetConsoleTitleA("LOGIN / SIGN-UP");

    char nameOnFile[25], passwordOnFile[25];
    FILE *fpRead, *fpWrite;

    if((fpRead = fopen("userData.dat", "a+")) != NULL)
    {
        fseek(fpRead, 0, SEEK_SET);//goto start of file
        fscanf(fpRead, "%s %s", nameOnFile, passwordOnFile);

        //check if to sign up or login
        if(strcmp(nameOnFile, "") != 0)//not equal, something is on file
        {
            //login
            do
            {
                printf("LOGIN \n\n");
                printf("ENTER YOUR USERNAME: \n");
                CreateTextBox("%s", user->username, 0);
                printf("ENTER YOUR PASSWORD: \n");
                CreateTextBox("%s", user->password, 1);
                system("cls");
            }
            while(strcmp(user->username, nameOnFile) != 0 || strcmp(user->password, passwordOnFile) != 0);

            return 1;
        }
        else
        {
            //sign up
            do
            {
                printf("SIGN UP \n\n");
                printf("ENTER A USERNAME: \n");
                CreateTextBox("%s", user->username, 0);
                printf("ENTER A PASSWORD: \n");
                CreateTextBox("%s", user->password, 1);
                system("cls");
            }
            while(strcmp(user->username, "") == 0 || strcmp(user->password, "") == 0);

            ///write the new user to file
            if((fpWrite = fopen("userData.dat", "w")) != NULL)
            {
                fprintf(fpWrite, "%s %s", user->username, user->password);
                fclose(fpWrite);

                StartTutorial();
                return 1;//user logged in
            }
            else
            {
                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), RED);
                printf("\nCANNOT SAVE USER DATA... RESTART THE PROGRAM");
                getch();
                return 0;//user not logged in
            }
        }
        fclose(fpRead);
    }
    else
    {
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), RED);
        printf("\nCANNOT LOAD USER DATA... RESTART THE PROGRAM");
        getch();
        return 0;//user not logged in
    }
}

void UpdateLogin()
{
    char uname[25], pwd[25];
    FILE *fp;

    system("cls");

    do
    {
        printf("CHANGE USERNAME AND PASSWORD\n");

        printf("ENTER NEW USERNAME: \n");
        CreateTextBox("%s", uname, 0);
        printf("ENTER NEW PASSWORD: \n");
        CreateTextBox("%s", pwd, 1);
        system("cls");
    }
    while(strcmp(uname, "") == 0 || strcmp(pwd, "") == 0);

    if((fp = fopen("userData.dat", "w")) != NULL)
    {
        fprintf(fp, "%s %s", uname, pwd);
        fclose(fp);
    }
    else
    {
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), RED);
        printf("\n CANNOT UPDATE AT THIS TIME...");
        getch();
    }
}

char MainMenu()
{
    system("cls");

    SetConsoleTitleA("Main Menu | ZEN CYPHER");
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), WHITE);

    printf ("A) ENCODE A MESSAGE\n");
    printf ("B) DECODE A MESSAGE\n");
    printf ("C) NEW FROM FILE\n");
    printf ("D) SHOW HISTORY\n");
    printf ("E) UPDATE LOGIN INFO\n");
    printf ("F) EXIT\n\n");

    printf("CHOOSE A LETTER OPTION ABOVE:");

    return getch();
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
