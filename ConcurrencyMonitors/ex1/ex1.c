
#include "ex1_monitor.c"
#include <unistd.h>

int numOfClients;
int clientsServed=0;

void *clientDo (void *cid){

    int *client = (int*) cid;

        
        enter(*client);
       
        printf("Customer %d is now being served\n", *client);
    
}



void *serverDo( ){
    int cid;

    while(1){

        cid = service();
        printf("Employee is serving customer %d \n", cid);
        sleep (2);

        clientsServed++;

        if(clientsServed == numOfClients){
           
            printf("All clients have been served \n");
            break;
        }

    }
}




int main(int argc , char *argv[]){

   

    numOfClients = atoi(argv[1]);

    while (numOfClients < 0 ){
        printf("Not enough clients given , give another number \n");

        scanf("%d",&numOfClients);

    }
    
    int i,cid[numOfClients];
    pthread_t clients[numOfClients], server;

    
    
    pthread_create(&server, NULL , &serverDo ,NULL);


    for (i=0 ; i< numOfClients ; i++ ){   

        sleep(1);

        cid[i]=i;

        pthread_create(&clients[i] , NULL , clientDo , &cid[i]);
        
    }


    for (i=0 ; i< numOfClients ; i++ ){

        pthread_join(clients[i], NULL);
    }
    pthread_join(server, NULL);
  

    return 0;
}