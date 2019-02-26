/*
  Programmer    : Shawn Grant
  Date		    : 28,1, 2019
  Purpose	    : Perform string functions that arent given in string.h
  Filename	    : StringManipulator.c
*/

#include <string.h>
#include <stdio.h>

void strReplace(char text[] ,char oldTxt[], char newTxt[])
{

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
        {
            result = 1;
        }else
        {
            result = 0;
        }
        j--;
    }

    return result;
}

/// Remove 'numChar' characters from 'text' starting at index 'at'
void strRemove(char text[], int numChars, int at)
{
    int i;

    for (i = 0; i < numChars; i++)
    {
        memmove(&text[at], &text[at + 1], strlen(text) - at);
        //at++;
    }

    //strcpy(text, newText);
}

int strPresentAtIndex(char text[], char subString[], int at)
{
    int i, j;
    int len = strlen(subString);
    int result;

    for(i = 0; i < len-1; i++)
    {
        if(text[at + i] == subString[j] && result != 0)
        {
            result = 1;
        }
        else
        {
            result = 0;
        }
        j++;
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

    printf("\n Inserted: %s", insertedTxt);
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
    else if(ch >= '0' && ch <= '9')
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
