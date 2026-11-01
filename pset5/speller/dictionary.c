// Implements a dictionary's functionality

#include <ctype.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
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

// Returns true if word is in dictionary, else false
bool check(const char *word)
{
    // TODO
    return false;
}

// Hashes word to a number
unsigned int hash(const char *word)
{
    // TODO: Improve this hash function
    return toupper(word[0]) - 'A';
}

bool addwordtodict(const char word[]) {
    unsigned int h = hash(word);
    printf("%s ; h => %d\n", word, h);
    // table[h]
    return true;
}

// Loads dictionary into memory, returning true if successful, else false
bool load(const char *dictionary)
{
    FILE *f = fopen(dictionary, "r");
    if (f == NULL) {
        return false;
    }

    char word[LENGTH + 1];
    int chIndex = 0;
    int ch;
    while ((ch = fgetc(f)) != EOF)
    {
        if (!isalpha(ch) && ch != '\'') {
            word[chIndex] = '\0';
            chIndex = 0;
            if (!addwordtodict(word)) {
                return false;
            }
        } else {
            word[chIndex++] = ch;
        }
    }

    fclose(f);

    return false;
}

// Returns number of words in dictionary if loaded, else 0 if not yet loaded
unsigned int size(void)
{
    // TODO
    return 0;
}

// Unloads dictionary from memory, returning true if successful, else false
bool unload(void)
{
    // TODO
    return false;
}

int main(int argc, char *argv[])
{
    load(argv[1]);
}
