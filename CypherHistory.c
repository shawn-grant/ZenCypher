/*
  Programmer    : Shawn Grant
  Date		    : 28,1, 2019
  Purpose	    : To Keep track of every encoding and decoding
  Filename	    : CypherHistory.c
*/

#include <stdio.h>
#include <conio.h>
#include <windows.h>
#include "CYPHER.H"

void AddToHistory(TextCypher newCypher)
{
    FILE *fp;

    if((fp = fopen("HISTORY.CYPH", "a+")) != NULL)
    {
        fprintf(fp, "%s\n%s\n%s\n", newCypher.dateTime, newCypher.original, newCypher.encoded);
        fclose(fp);
    }
    else
    {
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), RED);
        PrintAtCenterA("AN ERROR OCCURED...Press any key to continue\n");
        getch();
    }
}

void ShowHistory()
{
    TextCypher tmp;
    FILE *fp;
    char opt;
    int i = 1;

    system("cls");
    SetConsoleTitleA("HISTORY | Zen Cypher");

    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), BLUE);
    PrintAtCenterB("  _____   \n", 10);
    PrintAtCenterB(" /|    |_ \n", 10);
    PrintAtCenterB("|.CYPH | |\n", 10);
    PrintAtCenterB("|     _| |\n", 10);
    PrintAtCenterB("|____|/  |\n", 10);
    PrintAtCenterB("   |_____|\n\n", 10);
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), WHITE);

    PrintAtCenterA("_____________HISTORY____________\n\n");

    if((fp = fopen("HISTORY.CYPH", "r")) != NULL)
    {
        fseek(fp, 0, SEEK_SET);

        while(!feof(fp))
        {
            //fscanf(fp, "%s %s %s", tmp.dateTime, tmp.original, tmp.encoded);
            fgets(tmp.dateTime, 25, fp);
            fgets(tmp.original, 500, fp);
            fgets(tmp.encoded, 700, fp);

            if(feof(fp))
                break;

            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), YELLOW);
            printf("\tITEM %i", i);

            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), CYAN);
            PrintAtCenterA(" _____________________________________ \n");
            PrintAtCenterA("|________________ DATE _______________|\n");
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), WHITE);
            PrintAtCenterA(tmp.dateTime);
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), CYAN);
            PrintAtCenterA("|____________ ORIGINAL TEXT __________|\n");
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), WHITE);
            PrintAtCenterA(tmp.original);
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), CYAN);
            PrintAtCenterA("|____________ ENCODED TEXT ___________|\n");
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), WHITE);
            PrintAtCenterA(tmp.encoded);
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), CYAN);
            PrintAtCenterA("|_____________________________________|\n");
            printf("\n");

            i++;
        }

        fclose(fp);

        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), WHITE);
        PrintAtCenterA("DO YOU WISH TO CLEAR YOUR HISTORY? [Y/N]: ");
        scanf("%c", &opt);

        if(opt == 'Y' || opt == 'y')
            Clear();
    }
    else
    {
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), RED);
        PrintAtCenterA("NO HISTORY FOUND... Hiding something?\n");
        PrintAtCenterA("Press any key to continue\n");
        getch();
    }
}

void Clear()
{
    system("cls");

    if (remove("HISTORY.CYPH") == 0)
        PrintAtCenterA("History cleared successfully");
    else
        PrintAtCenterA("Unable to clear the history, it may already be clear");

    getch();
}
