package HW4_Team50;

import java.util.ArrayList;
import java.util.HashMap;
import java.util.List;

/**
 * A class for building semantic descriptors from a corpus of sentences,
 * representing word co-occurrence information.
 */

public class SemanticDescriptors {
    
    private HashMap< String , HashMap < String , Integer > > semanticDisc;
    private List<List<String>> sentencesList;

    /**
     * Constructs a SemanticDescriptors instance with a given list of sentences.
     *
     * @param list The list of sentences, where each sentence is a list of words.
     */

    public SemanticDescriptors (List<List<String>> list ){


         sentencesList = list ;
        
    }


    /**
     * Builds the semantic descriptors based on the co-occurrence of words in sentences.
     *
     * @return A map representing the semantic descriptors.
     */


    public HashMap<String, HashMap<String, Integer>> buildSemanticDescriptors () {


         semanticDisc = new HashMap <> ();

        for (int i = 0 ; i <sentencesList.size() ; i++){

            List < String > sentence = sentencesList.get(i);


            for( int j=0 ; j< sentence.size() ; j++){


                if( !semanticDisc.containsKey(sentence.get(j))){

                   semanticDisc.put( sentence.get(j) , countWords( sentence.get(j) , sentencesList ) );

             }



            }

        }


     return semanticDisc;
    }


    /**
     * Helper method that counts co-occurring words for a given word across the sentence list.
     *
     * @param st The target word.
     * @param sentencesList The list of sentences.
     * @return A map where keys are co-occurring words and values are their counts.
     */


    private HashMap<String , Integer > countWords( String st, List<List<String>> sentencesList ){


        HashMap <String ,Integer > wordCounter = new HashMap<> ();

         for (int i = 0 ; i <sentencesList.size() ; i++){

            List < String > sentence = sentencesList.get(i);

         if( sentence .contains(st)){


            for( int j=0 ; j< sentence.size() ; j++){

             if(sentence.get(j) !=st ) {
                    if(wordCounter.containsKey(sentence.get(j))){

                        wordCounter.put ( sentence.get(j) , wordCounter.get( sentence.get(j) ) + 1);
                    }
                    else{
                        wordCounter.put(sentence.get(j),1);


                    }
                    


                }

             }

            }


      }


     return wordCounter;


    }
    
}
