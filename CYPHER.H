/*
  Programmer    : Shawn Grant
  Date		    : 28,1, 2019
  Purpose	    : Contains structs used in the program and pprototypes
  Filename	    : CYPHER>H
*/

#ifndef CYPHER_H_INCLUDED
#define CYPHER_H_INCLUDED

typedef struct
{
    int day;
    int month;
    int year;
}Date;

///data type to hold the before and after text of an encryption
typedef struct
{
    char original[500];
    char encoded[700];
    char reciever[30];
}TextCypher;

//encoding
void Encode(TextCypher);
void Decode(TextCypher);
void SaveToFile(char []);
void OpenFromFile();
//string
void strReplace(char [], char [], char []);
void strRemove(char text[] ,char oldTxt[], int);
void strInsert(char [] ,char [], int);
int strIndexOf(char, char[]);
int strEndsWith(char[], char[]);
//history
void AddToHistory(TextCypher);
void ShowHistory();
void RemoveItem(int);
void Clear();

#endif // CYPHER_H_INCLUDED
