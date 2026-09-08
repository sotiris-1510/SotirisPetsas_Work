package HW4_Team50;

import java.util.*;
import java.io.*;


/**
 * An abstract class providing methods for reading and processing text
 * from files or strings into lists of word lists.
 */

public abstract class TextFormat {
    List<String> filenames = new ArrayList<>();
    String text;

    public TextFormat() {
        
    }

    /**
     * Abstract method to be implemented to process a text into a list of word lists.
     *
     * @param text The input text.
     * @return A list of sentences, where each sentence is a list of words.
     */

    public abstract List<List<String>> getSentenceLists(String text);

      /**
     * Reads text files, extracts the text, and processes it into lists of word lists.
     *
     * @param filenames List of filenames
     * @return A list of sentences from all files, where each sentence is a list of words.
     */

    public List<List<String>> getSentenceListsFromFiles(List<String> filenames) {
        List<List<String>> allSentences = new ArrayList<>();

        for (int i = 0; i < filenames.size(); i++) {
            String filename = filenames.get(i);

            StringBuilder builder = new StringBuilder();

            String st = "HW4_Team50/" + filename + ".txt";
            try (BufferedReader reader = new BufferedReader(new FileReader(st))) {
                String line;

                while ((line = reader.readLine()) != null) {
                    builder.append(line).append(" ");
                }

                String fullText = builder.toString();

            } catch (IOException e) {
                System.out.println("Σφάλμα κατά την ανάγνωση του αρχείου: " + filename);
                System.out.println("Μήνυμα: " + e.getMessage());
            }

            String fullText = builder.toString();
            allSentences = getSentenceLists(fullText);
        }

        return allSentences;
    }
}
