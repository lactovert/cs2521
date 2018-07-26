// words.c ... Build a tree of words from /usr/dict/words
// Written by John Shepherd, August 2008
// Modified by Angela Finlayson, January 2009

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>
#include "Item.h"
#include "Tree.h"

#define WORD_FILE "/usr/share/dict/words"
#define MAX_WORD_SIZE 100 

int getAllWords(FILE *, Tree t);


// Get words, store in tree, print tree stats
int main(int argc, char **argv){
    char *wordsFile =""; // name of file containing words
    FILE *wordf;         // file handle for file containing words
    Tree wordTree; 
    int strategy = NO_REBALANCE;
    // access the word file
    if (argc > 1){
	    wordsFile = argv[1];
      
    }else{
	    wordsFile = WORD_FILE;
    }
    if(argc > 2){
        strategy = atoi(argv[2]);
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
    wordTree = TREEinit(strategy);
    printf("Reading words from %s\n",wordsFile);    
    // build tree containing all words
    int numWords = getAllWords(wordf, wordTree);
    printf("Read in %d words\n",numWords);
    TREEshowStats(wordTree);
    //You may wish to comment this out for large trees
    TREEdisplay(wordTree);
 
    TREEdestroy(wordTree);
    fclose(wordf);
    return 0;
}


// Read all words from file into tree 
int getAllWords(FILE *f, Tree wordTree){
    int numWords = 0;
    char word[MAX_WORD_SIZE];

    while (fgets(word,MAX_WORD_SIZE,f) != NULL) {
        int n = strlen(word);
	    word[n-1] = '\0'; // strip off \n
	    // filter out empty words
	    if (strcmp(word,"") != 0) {
       	    TREEinsert(wordTree,strdup(word));  
            numWords++;
            assert(TREEsearch(wordTree,word) == 1);
        }       
    }
    
    //Warning: We are assuming these strings do not occur
    //in the input
    assert(TREEsearch(wordTree,"!aaaaaa!") == 0) ;
    assert(TREEsearch(wordTree,"!xxxxxx!") == 0) ;
    assert(TREEsearch(wordTree,"!yyyyyy!") == 0) ;
    assert(TREEsearch(wordTree,"!zzzzzz!") == 0) ; 
    return numWords;  
}
