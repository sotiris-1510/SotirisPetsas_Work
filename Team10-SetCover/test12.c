#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <string.h>


int * randomCoverage( int* U , int** poi , int* sizes, int n, int m , int c , int k ){
    

    int i ,j ;
    int count= 0;
    int totalCovered = 0;
    int * coverage= malloc (k* sizeof(int)  );
    int * covered = calloc ( n, sizeof(int));

    for (int i = 0; i < k; i++) coverage[i] = -1;


    while ( count < k && totalCovered < n){

        int random= rand() % m ;
        int new=0;

        
        for (  j = 0 ;j < sizes[random] ; j++){

            for ( i =0 ; i< n ; i++){

                if( U[i]== poi[random][j] && !covered[i]){
                    new ++;

                }
            }
        }

        if ( !new )continue;

        coverage[count++]= random;

        for (  j = 0 ;j < sizes[random] ; j++){

            for ( i =0 ; i< n ; i++){

                if( U[i]== poi[random][j] && !covered[i]){
                    totalCovered++;
                    covered[i]=1;


                }
            }
        }


    }

    free( covered );

    
   if( totalCovered < n ){
   

    free( coverage);
    return NULL;

   }else{

    return coverage;
   } 

  
   return coverage;
}



int * maxCoverage( int* U , int** poi , int* sizes, int n, int m , int c , int k ){

  

    int i ,j ;
    int count= 0;
    int totalCovered = 0;
    int * coverage= malloc (k* sizeof(int)  );
    int * covered = calloc ( n, sizeof(int));

    for (int i = 0; i < k; i++) coverage[i] = -1;


    while ( count < k && totalCovered < n){
        
        int best=-1;
        int mostPoints = -1 ;

        for ( i =0 ; i < m ; i++){

            int newPoints=0;

            for ( j=0 ; j < sizes[i] ; j++){

                for ( int u=0 ; u< n ; u++){

                    if(U[u]== poi[i][j] && !covered[u]){

                        newPoints++;
                    }
                }
            }

            if ( newPoints > mostPoints){
                mostPoints= newPoints;
                best = i ;
            }
        }

        if ( best == -1 )break;

        
        coverage[count++]= best;

        for(  j = 0 ; j < sizes[best] ; j++){

            for ( i =0 ; i< n ; i++){

                if( U[i]== poi[best][j] && !covered[i]){
                    totalCovered++;
                    covered[i]=1;


                }
            }
        }


    }

    free( covered );


   if( totalCovered < n ){
   

    free( coverage);
    return NULL;

   }else{

    return coverage;
   } 


    
    return coverage;
   
   
}



int main (int argc , char * argv[]){

    int n ,m ,c , k;
    int *U;
    int ** poi;
    int* size;
    FILE * fp;
    
    

    int flag=0;

    if ( flag==0 ){

        fp = fopen("sets.dat", "r");

        if (fp == NULL) {

            perror("Error opening file");  
            return 0;

        }

        
        fscanf(fp ,"%d %d %d %d",&n,&m,&c,&k );

        U= malloc(n *sizeof(int));

        for(int i=0 ; i< n ; i++){

            fscanf(fp , "%d" , &U[i]);
        }

        poi= malloc(m*sizeof(int *));
        size= malloc ( m *sizeof(int)); // the size of points each router covers


        char line [1024];
        fgets (line , sizeof(line), fp);

        for (int i=0 ; i<m ; i++){

            poi[i]= malloc(c * sizeof(int));
            size[i]=0;

            fgets (line , sizeof(line), fp);

            char * tok = strtok( line ," \n");

            while (tok != NULL){

                poi[i][size[i]]=atoi(tok);
                size[i]++;
                tok = strtok( NULL ," \n");
            }

            
        }


    }else if (flag ==1){

        //for experimental use


    }else {

        printf("The mode given is invalid , program terminated !");
        return 0;
    }

    // --- Print to verify ---
    printf("U: ");
    for (int i = 0; i < n; i++) printf("%d ", U[i]);
    printf("\n");

    for (int i = 0; i < m; i++) {
        printf("Router %d: ", i + 1);
        for (int j = 0; j < size[i]; j++)
            printf("%d ", poi[i][j]);
        printf("\n");
    }

  
    srand(time(NULL));

    clock_t start= clock();
    int* C0=randomCoverage( U , poi , size , n , m ,c ,k);
    clock_t end= clock();
    double time = ((double) (end - start )/ CLOCKS_PER_SEC)*1000;
    printf("Time: %.2f ms\n", time);



    start= clock();
    int* C1= maxCoverage( U , poi , size , n , m ,c ,k);
    end= clock();
    time = ((double) (end - start )/ CLOCKS_PER_SEC)*1000;
    printf("Time: %.2f ms\n", time);


    if(C0 == NULL){

        printf("The random coverage was unsuccesful\n");
    }else{


        printf("C0: ");
        for (int i = 0; i < k && C0[i] != -1; i++) printf("%d ", C0[i]);
        printf("\n");
    }

    if(C1 == NULL){

        printf("The coverage based on max covered was unsuccesful\n");
    }else{

        printf("C1: ");
        for (int i = 0; i < k  && C1[i] != -1; i++) printf("%d ", C1[i]);
        printf("\n");

    }
    
    free(U);
    for (int i = 0; i < m; i++) free(poi[i]);
    free(poi);
    free(size);
    fclose(fp);




 return 0;
}
