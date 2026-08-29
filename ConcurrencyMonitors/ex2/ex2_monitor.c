#include "ex2_monitor.h"


pthread_mutex_t lock;
pthread_cond_t waitingFill;
pthread_cond_t waitingEat ; 
int platesReady=0 ;

int activeEaters=0;
int activeFillers=0;
int totalPeople=0;
int remainingThreads=0;




static pthread_once_t is_initialized = PTHREAD_ONCE_INIT;

extern void init(){


    pthread_mutex_init (&lock , NULL);
    pthread_cond_init( &waitingFill, NULL);
    pthread_cond_init(&waitingEat, NULL);

   
}

void setTotalPeople(int total){

    remainingThreads=total;
}

void eat(int id){
    pthread_once(&is_initialized, init);

    pthread_mutex_lock(&lock);

    activeEaters++;

    while( platesReady == 0 ){

        if(activeFillers==0 && remainingThreads<=activeEaters ){

            printf("Person %d cannot eat - no filler left , give up \n", id);
            activeEaters--;
            remainingThreads--;

            pthread_cond_broadcast(&waitingFill);
            pthread_cond_broadcast(&waitingEat);
            pthread_mutex_unlock(&lock);
            return;
        }

        printf("Currently there aren't enough plates ready for person #%d to eat \n",id);

        pthread_cond_wait (&waitingEat,&lock);

    }

    platesReady--;

    pthread_cond_signal(&waitingFill);
    activeEaters--;
    remainingThreads--;
  

    pthread_mutex_unlock(&lock);

}

void work(int id){
    pthread_once(&is_initialized, init);

    pthread_mutex_lock(&lock);

    activeFillers++;


    while( platesReady == 5 ){

        if(activeEaters==0 && remainingThreads<=activeFillers ){

            printf("Person #%d cannot prepare - no eaters left , give up \n", id);
            activeFillers--;
            remainingThreads--;
            pthread_cond_broadcast(&waitingEat);
            pthread_cond_broadcast(&waitingFill);
            pthread_mutex_unlock(&lock);
            return;
        }


        printf("Currently all the plates are ready and person #%d can not prepare another plate   \n",id);

        pthread_cond_wait (&waitingFill,&lock);

    }

    platesReady++;

    pthread_cond_signal(&waitingEat);

    activeFillers--;
    remainingThreads--;


    pthread_mutex_unlock(&lock);



}