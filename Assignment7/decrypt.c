#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <inttypes.h>
#include "dictionary.h"

#define INITIAL_SIZE (1024)
#define GROWTH_FACTOR (2)
#define MAX_LOAD_FACTOR (1)
/*
Sources: Dictionary implementation from Professor Aspnes's notes
	 GetLine from StackOverflow
	 Hash function from Dr Aspens' encrypt.c file
*/

struct dictionaryElement
{
	uint64_t key;
	char *value;
	struct dictionaryElement *next;
};

struct dictionary
{
	int totalSize;
	int numberOfElements;
	struct dictionaryElement **allElements;
};

/*
Function : Dictionary CreateDictionaryHelper
Input 	 : int size (Its the total size at the beginning)
Role	 : Holds logice for allocating pointers
Output   : Dictionary diction 
*/
Dictionary CreateDictionaryHelper(int size)
{
	Dictionary diction;
	diction = malloc(sizeof(*diction));
	
	assert(diction != 0);
	diction->totalSize = size;
	diction->numberOfElements = 0;
	diction->allElements = malloc(sizeof(struct dictionaryElement *) * diction->totalSize);
	
	assert(diction->totalSize != 0);
	
	for(int i = 0; i < diction->totalSize; i++)
	{
		diction->allElements[i] = 0;
	}
	return diction;
}

/*
Function : Dictionary CreateDictionary
Input 	 : void
Role	 : Calls CreateDictionaryHelper with size of 1024
Output   : Dictionary  
*/
Dictionary CreateDictionary()
{
	return CreateDictionaryHelper(INITIAL_SIZE);
}

/*
Function : void DictionaryDestroy
Input 	 : Dictionary diction
Role	 : Frees memory
Output   : void  
*/
void DictionaryDestroy(Dictionary diction)
{
	struct dictionaryElement *element;
	struct dictionaryElement *next;
	
	for(int i = 0; i < diction->totalSize; i++)
	{
		for(element = diction->allElements[i]; element != 0; element = next)
		{
			next = element->next;
			free(element->value);
			free(element);
		}
	}
	free(diction->allElements);
	free(diction);
}

/*
Function : static void grow
Input 	 : Dictionary diction, uint64_t saltHash
Role	 : Increases dictionary size incase it gets too big
Output   : void  
*/
static void grow(Dictionary diction, uint64_t saltHash)
{
	Dictionary diction2;
	struct dictionary swap;
	struct dictionaryElement *dictionElement;
	
	diction2 = CreateDictionaryHelper(diction->totalSize * GROWTH_FACTOR);
	
	for(int i = 0; i < diction->totalSize; i++)
	{
		for(dictionElement = diction->allElements[i]; dictionElement != 0; dictionElement = dictionElement->next)
		{
			DictionaryInsert(diction2, dictionElement->key, dictionElement->value, saltHash);
		}
	} 
	swap = *diction;
	*diction = *diction2;
	*diction2 = swap;
	DictionaryDestroy(diction2);
}

/*
Function : void DictionaryInsert
Input 	 : Dictionary diction, uint64_t hash, char *value, uint64_t saltHash
Role	 : Inserts with hash as uint64_t key and char *value as value
Output   : void  
*/
void DictionaryInsert(Dictionary diction, uint64_t hash, char *value, uint64_t saltHash)
{
	struct dictionaryElement *dictionElement;
	assert(value);
	dictionElement = malloc(sizeof(*dictionElement));
	
	assert(dictionElement);
	
	dictionElement->key = hash;
	dictionElement->value = strdup(value);
	
	hash = hash % diction->totalSize;
	dictionElement->next = diction->allElements[hash];
	diction->allElements[hash] = dictionElement;
	
	diction->numberOfElements++;
	
	if(diction->numberOfElements >= diction->totalSize * MAX_LOAD_FACTOR)
	{
		grow(diction, saltHash);
	}	
}

/*
Function : const char *DictionarySearch
Input 	 : Dictionary diction, uint64_t hash,  uint64_t saltHash
Role	 : Finds value in dictionary
Output   : char *value string if entry exist or NULL if not found
*/
const char *DictionarySearch(Dictionary diction, uint64_t hash, uint64_t saltHash)
{
	struct dictionaryElement *dictionElement;
	for(dictionElement = diction->allElements[hash % diction->totalSize]; dictionElement != 0; dictionElement = dictionElement->next)
	{
		
		if(dictionElement->key == hash)
		{
			return dictionElement->value;
		}
		
	}
	return 0;
}


/*
Professor's implementation of FNV
*/

#define FNV_PRIME_64 ((1ULL<<40)+(1<<8)+0xb3)
#define FNV_OFFSET_BASIS_64 (14695981039346656037ULL)

static void FNV1a(uint64_t *hash, const char *s)
{
    while(*s)
    {
        *hash ^= *s++;
        *hash *= FNV_PRIME_64;
    }
}

static uint64_t precomputeSaltHash(const char *salt)
{
    uint64_t hash = FNV_OFFSET_BASIS_64;
    FNV1a(&hash, salt);
    return hash;
}

static uint64_t passwordHash(uint64_t saltHash, const char *password)
{
    FNV1a(&saltHash, password);
    return saltHash;
}

#define PASSWORD_DELIMITER (':')
int main(int argc, char **argv)
{    
    uint64_t saltHash = precomputeSaltHash(argv[1]);
    
    Dictionary allPossiblePasswords;
    allPossiblePasswords = CreateDictionary();
    
    FILE *f = fopen(argv[2], "r");
    if(f == 0)
    {
    	perror(argv[2]);
    	exit(2);
    }
   
    char *line = NULL;
    size_t len = 0;
    while(getline(&line, &len, f) != -1)
    {
    	size_t length = strlen(line);
    	if(line[length -1] == '\n')
    	{
    		line[length -1] = '\0';
    	}
    	uint64_t hash = passwordHash(saltHash, line);
    	DictionaryInsert(allPossiblePasswords, hash, line, saltHash);
    }
    fclose(f);
    free(line);
	
	int c;
	while((c = getchar()) != EOF)
	{
		putchar(c);
		if(c == PASSWORD_DELIMITER)
		{
			uint64_t hash;
			scanf("%" SCNx64 "\n", &hash);
			const char *s = DictionarySearch(allPossiblePasswords, hash, saltHash);
			if(s == NULL)
			{
				 printf("%" PRIx64 "\n", hash);
			}
			else
			{
				puts(s);
			}
		}
	}
	DictionaryDestroy(allPossiblePasswords);
	
	return 0;
}
