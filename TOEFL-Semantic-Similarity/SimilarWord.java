package HW4_Team50;

import java.io.BufferedWriter;
import java.io.FileWriter;
import java.io.IOException;
import java.util.ArrayList;
import java.util.HashMap;
import java.util.List;

/**
 * Implements {@link SimilarInterface} and provides functionality
 * to find the most similar word using semantic descriptors and cosine similarity.
 */

public class SimilarWord implements SimilarInterface{


    private HashMap<String, HashMap<String, Integer>> semanticDisc;
    
    private HashMap< String , Double > normMap;

    /**
     * Constructs a SimilarWord instance with a given semantic descriptors map.
     *
     * @param map A map representing semantic descriptors.
     */

    public SimilarWord(HashMap<String, HashMap<String, Integer>> map) {

        semanticDisc = map;
        normMap = new HashMap<>();
    }

     /**
     * Finds the most similar word to the given word among the given choices using cosine similarity.
     *
     * @param word The word to compare.
     * @param choices The array of possible choices.
     * @return The most similar word.
     */

    public String mostSimilarWord(String word, String[] choices) {
        word = word.toLowerCase();  

        double maxSimilarity = -1.0;
        String mostSimilar = null; 
    
        for (String choice : choices) {
            String choiceLower = choice.toLowerCase();
            double sim = cosineSimilarity(word, choiceLower);
            if (sim > maxSimilarity) {
                maxSimilarity = sim;
                mostSimilar = choice;
            }
        }

        if (maxSimilarity == -1.0) {
            mostSimilar = "None of the choices are similar ";
        }

         try {
            BufferedWriter writer = new BufferedWriter(new FileWriter ("HW4_Team50/accuracy.txt"));
           
            writer.write(String.format(mostSimilar+"\n"));
            writer.close();
            
        } catch (IOException e) {
            System.out.println("Error while writing to accuracy.txt " + e.getMessage());
        } 
    
        return mostSimilar;
    }

 
    /**
     * Calculates the cosine similarity between two words based on their semantic vectors.
     *
     * @param w1 The first word.
     * @param w2 The second word.
     * @return The cosine similarity score, or -1.0 if comparison cannot be made.
     */


    private double cosineSimilarity(String w1, String w2) {
        if (!semanticDisc.containsKey(w1) || !semanticDisc.containsKey(w2)) return -1.0;

        double norm1 = norm(w1);
        double norm2 = norm(w2);
        if (norm1 == 0 || norm2 == 0) return -1.0;

        double dotProduct = 0.0;
        for (String key : semanticDisc.get(w1).keySet()) {
            if (semanticDisc.get(w2).containsKey(key)) {
                dotProduct += semanticDisc.get(w1).get(key) * semanticDisc.get(w2).get(key);
            }
        }

        

        double denominator = norm1*norm2;

        return dotProduct / denominator;
    }

    /**
     * Calculates and caches the norm (length) of the vector for a given word.
     *
     * @param word The word to compute the norm for.
     * @return The norm value.
     */


    private double norm( String word){


        if(normMap.containsKey(word)){

            return normMap.get(word);


        }else{


         int sumOfSquares =0 ; 

         if (!semanticDisc.containsKey(word)) {
            return 0.0;
        }

        for (String key : semanticDisc.get( word ).keySet()){


            sumOfSquares += Math.pow (semanticDisc.get(word).get(key),2);


         }

         normMap.put(word , Math.sqrt(sumOfSquares));

         return Math.sqrt(sumOfSquares);
      }

    }
    
}
