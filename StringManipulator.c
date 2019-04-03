/*
  Programmer    : Shawn Grant
  Date		    : 28,1, 2019
  Purpose	    : Perform string functions that aren't given in string.h
  Filename	    : StringManipulator.c
*/

#include <string.h>
#include <stdlib.h>
#include <stdio.h>

/// Appends a character to a string
void strAppend(char str[], char c)
{
    str[strlen(str)] = c;
    str[strlen(str)+1] = '\0';
}

/// Function to determine if a string ends with the specified ending
/// Returns 1 if the ending matches, else 0
int strEndsWith(char str[], char ending[])
{
    int i, j, result;
    j = strlen(str);

    for (i = strlen(ending); i >= 0; i--)
    {
        if(str[j] == ending[i] && result != 0)
            result = 1;
        else
            result = 0;

        j--;
    }

    return result;
}

///this function inserts a string 'strVal' into 'text' at index 'at'
void strInsert(char text[] ,char strVal[], int at)
{
    char insertedTxt[500];

    strncpy(insertedTxt, text, at);
    insertedTxt[at] = '\0';
    strcat(insertedTxt, strVal);
    strcat(insertedTxt, text + at);

    //copy insertedtext back to the original variable to reflect change in calling function
    strcpy(text, insertedTxt);
}

///Find the index of a character in a string
int strIndexOf(char of, char in[])
{
    int index = 0;
    while(in[index] != of)
    {
        index++;
    }

    return index;
}

int isSymbol(char ch)
{
    /* Alphabet check */
    if((ch >= 'a' && ch <= 'z') || (ch >= 'A' && ch <= 'Z'))
    {
        return 0;
    }
    else
    {
        if(ch >= '0' && ch <= '9')
        {
            return 0;
        }
        else
        {
            if(isspace(ch) == 0)
            {
                return 1;
            }
        }
    }
}
