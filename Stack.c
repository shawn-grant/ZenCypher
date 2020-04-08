/*Title: Operating and Maintaining Stack
  Name: Shawn Grant
  Date:	1/4/2020
  File:	Stack.c
*/

#include "Stack.h"

Stack createStack()
{
    Stack newStack;
    newStack.top = 0;
    return newStack;
}

bool isFull(Stack s)
{
	return s.top >= MAX;
}

void push(int element, Stack *s)
{
    if(isFull(*s)) //check if the stack is empty
    {
        printf("\n Element cannot be inserted ");
    }
    else
    {
        s->storage[s->top] = element;
        s->top++;
    }
}

int pop(Stack *s)
{
    int e;

    if(isEmpty(*s))
    {
        printf("\nValue cannot be deleted, it does not exist");
        return -1;
    }
    else
    {
        e = s->storage[s->top-1];
        s->top--;
        return e;
    }
}

void printStack(Stack s)
{
    int i;

    if(isEmpty(s))
    {
        printf("\nStack is empty");
    }
    else
    {
        printf("\n\nSTACK");
        printf("\n\n------------");
        printf("\n  [%i] <-top", s.storage[s.top-1]);
        for(i=s.top-2; i>=0; i--)
        {
            printf("\n  [%i]", s.storage[i]);
        }
        printf("\n-----------");
    }
}

bool isEmpty(Stack s)
{
	return s.top == 0;
}

