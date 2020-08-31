// Implements a dictionary's functionality

#include <stdbool.h>
#include <string.h>
#include <strings.h>
#include "dictionary.h"
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
bool insert(uint32_t,char*);
#define get16bits(d) ((((uint32_t)(((const uint8_t *)(d))[1])) << 8)\
                       +(uint32_t)(((const uint8_t *)(d))[0]) )

// Represents a node in a hash table
uint64_t count = 0;

typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
}
node;

// Number of buckets in hash table
const unsigned int N = 20000;

// Hash table
node *table[N];

// Returns true if word is in dictionary else false
bool check(const char *word)
{
    char copy[46];
    strcpy(copy,word);
    uint32_t idx = hash(copy);


    node* temp = table[idx];
    while(temp != NULL)
    {
        if (strcasecmp(temp->word,word) == 0)
        {
            return true;
        }
        temp = temp->next;
    }
    return false;
}

// Hashes word to a number
unsigned int hash(const char *word)
{
    // hash from "http://www.azillionmonkeys.com/qed/hash.html" >> I wanted a quick hash function

    uint32_t len = strlen(word);
    uint32_t hash = len, tmp;
    int rem;

    if (len <= 0 || word == NULL) return 0;

    rem = len & 3;
    len >>= 2;

    for( ; len > 0 ; len --)
    {
        hash += get16bits (word);
        tmp  = (get16bits (word+2) << 11) ^ hash;
        hash = (hash << 16) ^ tmp;
        word += 2*sizeof (uint16_t);
        hash += hash >> 11;
    }

    switch (rem) {
        case 3: hash += get16bits (word);
                hash ^= hash << 16;
                hash ^= ((signed char)word[sizeof (uint16_t)]) << 18;
                hash += hash >> 11;
                break;
        case 2: hash += get16bits (word);
                hash ^= hash << 11;
                hash += hash >> 17;
                break;
        case 1: hash += (signed char)*word;
                hash ^= hash << 10;
                hash += hash >> 1;
    }

    hash ^= hash << 3;
    hash += hash >> 5;
    hash ^= hash << 4;
    hash += hash >> 17;
    hash ^= hash << 25;
    hash += hash >> 6;

    return hash % N;

}

// Loads dictionary into memory, returning true if successful else false
bool load(const char *dictionary)
{
    uint32_t idx;
    char line[46];
    FILE* f = fopen(dictionary, "r");

    if(f == NULL)
    {
        return false;
    }

    while(fscanf(f,"%s",line) != -1)
    {
        char copy[46];
        strcpy(copy,line);
        idx = hash(copy);
        if(!insert(idx,line))
        {
            return false;
        }
        else
        {
            count++;
        }


    }
    return true;


}

// Returns number of words in dictionary if loaded else 0 if not yet loaded
unsigned int size(void)
{
    return count;
}

// Unloads dictionary from memory, returning true if successful else false
bool unload(void)
{
    for(int i = 0 ; i < N ; i++)
    {
        node* temp = table[i];
        node* tmp = temp;

        while(tmp!=NULL)
        {
            tmp = tmp->next;
            free(temp);
            temp = tmp;
        }
    }
    return true;
}

bool insert(uint32_t idx, char* word)
{
    node* temp = table[idx];

    node* tmp = malloc(sizeof(node));
    if(tmp == NULL)
    {
        return false;
    }

    strcpy(tmp->word,word);


    if (temp == NULL)
    {
        table[idx] = tmp;
    }
    else
    {
        tmp->next = table[idx];
        table[idx] = tmp;
    }
    return true;
}
