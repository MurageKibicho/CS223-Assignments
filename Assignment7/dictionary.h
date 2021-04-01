#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <inttypes.h>

typedef struct dictionary *Dictionary;

Dictionary CreateDictionary();

void DictionaryDestroy(Dictionary diction);

void DictionaryInsert(Dictionary diction, uint64_t hash, char *value, uint64_t saltHash);

const char *DictionarySearch(Dictionary diction, uint64_t hash, uint64_t saltHash);

static void FNV1a(uint64_t *hash, const char *s);

static uint64_t precomputeSaltHash(const char *salt);

static uint64_t passwordHash(uint64_t saltHash, const char *password);


