


/**
 * 
 * @author Sotiris Petsas UC1367983
 * @bug No known bugs.
 * @date 10-10-2025
 * 
 * @file patternMatching.c
 * @brief Program to search for specific DNA patterns in a larger sequence using either
 * brute-force or Karp-Rabin algorithms to match the strings .
 *
 *  This program reads a large DNA sequence and a smaller pattern from files
 *  then counts how many times the pattern is found in the sequence.
 * 
 *  It uses two algorithms to calculate the number of matches found:
 *     -Brute Force algorithm (-bf)
 *     -Karp-Rabin algorithm (-kr)
 *  
 *  
 */


#include<stdio.h>
#include<string.h>
#include<math.h>
#include<limits.h>


/// Maximum length allowed for a DNA sequence or pattern
#define MAX_DNA_LENGTH 512000


/**
 * @brief Performs brute-force search for a pattern in a DNA sequence.
 *
 * @param dnaSequence The DNA sequence to be searched.
 * @param pattern The pattern to search for.
 * @param timesFound Pointer to an integer counter to store the number of occurrences found.
 *
 * This function compares each possible substring of the DNA sequence
 * with the pattern directly, character by character.
 */


void bruteForce(char *DNA , char *pattern , int *timesFound);


/**
 * @brief Performs Karp-Rabin pattern matching on the DNA sequence.
 *
 * @param dnaSequence The DNA sequence to be searched.
 * @param pattern The pattern to search for.
 * @param timesFound Pointer to an integer counter to store the number of occurrences found.
 *
 * The Karp-Rabin algorithm uses hashes to compare
 * substrings without checking every character directly.
 */

void karpRabin(char *dnaSequence , char *pattern , int *timesFound);


/**
 * @brief Reads the contents of a file into a string .
 *
 * @param nameFile Name of the file to be read.
 * @param content Pointer to where the content of the file will be stored.
 * @return int Returns 1 if successful, 0 otherwise.
 *
 * The function reads the entire file character by character
 * and stores it .
 */

int readFromFile( char *nameFile, char* content );


/**
 * @brief Computes the hash value for a given substring.
 *
 * @param subString The substring to hash.
 * @param length The length of the substring.
 * @return int The computed hash value.
 *
 * The hash is computed using a simple hash formula
 * with base 2 and modulo INT_MAX.
 */

int hash(char *subString, int length);



/**
 * @brief Recomputes the hash after sliding the window by one character.
 *
 * @param lm The leftmost character that is being removed.
 * @param prevHash The hash value of the previous substring.
 * @param rm The new rightmost character being added.
 * @param length The length of the pattern/window.
 * @return int The new hash value after rehashing.
 * 
 * 
 * The new hash is computed by removing the hash 
 * value of the leftmost character , multiplying the rest by 2
 * so they "move up" one position and adding the hash 
 * value of the new char.
 */
int rehash( char lm , int prevHash , char rm, int length);




/**
 * @brief Main entry point of the program.
 *
 * @param argc The number of command-line arguments.
 * @param argv The array of command-line argument strings.
 * @return int Returns 0 when terminated
 *
 * Expected command-line usage:
 *   - argv[1] = algorithm flag (-bf or -kr)
 *   - argv[2] = path to DNA sequence file
 *   - argv[3] = path to pattern file
 */



int main( int argc, char *argv[] ){

    char dnaSequence[MAX_DNA_LENGTH+1] ;
    char pattern[MAX_DNA_LENGTH+1] ;

    int timesFound=0;

    // Make sure the number of arguments given is correct.


    if( argc!=4){

        printf("ERROR : wrong amount of arguments given , program terminated \n");

        return 0 ;
    }

    // Make sure the path for the file of the Dna sequence is valid.

    char *alg=argv[1];
    if( readFromFile( argv[2] , dnaSequence) == 0 ){


        printf("ERROR : complications while reading the DNA sequence, program terminated\n");
        return 0;
    }

    

    // Make sure the path for the file of the pattern is valid.


    if( readFromFile( argv[3], pattern ) == 0 ){

        printf("ERROR : complications while reading the pattern, program terminated\n");
        return 0;


    }

    // Checks if the pattern is small enough where a comparison can be made with a substring of the sequence.
    if( strlen(pattern) > strlen(dnaSequence) ){

        printf("ERROR : the string of the pattern is larger than the string of the Sequence, program terminated \n");
        return 0;
    }

    


   // Decide which algorithm to use based on the input of the user, if its correct.

    if( strcmp(alg , "-bf")==0 ){

        bruteForce( dnaSequence , pattern , &timesFound );


    }else if( strcmp(alg, "-kr")==0 ){

        karpRabin( dnaSequence , pattern , &timesFound );


    }else{

        printf("ERROR : Wrong algorithm given , program terminated \n");
        return 0;
    }



    // Prints the amount of times the pattern is found in the given Sequence.

    printf("The DNA pattern is found %d times in the Sequence given\n", timesFound);

    

    return 0;
}
    
 void bruteForce(char *dnaSequence , char *pattern , int *timesFound){

    int i,j;


    // Iterates through the Sequence and searches for consecutively matching characters to the pattern , if it finds as many characters
    // in a row as the lentgh of the pattern then a matching substring is found.

    for(i=0 ; i<=strlen(dnaSequence)-strlen(pattern); i++){

        j=0;

        while( (dnaSequence [i+j] )== (pattern [j]) && dnaSequence[i+j]!='\0' && pattern[j]!='\0'){
            j++;
        }

        


        if( j== strlen(pattern)){

            (*timesFound)++;
        }

        

    }


        
    }



 void karpRabin(char *DNA , char *pattern , int *timesFound){

    int i ;

    int hashPattern = hash( pattern, strlen(pattern) );


    int hashSubstring=0;


    // Iterates through the string  and calculates the hash value of each substring that has 
    // length the same as the pattern, if its the first substring calculate manually its hash
    // with the Karp-Rabin algorithm else use the rehash algorithm to calculate the hash value


    for(i=0 ; i<= strlen(DNA) - strlen(pattern); i++ ){

        switch( i) {

            case 0 : hashSubstring= hash (DNA +i , strlen(pattern)  );
                     break;


            default : hashSubstring = rehash( DNA[i-1], hashSubstring , DNA[i + strlen(pattern) -1 ], strlen(pattern));
        }

        if( hashSubstring == hashPattern){

            (*timesFound)++;
        }


    }
     
 }

 


 int readFromFile( char *nameFile, char  *string ){

    
    long i=0;
    char c;


    FILE *fp = fopen( nameFile , "r" );

    // Makes sure that the path is valid

    if(fp== NULL  ){

        printf("ERROR : unable to open the stream to %s\n", nameFile);
        return 0;
    }



    while( (c=fgetc(fp )) != EOF){

        // Makes sure that the stirng isnt larger than the suggested size

        if( i >= MAX_DNA_LENGTH){

           printf("ERROR : the text sequence it too large \n");
           fclose(fp);

           return 0;
        }

        // Checks for illegal charachters in string 

        if( c!= 'a' && c!='c' &&  c!='g' && c!='t' ){

            printf("ERROR : the text contains illegal character \n");
            fclose(fp);

            return 0;
        }

        string[i]=c;


        i++;
      
    }


   
    

    fclose(fp);
    return 1;

    } 


    int hash( char *substring, int length){

        int i,pow=1;
        int hashValue=0; 


        // Calculates the hash value of the substring by multiplying the integer
        // value of a char* 2^( length - position of the char in the substring)
        // and then uses modulo to prevent overflow


        for( i=length-1 ; i>=0; i--){

           hashValue += (substring[i] * pow )% INT_MAX ;

           pow=pow*2;


        }

        

        return hashValue;
    }


    int rehash( char lm , int prevHash , char rm, int length){


        int powlm=1,i;

        // Calculates the 2^length -1 so we can accurately remove 
        // the leftmost character of the substring from the hash 

        for(i=1 ; i<length; i++){

            powlm*=2;
        }

        // Clculates rehash based on the give algorithm

        int rehashValue= ((prevHash- lm*powlm )*2 + rm);
        

        // Uses modulo to prevent overflow
        rehashValue= rehashValue % INT_MAX;


        return rehashValue;
    }


