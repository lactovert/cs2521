// Queue.h 
typedef struct queueImp *Queue; 
//Function Prototypes 
Queue createQueue( void ); 
void destroyQueue( Queue queue ); 
Item getQueue( Queue queue); 
void putQueue( Queue queue, Item data); 
int queueSize( Queue queue); 


