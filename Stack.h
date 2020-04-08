/*Title: Operating and Maintaining Stack
  Name:	Shawn Grant
  Date:	1/4/2020
  File:	Stack.h
*/

#ifndef STACK_H_INCLUDED
#define STACK_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#define MAX 5 //size of the array used to store the list

//definition of the record
typedef struct
{
    int storage[MAX]; //tool used to store the stack
    int top;
} Stack;


/*Stack prototypes */
Stack createStack();
void push(int, Stack*);
int pop(Stack*);
bool isFull(Stack);
bool isEmpty(Stack );
void printStack(Stack);

#endif // STACK_H_INCLUDED
