#include <stdio.h>
#include "printFixed.h"
#include <limits.h>

/*
*Function Name	: FindNumberOfDigits
*Input		: long long unsigned number
*Role		: Find the number of digits in an unsigned number
*Output	: int numberOfDigits
*/
int FindNumberOfDigits(long long unsigned number)
{
	int numberOfDigits = 0;
	while(number != 0)
	{
		number = number / 10;
		numberOfDigits++;
	}
	return numberOfDigits;
}

/*
*Function Name	: FindNumberOfDigitsSigned
*Input		: long long signed number
*Role		: Find the number of digits in a signed number
*Output	: int numberOfDigits
*/
int FindNumberOfDigitsSigned(long long number)
{
	int numberOfDigits = 0;
	while(number != 0)
	{
		number = number / 10;
		numberOfDigits++;
	}
	return numberOfDigits;
}

/*
*Function Name	: ReverseArray
*Input		: int numberArray[]
*Role		: Reverse the elements in a number array
*Output	: Void
*/
void ReverseArray(int numberArray[])
{
	int currentIndex = 0;
	int backWardIndex = 19;
	int arrayElementHolder;
	while(currentIndex < backWardIndex)
	{
		arrayElementHolder = numberArray[currentIndex];
		numberArray[currentIndex] = numberArray[backWardIndex];
		numberArray[backWardIndex] = arrayElementHolder;
		currentIndex++;
		backWardIndex--;
	}
}

/*
*Function Name	: PutInNumberArraySigned
*Input		: long long signed number, int numberOfDigits, int numberArray[]
*Role		: Put each digit of a signed number in a number array
*Output	: Void
*/
void PutInNumberArraySigned(long long number, int numberOfDigits, int numberArray[])
{
	int lastDigit = 0;
	
	for(int i  = 0; i < 20; i++)
	{
		lastDigit = number % 10;
		number = number / 10;
		numberArray[i] = lastDigit;
	}
	ReverseArray(numberArray);	
}

/*
*Function Name	: PutInNumberArray
*Input		: long long unsigned number, int numberOfDigits, int numberArray[]
*Role		: Put each digit of an unsigned number in a number array
*Output	: Void
*/
void PutInNumberArray(long long unsigned number, int numberOfDigits, int numberArray[])
{
	int lastDigit = 0;
	
	for(int i  = 0; i < 20; i++)
	{
		lastDigit = number % 10;
		number = number / 10;
		numberArray[i] = lastDigit;
	}
	ReverseArray(numberArray);	
}

/*
*Function Name	: PrintDigits
*Input		: int precision, int numberOfDigits, int numberArray[],char separator, char decimalPoint, int nonDecimalDigits, 			int remainder
*Role		: Hold logic for printing digits and separators
*Output	: Void
*/
void PrintDigits(int precision, int numberOfDigits, int numberArray[],char separator, char decimalPoint, int nonDecimalDigits, int remainder)
{	
	int index = 0;
	int totalPrint = 0;
	if(remainder == 0){}
	else if(remainder == 1)
	{
		printf("%d", numberArray[20 - numberOfDigits]);
		if(nonDecimalDigits >= 3)
		{
		putchar(separator);
		}
		else
		{
		putchar(decimalPoint);
		}
		totalPrint = 1;
	}
	else if(remainder == 2)
	{
		printf("%d", numberArray[20 - numberOfDigits]);
		printf("%d", numberArray[21 - numberOfDigits]);
		if(nonDecimalDigits >= 3)
		{
		putchar(separator);
		}
		else
		{
		putchar(decimalPoint);
		}
		totalPrint = 2;
	}
	for(int i = (20 + remainder) - numberOfDigits; i < 20 - precision; i++)
	{
		printf("%d",numberArray[i] );
		totalPrint++;
		numberOfDigits--;
		index++;
		if(index % 3 == 0)
		{
			if(totalPrint < nonDecimalDigits)
			{
				putchar(separator);
			}
			else if(totalPrint >= nonDecimalDigits)
			{
				putchar(decimalPoint);
			}
		}
	}	
	for(int j = 20 - precision; j < 20; j++)
	{
		printf("%d", numberArray[j]);
	}
}

/*
*Function Name	: PutSeparators
*Input		: int precision, int numberOfDigits, int numberArray[],char separator, char decimalPoint
*Role		: Coordinates calls to PrintDigits()
*Output	: Void
*/
void PutSeparators(int precision, int numberOfDigits, int numberArray[],char separator, char decimalPoint)
{
	int nonDecimalDigits = 0;
	int remainderModThree;
	int index;
		
	if(precision == 0)
	{
		for(int i = 20 - numberOfDigits; i < 20; i++)
		{
			printf("%d",numberArray[i]);
			numberOfDigits--;
			index++;
			if(numberOfDigits % 3 == 0)
			{
				if(numberOfDigits > 0)
				{
					putchar(separator);
				}
				else if(numberOfDigits <= 0)
				{
					putchar(decimalPoint);
				}
			}
		}
	}
	else if (precision >= numberOfDigits)
	{
		int numberOfZeros = precision - numberOfDigits;
		printf("0");
		putchar(decimalPoint);
		for(int i = 0 ; i < numberOfZeros; i++)
		{
			printf("0");
		}
		for(int i = 20 - numberOfDigits; i < 20; i++)
		{
			printf("%d", numberArray[i]);
		}	
	}
	else
	{
	nonDecimalDigits = numberOfDigits - precision;
	remainderModThree = nonDecimalDigits % 3 ;
	PrintDigits(precision, numberOfDigits, numberArray, separator, decimalPoint, nonDecimalDigits,remainderModThree);
	}
}

/*
*Function Name	: printFixed
*Input		: long long number, char separator, char decimalPoint, unsigned int precision
*Role		: Coordinates calls to PutSeparators()
*Output	: Void
*/
void printFixed(long long number, char separator, char decimalPoint, unsigned int precision)
{
	int numberArray[20] = {0};
	int numberOfDigits = FindNumberOfDigits(number);
	
	if(number == 0)
	{
		numberOfDigits = 1;
		PutSeparators(precision, numberOfDigits, numberArray,separator,decimalPoint);
	}
	else if(number < 0 && number >= -9223372036854775807)
	{
		printf("-");
		numberOfDigits = FindNumberOfDigitsSigned(number);
		long long newNumber = number*-1;
		PutInNumberArray(newNumber, numberOfDigits,numberArray);
		PutSeparators(precision, numberOfDigits, numberArray,separator,decimalPoint);
	}
	else if(number < 0 )
	{
		printf("-");
		long long newNumber = number;
		PutInNumberArray(newNumber, numberOfDigits,numberArray);
		PutSeparators(precision, numberOfDigits, numberArray,separator,decimalPoint);
	}
	else
	{
		PutInNumberArray(number, numberOfDigits,numberArray);
		PutSeparators(precision, numberOfDigits, numberArray,separator,decimalPoint);
	}
}

/*
int main()
{
	printFixed(0, ',', '.', 0);
	return 0;
}*/
