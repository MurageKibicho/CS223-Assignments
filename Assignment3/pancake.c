#include <stdio.h>
#include "pancake.h"
//gcc -g pancake.h pancake.c main.c -o  main

/*
*Function Name	: FlipHelper
*Input		: int x, int y, unsigned int *numberArray
*Role		: Reverse the elements in a number array
*Output	: Void
*/
void FlipHelper(int x, int y, unsigned int *numberArray)
{
	int currentIndex = x;
	int backWardIndex = y - 1;
	int arrayElementHolder;
	while(currentIndex < backWardIndex)
	{
		arrayElementHolder = numberArray[currentIndex];
		numberArray[currentIndex] = numberArray[backWardIndex];
		numberArray[backWardIndex] = arrayElementHolder;
		currentIndex++;
		backWardIndex--;
	}
	//for(int i = 0; i < 5; i++)
	//	printf("%d", numberArray[i]);
}


/*
*Function Name	: PrintHelper
*Input		: int x, int y, unsigned int *memory
*Role		: Print within range(x,y)
*Output	: Void
*/
	
void PrintHelper(int x, int y, unsigned int *memory)
{
	
	for(int  i = x; i < y; i++)
	{
		printf("%u", memory[i]);
		if(i != y - 1)
		{
			printf(" ");
		}
	}
	printf("\n");
}

//printf("RemBefore + RemAfter - RemAfter128 : %d", ((numberArray[3] +multiplier) % 256) + (numberThree % 256) -  ((numberThree % 256) + 128));

/*
*Function Name	: runPancakeProgram
*Input		: unsigned int *memory
*Role		: Logic for Pancake program
*Output	: Void
*/
void runPancakeProgram(unsigned int *memory)
{
	int counter = 0;
	int x;
	int y;
	
	while(memory[counter] < 4)
	{
		int n = memory[counter];
		switch(n)
		{
			case FLIP:
				x = memory[counter + 1];
				y = memory[counter + 2];
				FlipHelper(x,y, memory);
				counter+=3;
				break;
			case PRINT:
				x = memory[counter + 1];
				y = memory[counter + 2];
				PrintHelper(x, y, memory);
				counter+=3;
				break;
			case JUMP:
				counter = memory[counter + 1];
				break;
			case SKIP:
				x = memory[counter + 1];
				y = memory[counter + 2];
				if(memory[x] > memory[y])
				{
					//counter+=4;
					if(memory[counter + 3] == 0 || memory[counter + 3] == 1 || memory[counter + 3] == 3)
					{
						counter+=6;	
					}
					else if(memory[counter + 3] == 2)
					{
						counter+=5;
					}
					else if(memory[counter + 3] == 4)
					{
						counter+=4;
					}
				}
				else
				{
					counter+=3;
				}
				break;
			default:
				break;
		}
	}
}


/*int main()
{
	int memory[] = {2,12,1,0,1,0,1,0,1,0,1,0,1,2,12,
			0,2,4,3,2,3,2,12,0,4,6,3,4,5,2,12,
			0,6,8,3,6,7,2,12,0,8,10,3,8,9,2,12,
			0,10,12,3,10,11,2,12,1,0,12,4};
	//PrintHelper(2, 8, memory);
	runPancakeProgram(memory);
	return 0;
}*/




