/*Title: Operating and Maintaining Stack
  Name: Shawn Grant
  Date:	1/4/2020
  File:	Stack.c
*/
#include "CYPHER.H"

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

void push(TextCypher element, Stack *s)
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

TextCypher pop(Stack *s)
{
    TextCypher e;

    if(isEmpty(*s))
    {
        printf("\nValue cannot be deleted, it does not exist");
        return e;
    }
    else
    {
        e = s->storage[s->top-1];
        s->top--;
        return e;
    }
}

bool isEmpty(Stack s)
{
	return s.top == 0;
}

