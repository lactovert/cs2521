// words2.c ... Build a hashtable of words 
// Written by John Shepherd, August 2008


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>
#include "Item.h"
#include "HashTable.h"

#define WORD_FILE "/usr/share/dict/words"
#define MAX_WORD_SIZE 100 


// Get words, store in hashTable, print hashtable stats
int main(int argc, char **argv){
    char *wordsFile; // name of file containing words
    FILE *wordf;     // file handle for file containing words
    HashTable hashTable; 
    int size = 100;

    // access the word file
    if (argc > 1){
	    wordsFile = argv[1];
    }else{
	    wordsFile = WORD_FILE;
    }
    if(argc > 2){
        size = atoi(argv[2]);
    }

    if(strcmp(wordsFile,"-") == 0){
            wordf = stdin;
    } else {
        wordf = fopen(wordsFile,"r");
        if (wordf == NULL) {
            fprintf(stderr,"Can't open %s\n",wordsFile);
            exit(1);
        }
    }
 
    hashTable = newHashTable(size);
    printf("Reading words from %s\n",wordsFile);   
    int numWords = 0;
    char word[MAX_WORD_SIZE];

    while (fgets(word,MAX_WORD_SIZE,wordf) != NULL) {
        int n = strlen(word);
	word[n-1] = '\0'; // strip off \n
	// filter out empty words
	if (strcmp(word,"") != 0) {
       	    HashTableInsert(hashTable,strdup(word));
            numWords++;
            assert(HashTableSearch(hashTable,word) != NULL);
        }        
    }
    //Warning: We are assuming these strings do not occur
    //in the input
    assert(HashTableSearch(hashTable,"!aaaaaa!") == 0) ;
    assert(HashTableSearch(hashTable,"!xxxxxx!") == 0) ;
    assert(HashTableSearch(hashTable,"!yyyyyy!") == 0) ;
    assert(HashTableSearch(hashTable,"!zzzzzz!") == 0) ; 
    

    printf("Read in %d words\n",numWords);
    // print some properties
    HashTableStats(hashTable);
    dropHashTable(hashTable);
    fclose(wordf);
    return 0;
}

