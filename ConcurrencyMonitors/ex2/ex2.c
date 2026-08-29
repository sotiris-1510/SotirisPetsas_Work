#include "ex2_monitor.c"
#include <unistd.h>

int numOfPeople;



void *eater(void * pid){

    int *id =(int *) pid;
    printf("Person #%d will try to eat\n", *id);
    eat(*id);
   
    printf("Person #%d has finished its job trying to eat \n ", *id);
    return NULL;
}


void *filler(void *pid){

    int *id =(int *) pid;
    

    printf("Person #%d wil prepare a dish\n ", *id);
    work(*id); 
    printf("Person #%d has finished its job trying to prepare a dish\n", *id);
    return NULL;

}

int main(int argc , char *argv[]){

   

    numOfPeople = atoi(argv[1]);

    while (numOfPeople < 0 ){
        printf("Not enough people given , give another number \n");

        scanf("%d",&numOfPeople);

    }

    setTotalPeople(numOfPeople);


    int i,pid[numOfPeople];
    pthread_t people[numOfPeople] ;

    

    for (i=0 ; i< numOfPeople ; i++ ){

        pid[i]=i;

        double coin = (double)random()/RAND_MAX;

        if (coin <=0.10){

            
            pthread_create(&people[i] , NULL , eater , &pid[i]);
            

        }else{
           
            pthread_create(&people[i] , NULL , filler , &pid[i]);
           
        }

    }

    
    for (i=0 ; i< numOfPeople ; i++ ){

        pthread_join(people[i],NULL);
    }

    printf("All people have completed their tasks\n");

    return 0;
}





    