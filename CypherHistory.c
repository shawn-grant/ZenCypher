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
        fwrite(&newCypher, sizeof(TextCypher), 1, fp);
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
    TextCypher list[100];
    FILE *fp;
    char opt;
    int i = 0, length;

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

    PrintAtCenterA("_________HISTORY________\n\n");

    if((fp = fopen("HISTORY.CYPH", "r")) != NULL)
    {
        fseek(fp, 0, SEEK_SET);

        while(!feof(fp))
        {
            fread(&list[i], sizeof(TextCypher), 1, fp);
            i++;
        }

        fclose(fp);

        /// //////// DISPLAY /////////
        length = i;
        printf("%d ITEM(s)\n", length);

        for (i = 0; i < length; i++)
        {
            PrintAtCenterA("_______________________________________\n");
            PrintAtCenterA("|-----------------DATE----------------|\n");
            PrintAtCenterA(list[i].dateTime);
            PrintAtCenterA("|-------------ORIGINAL TEXT-----------|\n");
            PrintAtCenterA(list[i].original);
            PrintAtCenterA("|-------------ENCODED TEXT------------|\n");
            PrintAtCenterA(list[i].encoded);
            PrintAtCenterA("|_____________________________________|\n");

            printf("\n");
        }

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
