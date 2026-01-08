// Implements a dictionary's functionality

#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>

#include "dictionary.h"

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
} node;

// TODO: Choose number of buckets in hash table
const unsigned int N = 26;

// Hash table
node *table[N];

int wordCount = 0;

// Returns true if word is in dictionary, else false
bool check(const char *word)
{
    // TODO
    int index = hash(word);
    node *current = table[index];
    while (current)
    {
        if (strcasecmp(current->word, word) == 0)
        {
            return true;
        }
        else
        {
            current = current->next;
        }
    }

    return false;
}

// Hashes word to a number
unsigned int hash(const char *word)
{

    int sum = 0;
    if (strlen(word) > 0)
    {
        sum += tolower(word[0]);
    }
    if (strlen(word) > 1)
    {
        sum += tolower(word[1]);
    }
    if (strlen(word) > 2)
    {
        sum += tolower(word[2]);
    }

    // TODO: Improve this hash function
    return sum % N;
}

// Loads dictionary into memory, returning true if successful, else false
bool load(const char *dictionary)
{
    // TODO
    FILE *file = fopen(dictionary, "r");
    if (file == NULL)
    {
        return false;
    }
    char word[LENGTH + 1];

    while (fscanf(file, "%s", word) == 1)
    {
        node *n = malloc(sizeof(node));
        if (n == NULL)
        {
            unload();
            return false;
        }
        strcpy(n->word, word);
        int index = hash(word);
        if (table[index])
        {
            node *temp = table[index];
            n->next = temp;
        }
        else
        {
            n->next = NULL;
        }
        table[index] = n;
        wordCount++;
    }
    fclose(file);
    return true;
}

// Returns number of words in dictionary if loaded, else 0 if not yet loaded
unsigned int size(void)
{
    // TODO
    return wordCount;
}

// Unloads dictionary from memory, returning true if successful, else false
bool unload(void)
{
    // TODO
    for (int i = 0; i < N; i++)
    {
        node *cursor = table[i];
        while (cursor)
        {
            node *temp = cursor;
            cursor = cursor->next;
            free(temp);
        }
    }
    return true;
}
