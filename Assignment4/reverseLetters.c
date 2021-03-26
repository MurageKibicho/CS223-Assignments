#include <stdio.h>
#include <string.h>
#include <ctype.h>

//Array to hold all letters
static char letters[100000000];

/*
*Function name	: 	FlipHelper
*Input		: 	char letterArray[],int index
*Role		: 	Holds logic for reversing letters
*Output	: 	void
*/
void FlipHelper(char letterArray[],int index)
{
	int currentIndex = 0;
	int backWardIndex = index;
	char arrayElementHolder;
	while(currentIndex < backWardIndex)
	{
		if(!isalpha(letterArray[currentIndex]))
		{
			currentIndex++;
		}
		else if(!isalpha(letterArray[backWardIndex]))
		{
			backWardIndex--;
		}
		else
		{
			if(isupper(letterArray[currentIndex]) && islower(letterArray[backWardIndex]))
			{
				arrayElementHolder = letterArray[currentIndex];
				letterArray[currentIndex] = toupper(letterArray[backWardIndex]);
				letterArray[backWardIndex] = tolower(arrayElementHolder);		
				currentIndex++;
				backWardIndex--;
			}
			else if(islower(letterArray[currentIndex]) && isupper(letterArray[backWardIndex]))
			{
				arrayElementHolder = letterArray[currentIndex];
				letterArray[currentIndex] = tolower(letterArray[backWardIndex]);
				letterArray[backWardIndex] = toupper(arrayElementHolder);		
				currentIndex++;
				backWardIndex--;
			}
			else
			{
				arrayElementHolder = letterArray[currentIndex];
				letterArray[currentIndex] = letterArray[backWardIndex];
				letterArray[backWardIndex] = arrayElementHolder;		
				currentIndex++;
				backWardIndex--;
			}	
		}
	}
	for(int i = 0; i < index+1; i++)
		putchar(letterArray[i]);
}
/*
*Function name	: 	ReverseLetters
*Input		: 	None
*Role		: 	Reads characters into letters Array
*Output	: 	void
*/
void ReverseLetters()
{
	int c; 
	int index = 0;
	while((c = getchar()) != EOF)
	{
		
		letters[index] = c;
		index++;
		
	}
	index--;
	FlipHelper(letters, index);
}
int main(int argc, char **argv)
{
	ReverseLetters();
	
	return 0;
}

