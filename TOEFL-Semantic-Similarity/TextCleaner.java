
package HW4_Team50;

import java.util.*;

/**
 * A utility class for cleaning and tokenizing text by removing stopwords
 * and unwanted characters.
 */

public class TextCleaner {

    private Set<String> stopwords;

    /**
     * Constructs a TextCleaner with a minimal list of English stopwords.
     */

    public TextCleaner() {
        
        stopwords = new HashSet<>(Arrays.asList(
            "a", "an", "the",
    

    "i", "you", "he", "she", "it", "we", "they", 
    "my", "your", "his", "its", "our", "their",
    

    "in", "on", "at", "by", "for", "with", "about", 
    "from", "to", "of",
  
    "and", "but", "or", "so", "if", "because",
    

    "be", "is", "am", "are", "was", "were", 
    "have", "has", "had", "do", "does", "did",
    
    "very", "not", "no", "yes", "more", "most", "some" 
        ));
    }

    /**
     * Cleans and tokenizes a sentence, removing stopwords and non-alphabetical characters.
     *
     * @param sentence The input sentence.
     * @return A list of cleaned words from the sentence.
     */

    public List<String> cleanAndTokenize(String sentence) {
        List<String> result = new ArrayList<>();

        String cleaned = sentence.toLowerCase().replaceAll("[^a-z ]", " ");
        String[] words = cleaned.split("\s+");

        for (String word : words) {
            if (!stopwords.contains(word) && word.length() > 1) {
                result.add(word);
            }
        }

        return result;
    }

    /**
     * Cleans a corpus of sentences without destroying sentence structure.
     *
     * @param rawSentences The list of sentences (each as a list of words).
     * @return A cleaned version of the corpus.
     */

    public List<List<String>> cleanCorpus(List<List<String>> rawSentences) {
        List<List<String>> cleaned = new ArrayList<>();
        for (List<String> sentence : rawSentences) {
            List<String> cleanedSentence = new ArrayList<>();
            for (String word : sentence) {
                String w = word.toLowerCase().replaceAll("[^a-z]", "");
                if (!stopwords.contains(w) && w.length() > 1) {
                    cleanedSentence.add(w);
                }
            }
            if (cleanedSentence.size() > 1) {
                cleaned.add(cleanedSentence);
            }
        }
        return cleaned;
    }
}
