package HW4_Team50;

/**
 * An interface that defines a method for finding the most similar word
 * from a list of candidate words.
 */

public interface SimilarInterface {

      /**
     * Finds the word from the choices array that is most similar to the given word.
     *
     * @param word The target word.
     * @param choices The array of candidate words.
     * @return The most similar word.
     */

     public String mostSimilarWord(String word, String[] choices);
    
}
