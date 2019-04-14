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
    int i = 0;

    system("cls");
    SetConsoleTitleA("HISTORY | Zen Cypher");

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
        int length = i-1;
        printf("%d ITEM(s)\n", length);

        for (i = 0; i <= length; i++)
        {
            printf(" _______________________________________\n");
            printf("|\tDATE: %-26s|\n", list[i].dateTime);
            printf("|\tORIGINAL TEXT : %-16s|\n", list[i].original);
            printf("|\tENCODED TEXT  : %-16s|\n", list[i].encoded);
            printf("|\tRECIPIENT     : %-16s|\n", list[i].reciever);
            printf("|_______________________________________|\n\n");
        }

        getch();
    }
    else
    {
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), RED);
        PrintAtCenterA("NO HISTORY FOUND... Hiding something?\n");
        PrintAtCenterA("Press any key to continue\n");
        getch();
    }
}
