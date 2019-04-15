/*
  Programmer    : Shawn Grant
  Created       : 28,1, 2019
  Purpose	    : Driver and helping functions
  Filename	    : main.c
*/

#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <time.h>
#include <string.h>
#include <conio.h>
#include "CYPHER.H"

void UpdateLogin();
int LoginSignUp(User *);
char MainMenu();

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
                ShowHistory();
                break;

            case 'D':
            case 'd':
                UpdateLogin();
                break;

            default:
                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), RED);
                printf("\n");
                PrintAtCenterA("INVALID OPTION!\n");
                PrintAtCenterA("  Press any key to continue...  ");
                getch();
                break;
            }

            choice = MainMenu();
        }
    }

    GoodBye();///leave the program
    return 0;
}

int LoginSignUp(User *user)
{
    SetConsoleTitleA("LOGIN / SIGN-UP");

    system("cls");
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), BLUE);

    PrintAtCenterB("      ___      \n", 15);
    PrintAtCenterB("     /   \\     \n", 15);
    PrintAtCenterB("    |     |    \n", 15);
    PrintAtCenterB("    |     |    \n", 15);
    PrintAtCenterB("     \\   /     \n", 15);
    PrintAtCenterB("  ___|   |___  \n", 15);
    PrintAtCenterB(" /           \\ \n", 15);
    PrintAtCenterB("|_____________|\n\n", 15);

    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), WHITE);

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
                PrintAtCenterA("LOGIN \n\n");
                PrintAtCenterA("ENTER YOUR USERNAME: \n");
                CreateTextBox("%s", user->username, 0);
                PrintAtCenterA("ENTER YOUR PASSWORD: \n");
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
                PrintAtCenterA("SIGN UP \n\n");
                PrintAtCenterA("ENTER A USERNAME: \n");
                CreateTextBox("%s", user->username, 0);
                PrintAtCenterA("ENTER A PASSWORD: \n");
                CreateTextBox("%s", user->password, 1);
                system("cls");
            }
            while(strcmp(user->username, "") == 0 || strcmp(user->password, "") == 0);

            ///write the new user to file
            if((fpWrite = fopen("userData.dat", "w")) != NULL)
            {
                fprintf(fpWrite, "%s %s", user->username, user->password);
                fclose(fpWrite);

                //ShowTitle();
                return 1;//user logged in
            }
            else
            {
                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), RED);
                PrintAtCenterA("\nCANNOT SAVE USER DATA... RESTART THE PROGRAM");
                getch();
                return 0;//user not logged in
            }
        }
        fclose(fpRead);
    }
    else
    {
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), RED);
        PrintAtCenterA("\nCANNOT LOAD USER DATA... RESTART THE PROGRAM");
        getch();
        return 0;//user not logged in
    }
}

void UpdateLogin()
{
    char uname[25], pwd[25];
    FILE *fp;

    system("cls");

    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), BLUE);

    PrintAtCenterB("      ___      \n", 15);
    PrintAtCenterB("     /   \\     \n", 15);
    PrintAtCenterB("    |     |    \n", 15);
    PrintAtCenterB("    |     |    \n", 15);
    PrintAtCenterB("     \\   /     \n", 15);
    PrintAtCenterB("  ___|   |___  \n", 15);
    PrintAtCenterB(" /           \\ \n", 15);
    PrintAtCenterB("|_____________|\n\n", 15);

    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), WHITE);

    do
    {
        PrintAtCenterA("CHANGE USERNAME AND PASSWORD\n");

        PrintAtCenterA("ENTER NEW USERNAME: \n");
        CreateTextBox("%s", uname, 0);

        PrintAtCenterA("ENTER NEW PASSWORD: \n");
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
        PrintAtCenterA("\n CANNOT UPDATE AT THIS TIME...");
        getch();
    }
}

char MainMenu()
{
    system("cls");

    SetConsoleTitleA("Main Menu | ZEN CYPHER");
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), WHITE);

    PrintAtCenterA("________________________\n");
    PrintAtCenterB("  ___   __  __       \n", 21);
    PrintAtCenterB(" | | | |   |  | |  | \n", 21);
    PrintAtCenterB(" |   | |-- |  | |  | \n", 21);
    PrintAtCenterB(" |   | |__ |  | |__| \n\n", 21);

    PrintAtCenterA("________________________\n");

    PrintAtCenterB ("-[A] ENCODE A MESSAGE -\n", 26);
    PrintAtCenterB ("-[B] DECODE A MESSAGE -\n", 26);
    PrintAtCenterB ("-[C] SHOW HISTORY     -\n", 26);
    PrintAtCenterB ("-[D] UPDATE USER INFO -\n", 26);
    PrintAtCenterB ("-[E] EXIT             -\n\n", 26);

    PrintAtCenterA("CHOOSE A LETTER OPTION ABOVE: ");

    return getch();
}
