/*
  Programmer    : Shawn Grant
  Date		    : 28,1, 2019
  Purpose	    : All functions in the encode and decode process
  Filename	    : EncoderDecoder.c
*/

#include <string.h>
#include <ctype.h>
#include <stdio.h>
#include <time.h>
#include "CYPHER.H"

#define CAPS_SPECIFIER "<[C]>"
#define SPACE_SPECIFIER "<[S]>"
#define NUMBER_SPECIFIER "<[N]>"
#define SYMBOL_SPECIFIER "<[@]>"
#define INCREMENT 5

const char lettersUpr[26] = {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M',
                        'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z'};

const char lettersLwr[26] = {'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm',
                        'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z'};

const char codes[26] =      {'x', '+', '-', '_', 'V', ';', '/', '[', ']', '{', '}', ':', '?',
                        '!', '@', '#', '%', '6', '^', '&', '*', '(', ')', '<', '>', 'z'};

void Encode(TextCypher cypher)
{
    char newTxt[700];
    int i, index, newStringLength;
    time_t t = time(NULL);
    struct tm tm = *localtime(&t);

    system("cls");
    fflush(stdin);

    /// ///////// GET USER DATA ////////////

    printf("ENTER RECIPIENT USERNAME:\n");
    CreateTextBox("%s", cypher.reciever, 0);
    printf("ENTER TEXT (ENGLISH):\n");
    CreateLargeTextBox("%s", cypher.original);

    newStringLength = strlen(cypher.original);
    strcpy(newTxt, cypher.original); //move string from the structure to another var for easy referencing

    /// //////////encoding process ///////////////
    for (i = 0; i < newStringLength; i++)
    {
        if(isdigit(newTxt[i]) == 1)//if the character is a number
        {
            //add the number specifier before then
            strInsert(newTxt, NUMBER_SPECIFIER, i);
            ///update the loop run length
            newStringLength = strlen(newTxt);
            i += strlen(NUMBER_SPECIFIER);
        }
        else if(isspace(newTxt[i]) == 1)//if the character is a space
        {
            //add the uppercase specifier before
            strInsert(newTxt, SPACE_SPECIFIER, i);
            ///update the loop run length
            newStringLength = strlen(newTxt);
            i += strlen(SPACE_SPECIFIER);
        }
        else//not a number, space or symbol; Swap letter for a code
        {
            if(isupper(newTxt[i]) == 1)//for upper case letters
            {
                //add the uppercase specifier before
                strInsert(newTxt, CAPS_SPECIFIER, i);
                ///update the loop run length
                newStringLength = strlen(newTxt);
                i += strlen(CAPS_SPECIFIER);
                //swap
                LetterToCode(newTxt, i, newTxt[i], 1);
            }else
            {
                LetterToCode(newTxt, i, newTxt[i], 0);
            }
        }
    }

    strcpy (cypher.encoded, newTxt);//copy encoded text to the structure

    /// Add time/date to the cypher
    sprintf(cypher.dateTime, "%i/%i/%i @ %i:%i", tm.tm_mday, tm.tm_mon+1, tm.tm_year+1900, tm.tm_hour-12, tm.tm_min);

    ///add recipient name to the coded string


    printf("\nENCODED TEXT: \n %s", cypher.encoded);

    AddToHistory(cypher);
    //SaveToFile(cypher);

    getch();
}

void Decode(TextCypher cypher)
{
    char newTxt[700];
    int i, index, newStringLength;

    system("cls");
    fflush(stdin);

    printf("ENTER TEXT (ENCCODE):\n");
    CreateLargeTextBox("%s", cypher.original);

    newStringLength = strlen(cypher.original);
    strcpy(newTxt, cypher.original);

    ShowLoading();
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
    }else
    {
        printf("=( File cannot be saved...");
    }
}

void OpenFromFile()
{

}

void LetterToCode(char str[], int at, char letter, int uCase)
{
    int index;

    ///uCase is wether or not the char is upper(1) or lower case(0)
    if(uCase == 1)
    {
        index = strIndexOf(letter, lettersUpr);
        str[at] = codes[index];
    }else{
        index = strIndexOf(letter, lettersLwr);
        str[at] = codes[index];
    }

}

void CodeToLetter(char str[], int at, char code, int uCase)
{
    int index;

    ///uCase is wether or not the char is upper(1) or lower case(0)
    if(uCase == 1)
    {
        index = strIndexOf(code, codes);
        str[at] = lettersUpr[index];
    }else{
        index = strIndexOf(code, codes);
        str[at] = lettersLwr[index];
    }

}

