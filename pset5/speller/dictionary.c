// Implements a dictionary's functionality

#include <ctype.h>
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
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

char *strToLower(const char *word) {
    int strLen = strlen(word);
    char * lWord = malloc(strLen + 1);
    if (lWord == NULL)
        return NULL;

    for (int i = 0; i < strLen; i++) {
        lWord[i] = tolower(*(word + i));
    }
    lWord[strLen] = '\0';

    return lWord;
}

// Returns true if word is in dictionary, else false
bool check(const char *word)
{
    char *lWord = strToLower(word);
    if (lWord == NULL) {
        return false;
    }

    for (int i = 0; i < N; i ++) {
        node *currentNode = table[i];
        while (currentNode != NULL)
        {
            if (strcmp(currentNode->word, lWord) == 0) {
                free(lWord);
                return true;
            }

            currentNode = currentNode->next;
        }

    }

    free(lWord);
    return false;
}

// Hashes word to a number
unsigned int hash(const char *word)
{
    // TODO: Improve this hash function
    return toupper(word[0]) - 'A';
}

bool addwordtodict(const char word[]) {
    if (strlen(word) > LENGTH) {
        return false;
    }
    unsigned int h = hash(word);
    // printf("%s: h => %d\n", word, h);
    node *newNode = malloc(sizeof(node));

    if (newNode == NULL) {
        return false;
    }

    newNode->next = NULL;
    strcpy(newNode->word, word);

    node *currentNode = table[h];
    if (currentNode == NULL) {
        table[h] = newNode;
        return true;
    }

    node *prevNode = NULL;
    while (currentNode != NULL)
    {
        int cmpResult = strcmp(currentNode->word, newNode->word);
        if (cmpResult == 0) {
            free(newNode);
            return true;
        }

        if (cmpResult > 0) {
            newNode->next = currentNode;

            if (prevNode != NULL) {

                prevNode->next = newNode;
                return true;
            }

            table[h] = newNode;
            return true;
        }

        if (currentNode->next == NULL) {
            currentNode->next = newNode;
            return true;
        }

        prevNode = currentNode;
        currentNode = currentNode->next;
    }


    printf("--------------- returning false should not exist -------------------");
    free(newNode);
    return false;
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
            char *lWord = strToLower(word);
            if (lWord == NULL) {
                unload();
                fclose(f);
                return false;
            }
            if (!addwordtodict(lWord)) {
                fclose(f);
                free(lWord);
                unload();
                return false;
            }else {
                free(lWord);
            }
        } else {
            word[chIndex++] = ch;
        }
    }

    fclose(f);

    return true;
}

// Returns number of words in dictionary if loaded, else 0 if not yet loaded
unsigned int size(void)
{
    int count = 0;
    for (int i = 0; i < N; i++) {
        node *currentNode = table[i];
        while (currentNode != NULL)
        {
            count++;
            currentNode = currentNode->next;
        }
    }

    return count;
}

// Unloads dictionary from memory, returning true if successful, else false
bool unload(void)
{
    for (int i = 0; i < N; i++) {
        node *currentNode = table[i];
        table[i] = NULL;
        while (currentNode != NULL)
        {
            node *tmpNode = currentNode;
            currentNode = currentNode->next;
            free(tmpNode);
        }

    }

    return true;
}

void printDictWords()
{
    for (int i = 0; i < N; i++) {
        node *currentNode = table[i];
        if (currentNode == NULL) {
            printf("skipping %d\n", i);
            continue;
        }

        printf("word:");
        while (currentNode != NULL) {
            printf(" %s,", currentNode->word);
            currentNode = currentNode->next;
        }
        printf("\n");
    }
}


// int main(int argc, char *argv[])
// {
//     load(argv[1]);
//     printf("==================");
//     printDictWords();

//     char s[] = "CAT";
//     printf("%s in in dict: %d\n", s, check(s));
//     printf("size: %d\n", size());
//     printf("unloaded: %d\n", unload());
//     printf("size: %d\n", size());
// }
