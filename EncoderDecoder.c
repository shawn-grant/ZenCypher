/*
  Programmer    : Shawn Grant
  Date		    : 28,1, 2019
  Purpose	    : All functions in the encode and decode process
  Filename	    : EncoderDecoder.c
*/

#include <string.h>
#include <ctype.h>
#include <conio.h>
#include <stdlib.h>
#include <stdio.h>
#include <windows.h>
#include <time.h>
#include "CYPHER.H"

#define SPACE_SPECIFIER "700"
#define NUMBER_SPECIFIER "800"
#define SYMBOL_SPECIFIER "900"

#define UPPER 9
#define LOWER 2

/// WORKING
void Encode (TextCypher cypher)
{
    char inputStr[700], newTxt[700] = "", amPm[3], asciiValTxt[4];
    int i, asciiVal;
    time_t t = time(NULL);
    struct tm tm = *localtime(&t);
    int publicKey, privateKey; /// equivalent to public and private key in cryptography

    publicKey = (rand() % (UPPER - LOWER + 1)) + LOWER; // single digit
    privateKey = (publicKey * 5) - publicKey;// key used to encrypt
    /// Add the public key to the text
    newTxt[0] = publicKey + '0';

    system("cls");
    SetConsoleTitleA("ENCODER | Zen Cypher");
    fflush(stdin);

    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), BLUE);

    PrintAtCenterB("  ____            _\n", 21);
    PrintAtCenterB(" /    \\__________| |\n", 21);
    PrintAtCenterB("|  @   ____________| \n", 21);
    PrintAtCenterB(" \\____/            \n\n", 21);

    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), WHITE);

    /// //////////// GET USER DATA ///////////////

    PrintAtCenterA("ENTER TEXT (ENGLISH):\n");
    CreateLargeTextBox("%s", inputStr);

    strcpy(cypher.original, inputStr);

    /// ////////// encoding process ///////////////
    for (i = 0; i < strlen(inputStr); i++)
    {
        if(isdigit(inputStr[i]) == 1)//if the character is a number
        {
            //add the number specifier before the num
            strcat(newTxt, NUMBER_SPECIFIER);
            strAppend(newTxt, inputStr[i]);
        }
        else if(isspace(inputStr[i]) != 0)//if the character is a space
        {
            //add the space specifier before
            strcat(newTxt, SPACE_SPECIFIER);
        }
        else if(isSymbol(inputStr[i]) != 0)//if the character is a symbol
        {
            //add the symbol specifier before
            strcat(newTxt, SYMBOL_SPECIFIER);
            strAppend(newTxt, inputStr[i]);
        }
        else//not a number, space or symbol
        {
            asciiVal = inputStr[i]; ///effectively converts the char to its ascii value
            asciiVal += privateKey; /// increment by key

            itoa(asciiVal, asciiValTxt, 10);//convert the ascii number to string

            if(asciiVal < 100)//add 0 before to ensure groups of 3s
                strInsert(asciiValTxt, "0", 0);

            strcat(newTxt, asciiValTxt);
        }
    }

    strcpy (cypher.encoded, newTxt);//save encoded text to the structure

    /// Add time/date to the cypher
    tm.tm_hour >= 12? strcpy(amPm, "PM"):strcpy(amPm, "AM");

    if(tm.tm_hour > 12) tm.tm_hour -= 12;

    sprintf(cypher.dateTime, "%i/%i/%i @ %i:%i %s",
            tm.tm_mday, tm.tm_mon + 1, tm.tm_year + 1900, tm.tm_hour, tm.tm_min, amPm);

    PrintAtCenterA("--------ENCODED TEXT--------\n");
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), GREEN);
    PrintAtCenterA(cypher.encoded);
    printf("\n\n");

    //SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), YELLOW);
    //PrintAtCenterA("** You may copy the text above **\n\n");

    SaveToFile(cypher);
    AddToHistory(cypher);
}

/// WORKING
void Decode(TextCypher cypher)
{
    char inputStr[700], newTxt[700] = "", amPm[3], asciiValTxt[4] = "", opt, fName[25];
    int i, asciiVal, pass;
    time_t t = time(NULL);
    struct tm tm = *localtime(&t);
    int publicKey, privateKey; //equivalent to public and private key in cryptography
    FILE *fp;

    system("cls");
    SetConsoleTitleA("DECODER | Zen Cypher");
    fflush(stdin);

    PrintAtCenterA("----CHOOSE AN OPTION----\n");
    PrintAtCenterA("----------------------------\n");
    PrintAtCenterA("-[A] DECODE A .ZEN FILE -\n");
    PrintAtCenterA("-[B] DECODE COPIED TEXT -\n");

    opt = getch();

    system("cls");
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), BLUE);

    PrintAtCenterB("  ____            _\n", 21);
    PrintAtCenterB(" /    \\__________| |\n", 21);
    PrintAtCenterB("|  @   ____________| \n", 21);
    PrintAtCenterB(" \\____/            \n\n", 21);

    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), WHITE);

    switch(opt)
    {
        /// From file
        case 'A':
        case 'a':
            /// // GET USER DATA /////
            PrintAtCenterA("ENTER FILE NAME : \n");
            CreateTextBox("%s", fName, 0);

            while(strEndsWith(fName, ".zen") != 1)
            {
                PrintAtCenterA("*Must be a .zen file \n");
                PrintAtCenterA("ENTER VALID FILE NAME : \n");
                CreateTextBox("%s", fName, 0);
            }

            if((fp = fopen(fName, "r")) != NULL)
            {
                fscanf(fp, "%s", inputStr);
                fclose(fp);
                pass = 1;
            }
            else
            {
                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), RED);
                PrintAtCenterA("CANT OPEN FILE, IT MAY NOT EXIST \n");
                pass = 0;
            }
            break;

            /// From text
        case 'B':
        case 'b':
            /// // GET USER DATA /////
            PrintAtCenterA("ENTER THE CYPHER TEXT : \n");
            CreateLargeTextBox("%s", inputStr);
            pass = 1;
            break;

        default:
            PrintAtCenterA("INVALID CHOICE, TRY AGAIN!");
            pass = 0;
            break;
    }

    /// decode
    if(pass == 1)
    {
        strcpy(cypher.encoded, inputStr);

        publicKey = inputStr[0] - '0';
        privateKey = (publicKey * 5) - publicKey; // key used to decrypt

        for (i = 1; i < strlen(inputStr); i++)
        {

            /// get 3 digit ascii code
            strAppend (asciiValTxt, inputStr[i]);
            strAppend (asciiValTxt, inputStr[i + 1]);
            strAppend (asciiValTxt, inputStr[i + 2]);

            if (strcmp(asciiValTxt, NUMBER_SPECIFIER) == 0)
            {
                strAppend (newTxt, inputStr[i + strlen(NUMBER_SPECIFIER)]);
                i += strlen (NUMBER_SPECIFIER);
            }
            else
            {
                if (strcmp(asciiValTxt, SPACE_SPECIFIER) == 0)
                {
                    strAppend(newTxt, ' ');
                    i += strlen(SPACE_SPECIFIER)-1;
                }
                else
                {
                    if (strcmp(asciiValTxt, SYMBOL_SPECIFIER) == 0)
                    {
                        strAppend(newTxt, inputStr[i + strlen(SYMBOL_SPECIFIER)]);
                        i += strlen(SYMBOL_SPECIFIER);
                    }
                    else
                    {
                        asciiVal = atoi(asciiValTxt);
                        asciiVal -= privateKey;

                        strAppend(newTxt, asciiVal);
                        i += 2;/// skip to next ascii set
                    }
                }
            }

            memset(asciiValTxt, 0, sizeof(asciiValTxt)); //clear the text for next entry
        }

        strcpy (cypher.original, newTxt);//save encoded text to the structure

        /// Add time/date to the cypher
        tm.tm_hour >= 12? strcpy(amPm, "PM") : strcpy(amPm, "AM");

        if(tm.tm_hour > 12) tm.tm_hour -= 12;

        sprintf(cypher.dateTime, "%i/%i/%i @ %i:%i %s",
                tm.tm_mday, tm.tm_mon + 1, tm.tm_year + 1900, tm.tm_hour, tm.tm_min, amPm);

        PrintAtCenterA("--------DECODED TEXT--------\n");
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), GREEN);
        PrintAtCenterA(cypher.original);

        AddToHistory(cypher);
    }

    getch();
}

void SaveToFile(TextCypher cypher)
{
    char fName[25];
    FILE *fp;

    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), WHITE);

    SetConsoleTitleA("SAVE TO FILE | Zen Cypher");

    fflush(stdin);
    PrintAtCenterA("ENTER A FILENAME: \n");
    CreateTextBox("%s", fName, 0);

    while(strcmp(fName, "") == 0)
    {
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), YELLOW);
        PrintAtCenterA("**ENTER A VALID FILENAME: \n");
        CreateTextBox("%s", fName, 0);
    }

    strcat(fName, ".zen");///add extension

    if((fp = fopen(fName, "w+")) != NULL)
    {
        fprintf(fp, "%s", cypher.encoded);
        PrintAtCenterA("Saved As \n");
        PrintAtCenterA(fName);
        fclose(fp);
        getch();
    }
    else
    {
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), RED);
        PrintAtCenterA("=( File cannot be saved at this moment...\n");
        getch();
    }

}
