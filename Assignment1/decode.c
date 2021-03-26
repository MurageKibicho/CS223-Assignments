#include <stdio.h>
#include <ctype.h>

/*
*Function name	: 	RepeatPrinter
*Arguments	:	int encodedLength, int character
*Return type	:	void
*Role		:	Holds a loop to print characters 
*/
void RepeatPrinter(int encodedLength, int character)
{
	for(int i = 0; i < encodedLength + 1; i++)
	{
		putchar(character);
	}
}

/*
*Function name	: 	Decode
*Arguments	:	None
*Return type	:	void
*Role		:	Holds Logic for decoding Run-Length 
*/
void Decode()
{
	int c;
	int next;
	while((c = getchar()) != EOF)
	{
		if(isdigit(c))
		{
			next = getchar();
			RepeatPrinter(c - '0', next);
		}
		else
		{
			putchar(c);
		}
	}
}

int main(int argc, char **argv)
{
	Decode();
	return 0;
}

