/*
  Programmer    : Shawn Grant
  Date		    : 28,1, 2019
  Purpose	    : All functions in the encode and decode process
  Filename	    : EncoderDecoder.c
*/

#include <string.h>
#include <ctype.h>
#include <conio.h>
#include <stdio.h>
#include <time.h>
#include "CYPHER.H"

#define SPACE_SPECIFIER "<[S]>"
#define NUMBER_SPECIFIER "<[N]>"
#define SYMBOL_SPECIFIER "<[@]>"

#define INCREMENT 5
#define UPPER 9
#define LOWER 0

void Encode(TextCypher cypher)
{
    char inputStr[700], newTxt[700] = "", amPm[3], asciiValTxt[4];
    int i, asciiVal;
    time_t t = time(NULL);
    struct tm tm = *localtime(&t);
    int key, calculatedKey;

    key = (rand() % (UPPER - LOWER + 1)) + LOWER;
    calculatedKey = ((key * 5) ) - key;

    printf("key = %i\n", key);//debugging statement
    printf("New key = %i\n", calculatedKey);//debugging statement

    system("cls");
    fflush(stdin);

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
            strcat(newTxt, &inputStr[i]);
            //newTxt[i] += INCREMENT;
        }
        else if(isspace(inputStr[i]) != 0)//if the character is a space
        {
            //add the uppercase specifier before
            strcat(newTxt, SPACE_SPECIFIER);
        }
        else if(isSymbol(inputStr[i]) != 0)//if the character is a symbol
        {
            //add the uppercase specifier before
            strcat(newTxt, SYMBOL_SPECIFIER);
            strcat(newTxt, &inputStr[i]);
        }
        else//not a number, space or symbol
        {
            asciiVal = inputStr[i];

            printf("\n%c is %i\n", inputStr[i], asciiVal);//debugging statement
            itoa(asciiVal, asciiValTxt, 10);

            if(asciiVal < 100)//add 0 before to ensure groups of 3s
            {
                strInsert(asciiValTxt, "0", 0);
            }
            strcat(newTxt, asciiValTxt);
        }
    }

    //add the new key
    //newTxt[i] = calculatedKey;
    strcpy (cypher.encoded, newTxt);//copy encoded text to the structure

    /// Add time/date to the cypher
    tm.tm_hour >= 12? strcpy(amPm, "PM"):strcpy(amPm, "AM");

    if(tm.tm_hour > 12) tm.tm_hour -= 12;

    sprintf(cypher.dateTime, "%i/%i/%i @ %i:%i %s",
            tm.tm_mday, tm.tm_mon+1, tm.tm_year+1900, tm.tm_hour, tm.tm_min, amPm);

    ///add recipient name to the coded string here


    printf("\nENCODED TEXT: \n %s", cypher.encoded);

    AddToHistory(cypher);

    getch();
}

void Decode(TextCypher cypher)
{
    /*char newTxt[700];
    int i, index, newStringLength;

    system("cls");
    fflush(stdin);

    printf("ENTER THE CODE:\n");
    CreateLargeTextBox("%s", cypher.encoded);

    newStringLength = strlen(cypher.original);
    strcpy(newTxt, cypher.original);
    */
    ShowLoading();

    /*
        if (strPresentAtIndex(text, CAPS_SPECIFIER, i) == 1)//is a caps
            strRemove(text, strlen(CAPS_SPECIFIER), i);
            newStringLength = strlen(txt);
            i-= strlen(CAPS_SPECIFIER);
            codeToLetter(text, i, text[i], 1);
        else if (strPresentAtIndex(text, NUM_SPECIFIER, i) == 1)
            strRemove(text, strlen(NUM_SPECIFIER), i);
            newStringLength = strlen(txt);
            i-= strlen(NUM_SPECIFIER);
            codeToLetter(text, i, text[i], 0);
        else if (strPresentAtIndex(text, SPACE_SPECIFIER, i) == 1)
            strRemove(text, strlen(SPACE_SPECIFIER), i);
            newStringLength = strlen(txt);
            i-= strlen(SPACE_SPECIFIER);
            codeToLetter(text, i, text[i], 0);
        else if (strPresentAtIndex(text, SYMBOL_SPECIFIER, i) == 1)
            strRemove(text, strlen(SYMBOL_SPECIFIER), i);
            newStringLength = strlen(txt);
            i-= strlen(SYMBOL_SPECIFIER);
        else

    */
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
