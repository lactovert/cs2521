// A binary tree interface


#define NO_REBALANCE 0     //no rebalancing strategy
#define REBALANCE_1 1      //rebalance after every insertion
#define REBALANCE_100 2    //rebalance after every 100 insertions
#define REBALANCE_1000 3   //rebalanct after every 1000 insertions
#define RANDOMISED 4       //used randomInsertion
#define SPLAY 5            // use splay insertion (and search)


typedef struct treeImp * Tree;

Tree TREEinit(int balanceStrategy);
void TREEinsert(Tree t, Item i);
int TREEcount(Tree t);
int TREEsearch(Tree t, Key k);
int TREEheight(Tree t);
void TREEdestroy(Tree t);
void TREEdisplay(Tree t);
void TREEshowStats(Tree t);

