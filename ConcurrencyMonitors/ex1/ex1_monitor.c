
#include "ex1_monitor.h"
#define MAX_CAPACITY 100
#define FALSE 0
#define TRUE 1

pthread_cond_t serverWait ;
pthread_mutex_t lock ;
pthread_cond_t clientWait[MAX_CAPACITY];

static pthread_once_t is_initialized = PTHREAD_ONCE_INIT;

// Queue implemantation with helper fucntions

typedef struct Queue{

    int clients[MAX_CAPACITY];
    int front ;
    int rear ;
    int count ; 
} Queue;

static void queueInit(Queue *q){

    q->count=0;
    q->front=0;
    q->rear=0;

}
static int isEmpty( Queue *q){

    if (q->count == 0 ){
        return TRUE;
    }
    else return FALSE;
}

static int isFull( Queue *q){

    if (q->count == MAX_CAPACITY ){
        return TRUE;
    }
    else return FALSE;
}


static void enQueue( Queue *q , int cid){

    if (isFull( q ) ){
        printf ("The restauant is currently full, customer %d cannot enter \n", cid);

    }else {

        q->clients[q->rear]= cid;
        q->rear = (q->rear +1 )% MAX_CAPACITY ;
        q->count++;
    }



}

static int deQueue( Queue *q ){

    int client;

    if (isEmpty( q ) ){
        printf ("The restauant is currently empty\n");
        return -1;
    }else {

        client = q->clients[q->front];
        q->front=(q->front +1)%MAX_CAPACITY;
        q->count --;

       
    }

    return client;

}





static Queue *q;
static int nextToServe=0; 
extern void init(){



    pthread_mutex_init (&lock , NULL);
    pthread_cond_init( &serverWait, NULL);

    for ( int i=0 ; i < MAX_CAPACITY ; i++){
        pthread_cond_init(&clientWait[i],NULL);
    }
    q = (Queue*)malloc(sizeof(Queue)); 
    queueInit(q);
}

void enter ( int cid){

    pthread_once(&is_initialized, init);

    pthread_mutex_lock(&lock);

    if (!isFull(q)){

        enQueue(q,cid);

        pthread_cond_signal(&serverWait);
    

        while( cid !=nextToServe){

            printf("Customer %d is waiting for their turn \n", cid );
            pthread_cond_wait(&clientWait[cid], &lock);

        }

        

    } else {

        printf("Customer %d cannot enter - restaurant is full\n", cid);
    }



    pthread_mutex_unlock(&lock);


}

int service (){

    pthread_once(&is_initialized, init);
    pthread_mutex_lock(&lock);

  while (isEmpty(q)){

    printf("Employee currently is waiting for customers \n");
    pthread_cond_wait(&serverWait,&lock);

  }
    int gettingServed = deQueue(q);

    nextToServe= gettingServed;

    pthread_cond_signal(&clientWait[gettingServed]);

    pthread_mutex_unlock(&lock);

 return gettingServed;
}

