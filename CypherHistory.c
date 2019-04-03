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
        printf("AN ERROR OCCURED...\nPress any key to continue");
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

    printf("_________HISTORY_______\n\n");

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

        if(length > 0)
        {
            for (i = 0; i <= length; i++)
            {
                printf(" _______________________________________\n");
                printf("|\tDATE: %-26s|\n", list[i].dateTime);
                printf("|\tORIGINAL TEXT : %-16s|\n", list[i].original);
                printf("|\tENCODED TEXT  : %-16s|\n", list[i].encoded);
                printf("|\tRECIPIENT     : %-16s|\n", list[i].reciever);
                printf("|_______________________________________|\n\n");
            }

            printf("_______OPTIONS_______\n");
            printf("1) DELETE ITEM\n");
            printf("2) CLEAR HISTORY\n");
            getch();
        }
        else
        {
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), RED);
            printf("NO ITEMS\n");
            getch();
        }
    }
    else
    {
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), RED);
        printf("NO HISTORY DATA...\nPress any key to continue");
        getch();
    }
}

void RemoveItem(int item)
{

}

void Clear()
{
    if (remove("HISTORY.CYPH") == 0)
    {
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), YELLOW);
        printf("HISTORY CLEARED");
        getch();
    }
    else
    {
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), RED);
        printf("Unable to delete the file\n");
    }
}
