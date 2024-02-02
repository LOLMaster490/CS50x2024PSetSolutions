// Implements a dictionary's functionality

#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#  define strcasecmp _stricmp 
#  define strncasecmp _strnicmp 
#include "dictionary.h"

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
} node;

// Choose number of buckets in hash table
const unsigned int N = 26 * LENGTH;

// Initialize a counter for keeping track of nubmer of items in hash table
int itemCounter = 0;

// Hash table
node *table[N];

// Returns true if word is in dictionary, else false
bool check(const char *word)
{
    int currentHash = hash(word);
    node *traversalPointer = table[currentHash];
    while (traversalPointer != NULL)
    {
        if (strcasecmp(traversalPointer->word, word) == 0)
        {
            return true;
        }
        traversalPointer = traversalPointer->next;
    }
    return false;
}

// Hashes word to a number
unsigned int hash(const char *word)
{
    unsigned int result = 0;
    // Sum all values of toupper() ASCII characters in a word minus value of uppercase A, which should results in more buckets which
    // helps with speed compared to number of buckets equal to size of alphabet, also should work better than buckets made up of
    // n-letter buckets as should be more probable to randomly hit a random sum of character index than random n-letter beginning of
    // a word.
    for (int i = 0, n = strlen(word); i < n; i++)
    {
        if ((word[i] >= 'A' && word[i] <= 'Z') || (word[i] >= 'a' && word[i] <= 'z'))
        {
            unsigned int resultDebug = toupper(word[i]) - 'A';
            result += resultDebug;
        }
    }
    return result;
}

// Loads dictionary into memory, returning true if successful, else false
bool load(const char *dictionary)
{
    FILE *dict = fopen(dictionary, "r");
    char *stringBuffer = malloc(LENGTH);
    while (fscanf(dict, "%s", stringBuffer) != EOF)
    {
        node *n = malloc(sizeof(node));
        if (n == NULL)
        {
            return false;
        }
        // COPY DATA INTO ALLOCATED MEMORY
        strcpy(n->word, stringBuffer);
        n->next = table[hash(stringBuffer)];
        // CONNECT CREATED NODE TO HASH TABLE
        table[hash(stringBuffer)] = n;
        itemCounter++;
    }

    free(stringBuffer);
    fclose(dict);
    // TODO
    return true;
}

// Returns number of words in dictionary if loaded, else 0 if not yet loaded
unsigned int size(void)
{
    if (itemCounter > 0)
    {
        return itemCounter;
    }
    else
    {
        return 0;
    }
}

// Unloads dictionary from memory, returning true if successful, else false
bool unload(void)
{
    node *cursor = table[0];
    node *tmp = cursor;
    for (int i = 0; i < N; i++)
    {
        cursor = table[i];
        tmp = cursor;
        while (cursor != NULL)
        {
            cursor = cursor->next;
            free(tmp);
            tmp = cursor;
        }
    }
    // TODO
    return true;
}
