#include <stdio.h>
#include <ctype.h>
#include <stdbool.h>

/*
*Function name	: 	WhenCounterIsZero
*Arguments	:	int previous
*Return type	:	void
*Role		:	Contains logic for time counter value is 0 
*/
void WhenCounterIsZero(int previous)
{
	if(isdigit(previous))
	{
		putchar('0');
		putchar(previous);
	}
	else
	{
		putchar(previous);
	}
}

/*
*Function name	: 	WhenCounterIsOne
*Arguments	:	int previous
*Return type	:	void
*Role		:	Contains logic for time counter value is one 
*/
void WhenCounterIsOne(int previous)
{
	if(isdigit(previous))
	{
		putchar('1');
		putchar(previous);
	}
	else
	{
	putchar(previous);
	putchar(previous);
	}
}

/*
*Function name	: 	RunLength
*Arguments	:	int previous, int c, int counter
*Return type	:	void
*Role		:	Organises logic for Run Length Encoding 
*/
void RunLength(int previous, int c, int counter)
{
	while(true)
	{
		c = getchar();
		if(previous == c)
		{
			if(counter < 9)
			{
				counter++;
			}
			else
			{
				putchar('9');
				counter = 0;
				putchar(previous);
			}	
		}
		else if(previous == EOF)
		{
			//Allows us to handle case when previous initialized to EOF 
		}
		else if(counter == 0)
		{
			WhenCounterIsZero(previous);
			counter = 0;
		}
		else if(counter == 1)
		{
			WhenCounterIsOne(previous);
			counter = 0;
		}
		else
		{
			putchar(counter+'0');
			putchar(previous);
			counter = 0;
		}
		previous = c;
		if(c == EOF)
		{
			break;
		}
	}
}

/*
*Function name	: 	Encode
*Arguments	:	None
*Return type	:	void
*Role		:	Holds RunLength function 
*/
void Encode()
{
	int c = 0;
	int counter = 0;
	int previous = EOF;
	RunLength(previous, c, counter);	
}

int main(int argc, char **argv)
{
	Encode();
	return 0;
}
