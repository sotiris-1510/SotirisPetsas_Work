package HW4_Team50;

import java.util.*;

/**
 * A class that extends {@link TextFormat} and processes text
 * into lists of words for each sentence.
 */

public class SentenceListFile extends TextFormat {

    /**
     * Splits the given text into sentences and then splits each sentence into a list of words.
     *
     * @param text The input text.
     * @return A list of sentences, where each sentence is a list of words.
     */

    public List<List<String>>  getSentenceLists(String text) {

        String[] sentences = text.split("[.!?]");
        List<List<String>> sentenceLists = new ArrayList<>();

        for (int i = 0; i < sentences.length; i++) {
            String sentence = sentences[i].trim(); 
            String trimmedSentence = sentence.trim();

            trimmedSentence = trimmedSentence.toLowerCase();

            if (!trimmedSentence.isEmpty()) {
                String[] words = trimmedSentence.split("[,-;:()\"'\\s]+");
                List<String> wordList = new ArrayList<>(Arrays.asList(words));
                sentenceLists.add(wordList);
            }
        }

        return sentenceLists;
    }
    
}
