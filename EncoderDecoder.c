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
#include <time.h>
#include "CYPHER.H"

#define SPACE_SPECIFIER "AAA"
#define NUMBER_SPECIFIER "[N]"
#define SYMBOL_SPECIFIER "[@]"

#define INCREMENT 5
#define UPPER 9
#define LOWER 2

/// WORKING
void Encode (TextCypher cypher)
{
    char inputStr[700], newTxt[700] = "", amPm[3], asciiValTxt[4];
    int i, asciiVal;
    time_t t = time(NULL);
    struct tm tm = *localtime(&t);
    int publicKey, privateKey; //equivalent to public and private key in cryptography

    publicKey = (rand() % (UPPER - LOWER + 1)) + LOWER; // single digit
    privateKey = (publicKey * 5) - publicKey;// key used to encrypt

    system("cls");
    fflush(stdin);

    /// Add the public key to the text
    newTxt[0] = publicKey + '0';

    /// //////////// GET USER DATA ////////////////

    printf("ENTER RECIPIENT USERNAME:\n");
    CreateTextBox("%s", cypher.reciever, 0);

    printf("ENTER TEXT (ENGLISH):\n");
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

    ///add recipient name to the coded string here

    printf("\nENCODED TEXT: \n %s", cypher.encoded);

    AddToHistory(cypher);

    getch();
}

/// WORKING
void Decode(TextCypher cypher)
{
    char inputStr[700], newTxt[700] = "", amPm[3], asciiValTxt[4] = "";
    int i, asciiVal;
    time_t t = time(NULL);
    struct tm tm = *localtime(&t);
    int publicKey, privateKey; //equivalent to public and private key in cryptography

    system("cls");

    /// // GET USER DATA /////

    printf("ENTER CODE : \n");
    CreateLargeTextBox("%s", inputStr);
    fflush(stdin);

    strcpy(cypher.encoded, inputStr);

    publicKey = inputStr[0] - '0';
    privateKey = (publicKey * 5) - publicKey; // key used to decrypt

    for (i = 1; i < strlen(inputStr); i++)
    {

        if (strPresentAtIndex (inputStr, NUMBER_SPECIFIER, i) == 1)
        {
            strAppend(newTxt, inputStr[i + strlen(NUMBER_SPECIFIER)]);
            i += strlen(NUMBER_SPECIFIER);
            printf("\nNUMBER: %s\n", newTxt);
        }
        else
        {
            if (strPresentAtIndex (inputStr, SPACE_SPECIFIER, i) == 1)
            {
                strAppend(newTxt, '  ');
                i += strlen(SPACE_SPECIFIER);
                printf("\nSpace: %s\n", newTxt);
            }
            else
            {
                if (strPresentAtIndex (inputStr, SYMBOL_SPECIFIER, i) == 1)
                {
                    strAppend(newTxt, inputStr[i + strlen(SYMBOL_SPECIFIER)]);
                    i += strlen(SYMBOL_SPECIFIER);
                    printf("\nSymbol: %s\n", newTxt);
                }
                else
                {
                    //if(isdigit (inputStr[i]) == 1)
                   //{
                        /// get 3 digit ascii code
                        strAppend (asciiValTxt, inputStr[i]);
                        strAppend (asciiValTxt, inputStr[i + 1]);
                        strAppend (asciiValTxt, inputStr[i + 2]);

                        asciiVal = atoi(asciiValTxt);
                        asciiVal -= privateKey;

                        strAppend(newTxt, asciiVal);
                        memset(asciiValTxt, 0, sizeof(asciiValTxt)); //clear the text for next entry

                        i += 2;/// skip to next ascii set
                    //}
                }
            }
        }
    }

    strcpy (cypher.original, newTxt);//save encoded text to the structure

    /// Add time/date to the cypher
    tm.tm_hour >= 12? strcpy(amPm, "PM"):strcpy(amPm, "AM");

    if(tm.tm_hour > 12) tm.tm_hour -= 12;

    sprintf(cypher.dateTime, "%i/%i/%i @ %i:%i %s",
            tm.tm_mday, tm.tm_mon + 1, tm.tm_year + 1900, tm.tm_hour, tm.tm_min, amPm);

    printf("\nDECODED TEXT: \n %s", cypher.original);

    AddToHistory(cypher);

    getch();
}

void SaveToFile(TextCypher cypher)
{
    char fName[25];
    FILE *fp;

    printf("ENTER A FILENAME: \n");
    CreateTextBox("%s", fName, 0);

    while(strcmp(fName, "") == 0)
    {
        printf("**ENTER A VALID FILENAME: \n");
        CreateTextBox("%s", fName, 0);
    }

    strcat(fName, ".cyph");///add extension

    if((fp = fopen(fName, "w+")) != NULL)
    {
        fwrite(&cypher, sizeof(TextCypher), 1, fp);
    }
    else
    {
        printf("=( File cannot be saved...");
    }
}

void OpenFromFile()
{

}
