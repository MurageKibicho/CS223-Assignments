#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Abstract data type for an editable string buffer.
typedef struct buffer *Buffer;

//Lol just learnt that size_t will never be negative
//Use while loop to free linked list, not for loop
//Single element in my linked list
struct linkedListElement
{
	char characterHolder;
	struct linkedListElement *previous;
	struct linkedListElement *next;	
};

//Struct holds entire linked list
//cursorArray is an array of cursor indices
struct buffer
{
	struct linkedListElement *start;
	struct linkedListElement **cursorArray;
	int lengthList;
	int numberOfCursors;
};

/*
*Function: bufferSize
*Input : (Buffer b)
*Role: Gives number of characters minus ending '\0'
*Output: sizeOfBuffer-1
*/
size_t bufferSize(Buffer b)
{
	size_t sizeOfBuffer = b->lengthList;
	return sizeOfBuffer-1;
}

/*
*Function: bufferCursors
*Input : (Buffer b)
*Role: Gives number of cursors in buffer
*Output: numberCursors
*/
size_t bufferCursors(Buffer b)
{
	size_t numberCursors = b->numberOfCursors;
	return numberCursors;
}

/*
*Function: bufferCreate
*Input : (size_t n)
*Role: Creates a character buffer with n cursors
*Output: Buffer b
*/
Buffer bufferCreate(size_t n)
{
	
	Buffer b;
	b = malloc(sizeof(struct buffer));
	b->start = malloc(sizeof(struct linkedListElement));	
	b->cursorArray = malloc(n * sizeof(struct linkedListElement));
	b->lengthList = 1;
	b->numberOfCursors = n;
	b->start->previous = NULL;
	b->start->next = NULL;
	b->start->characterHolder = '\0';
	for(int i = 0; i < n; i++)
	{
		b->cursorArray[i] = b->start;
	}
	return b;
}

/*
*Function: bufferDestroy
*Input : (Buffer b)
*Role: Frees malloc'd linked list elements, note while loop to free, not for loop
*Output: Buffer b
*/
void bufferDestroy(Buffer b)
{
	free(b->cursorArray);
	//free(b->start);
	struct linkedListElement *e;
	e = b->start;
	while(e != NULL)
	{
		struct linkedListElement *temp;
		temp = e;
		e = e->next;
		free(temp);
	}
	free(b);
}

/*
*Function: bufferInsert
*Input : (Buffer b, size_t i, char c)
*Role: Insert c before cursor i in Buffer b
*Output: Buffer b
*/
void bufferInsert(Buffer b, size_t i, char c)
{
	if(i >= bufferCursors(b) || c == '\0')
	{
		return;
	}	
	else
	{
		struct linkedListElement *currentElement = b->cursorArray[i];
		struct linkedListElement *newElement = malloc(sizeof(struct linkedListElement));
		
		newElement->characterHolder = c;
		newElement->previous = currentElement->previous;
		newElement->next = currentElement;
		
		currentElement->previous = newElement;
		
		if(newElement->previous == NULL)
		{
			b->start = newElement;
		}
		else
		{
			newElement->previous->next = newElement;	
		}
		
		b->lengthList++;			
	}
}

/*
*Function: bufferCursorForward
*Input : (Buffer b, size_t i)
*Role: Move cursor i to next character
*Output: void
*/
void bufferCursorForward(Buffer b, size_t i)
{
	if(i >= bufferCursors(b) || (b->cursorArray[i]->next == NULL))
	{
		return; 
	}
	else
	{
		b->cursorArray[i] = b->cursorArray[i]->next;		 
	}
}

/*
*Function: bufferCursorBack
*Input : (Buffer b, size_t i)
*Role: Move cursor i to previous character
*Output: void
*/
void bufferCursorBack(Buffer b, size_t i)
{
	if(i >= bufferCursors(b) || (b->cursorArray[i]->previous == NULL))
	{
		return; 
	}
	else
	{
		b->cursorArray[i] = b->cursorArray[i]->previous;		 
	}
}

/*
*Function: *bufferContents
*Input : (const Buffer b)
*Role: Save buffer contents to char*, don't free myself
*Output: char*
*/
char *bufferContents(const Buffer b)
{
	struct linkedListElement *e;
	size_t length = bufferSize(b);
	char* wordHolder = malloc(length+1);
	int i = 0;
	for(e = b->start; e != NULL; e = e->next)
	{
		wordHolder[i] = e->characterHolder;
		i++;
	} 
	wordHolder[length] = '\0';
	return wordHolder;
}

/*
int main()
{
	size_t n = 5;
	Buffer b = bufferCreate(n);
	//printf("%ld\n", bufferCursors(b));
	//bufferInsert(b, 1, 'a');
	bufferInsert(b, 1, 'b');
	char* cc = bufferContents(b);
	free(cc);
	bufferDestroy(b);
	return 0;
}*/
