#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct wordArray *WordArray;

struct wordArray
{
	int length;
	int *value;
};

/*
*Name	: Powerof
*Input	: int number, int power
*Role	: Raise number to power
*Output : int value
*/
int Powerof(int number, int power)
{	
	int value = 1;
	for(int i = 0; i < power; i++)
	{
		value *= number;
	}
	return value;
}
/*
*Name	: wordArrayCreate
*Input	: unsigned int n
*Role	: Malloc struct
*Output : WordArray w
*/
WordArray wordArrayCreate(unsigned int n)
{
	WordArray w;
	long sizeOfArray = Powerof(26, n);
	w = malloc(sizeof(struct wordArray));	
	w->value = calloc(sizeOfArray, sizeof(int));
	w->length = n;
	return w;
}
/*
*Name	: wordArrayDestroy
*Input	: WordArray w
*Role	: free WordArray
*Output : void
*/
void wordArrayDestroy(WordArray w)
{
	free(w->value);
	free(w);
}
/*
*Name	: wordArrayKeyLength
*Input	: WordArray w
*Role	: Return length of WordArray w
*Output : int keyLength
*/
int wordArrayKeyLength(WordArray w)
{
	int keyLength = 0;
	keyLength = w->length;
	return keyLength;
}
/*
*Name	: *wordArrayRef
*Input	: WordArray w, const char *key
*Role	: Returns a pointer to index key(Base 26 to decimal converter)
*Output : &(w->value[result])
*/
int *wordArrayRef(WordArray w, const char *key)
{
	int charLength = strlen(key);
	int wordArrayLength = wordArrayKeyLength(w);
	int result = 0;
	int power = 0;
	
	if(charLength != wordArrayLength)
	{
		return 0;
	}
	else
	{
		for(int i = charLength - 1; i >= 0; i--)
		{
			if(key[i] < 'a' || key[i] > 'z')
			{
				return 0;
			}
			else
			{
				result += (int) (key[i] - 'a' ) * Powerof(26, power);
				power++;
			}
		}
		return &(w->value[result]);	
	}	
}
/*
*Name	: *wordArrayMinKey
*Input	: WordArray w
*Role	: Creates smallest key of size w->length
*Output : char *wordHolder
*/
char *wordArrayMinKey(WordArray w)
{
	int length = w->length;
	char* wordHolder = malloc(length + 1);
	
	for(int i = 0; i < length; i++)
	{
		wordHolder[i] = 'a';
	}
	wordHolder[length] = '\0';
	return wordHolder;
}
/*
*Name	: wordArrayIncKey
*Input	: char *s
*Role	: Adds one to end of char8 i.e("abc")=>("abd") 
*Output : char *wordHolder
*/
int wordArrayIncKey(char *s)
{
	int charLength = strlen(s);
	int numberOfZ = 0;
	
	for(int i = charLength - 1; i >= 0; i--)
	{
		if((s[i] + 1) <= 122)
		{
			s[i]++;
			break;
		}
		else
		{
			numberOfZ++;
			s[i] = 'a';
		}	
	}
	
	if(numberOfZ >= charLength)
	{
		return 1;
	}
	else
	{
		return 0;
	}
}
/*
*Name	: wordArrayPrint
*Input	: WordArray w
*Role	: Prints  (WordArray w) from min to max i.e ("aaa")=>("zzz")
*Output : void
*/
void wordArrayPrint(WordArray w)
{
	char *key = wordArrayMinKey(w);
	
	do
	{
		printf("%s ", key);
        	printf("%d\n",*wordArrayRef(w, key));
    	} while(wordArrayIncKey(key) == 0);
}


