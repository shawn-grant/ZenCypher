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

    return result;//return 1 if str does end with ending
}

void strRemove(char text[] ,char oldTxt[], int at)
{

}

void strInsert(char text[] ,char strVal[], int at)
{
    char insertedTxt[500];

    ///this function inserts a string 'strVal' into 'text' at index 'at'
    strncpy(insertedTxt, text, at);
    insertedTxt[at] = '\0';
    strcat(insertedTxt, strVal);
    strcat(insertedTxt, text + at);

    printf("\n Inserted: %s", insertedTxt);
    //copy insertedtext back to the original variable to reflect change in driver
    strcpy(text, insertedTxt);
}

int strIndexOf(char of, char in[])
{
    int index = 0;
    while(in[index] != of)
    {
        index++;
    }

    return index;
}
